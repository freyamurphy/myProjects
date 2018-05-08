/* Author: Freya Murphy 170004881
   Date created: 09-11-17
   Date last modified: 20-11-17
   Purpose: Translate an assembly program into machine code for the Manchester Baby.
*/

#include <string>
#include <vector>
#include <iostream>
// For reading and writing to files
#include <fstream>
// For converting other types to string
#include <sstream>
// For formatting output as a table
#include <iomanip>

#include "assembler.h"

using namespace std;


/***************
 * GLOBAL VARIABLES
 ***************/

// Stores labels and their corresponding memory address
vector< vector<string> > symbolTable;
// Stores lines of machine code to output to file
vector< vector<bool> > outputBuffer;
vector< vector<string> > parsedFile;

/***************
 * MAIN FUNCTIONS
 ***************/

int main(int argc, char** argv) {
    try {
        string file;
        // No argument was given
        if (argc == 1) {
            file = getAssemblyFileName();
        }
        // 1 argument was given
        else if (argc == 2) {
            file = argv[1];
        }
        else {
            string filename;
            stringstream convert;
            convert << argv[0];
            convert >> filename;
            string msg = "Error: " + filename + " takes 0 or 1 argument." + '\n' + "Usage: " + filename + " [filename]";
            throw msg;
        }
        assemble(file);
    }
    catch (string msg) {
        cout << msg << endl;
    }
    
    
    return 0;
}

/*
 * Translates an assembly file into machine code and outputs to a file
 */
void assemble(string fileName) {
    cout << "*** PARSING FILE ***" << endl;
    parseFile(fileName);
    cout << endl << "*** FIRST PASS ***" << endl;
    firstPass();
    cout << endl << "*** SECOND PASS ***" << endl;
    secondPass();
    cout << endl << "*** SAVING TO FILE ***" << endl;
    sendOutputBufferToFile();
}

/*
 * Translates instructions and adds labels and variable names to symbol table.
 */
void firstPass() {
    int currAddress = 0;
    vector<string> currLine;
    string label;
    string instruction;
    string operand;
    vector<bool> opcode;
    vector<bool> oBRow;
    vector<bool> memoryAdd;
    bool containsSTP;
    
    for (int l = 0; l < static_cast<int>(parsedFile.size()); l++) {
        // Get label, instruction and operand for this line
        currLine = parsedFile.at(l);
        label = currLine.at(0);
        instruction = currLine.at(1);
        operand = currLine.at(2);
        
        // A label must refer to the address of an instruction.
        if (label != "" && instruction == "") {
            string strl;
            stringstream convert;
            convert << l+1;
            convert >> strl;
            
            string msg = "Error on line " + strl + ": Cannot have label with no instruction."; 
            throw msg;
        }
        // The label refers to the address of the current line
        else if (label != "" && instruction != "") {
            addToSymbolTable(label, currAddress);
        }
        
        if (instruction.size() > 0) {
            // Initialise output buffer
            oBRow.clear();
            for (int i = 0; i < 32; i++) {
                oBRow.push_back(0);
            }
            
            outputBuffer.push_back(oBRow);
            
            // Special case when a variable is declared
            if (instruction == "VAR") {
                // Validate operand
                if (!validateNumbericalOperand(operand)) {
                    string strl;
                    stringstream convert;
                    convert << l+1;
                    convert >> strl;
                    string msg = "Error on line " + strl + ": Invalid operand used with VAR";
                    throw msg;
                }
                
                int decNum;
                stringstream ss;
                ss << operand;
                ss >> decNum;
                
                // Convert the operand to a binary number
                vector<bool> binNum = convertDecimalToBinary(decNum);
                
                // Send the number to the output buffer
                outputBuffer.at(currAddress) = binNum;
                
                // Move to the next instruction
                currAddress++;
                continue;
            }
            
            // Decode instruction
            else {
                try {
                    opcode = decodeInstruction(instruction);
                    sendInstructionToOutputBuffer(opcode, currAddress);
                }
                catch(string e) {
                    string line;
                    stringstream convert;
                    convert << l+1;
                    convert >> line;
                    
                    string msg = "Error on line " + line + ": " + e;
                    throw msg;
                }
            }
            
            // The program must contain an STP instruction at some point.
            if (instruction == "STP") {
                containsSTP = true;
            }
            
            // If an operand is required
            if (!(instruction == "STP" || instruction == "CMP") ) {
                
                if (operand.size() == 0) {
                    string line;
                    stringstream convert;
                    convert << l+1;
                    convert >> line;
                    
                    string msg = "Error on line " + line + ": ";
                    msg += instruction + " requires an operand.";
                    throw msg;
                }
                
                // If the operand is not a label
                if (validateNumbericalOperand(operand)) {
                    memoryAdd = convertStringToBoolVector(operand);
                    sendOperandToOutputBuffer(memoryAdd, currAddress);
                }
                else {
                    addToSymbolTable(operand);
                }
                
            }
            
            currAddress++;
        }
        
    }
    
    // Without STP, the program will continue running forever.
    if (!containsSTP) {
        string msg = "Error: Every program must contain an STP instruction.";
        throw msg;
    }
    
    // For testing
    cout << endl << "Output buffer:" << endl;
    displayOB();
    cout << endl << "Symbol table:" << endl;
    displayST();
}

/*
 * Fills in blanks in output buffer using symbol table.
 */
void secondPass() {
    
    int currAddress = 0;
    string instruction;
    string operand;
    int operandAddress;
    
    for (int i = 0; i < static_cast<int>(parsedFile.size()); i++) {
        
        // Get instruction and operand for this line
        instruction = parsedFile.at(i).at(1);
        operand = parsedFile.at(i).at(2);
        
        // Skip lines with no instruction
        if (!(instruction.size() == 0)) {
            
            // All instructions other than STP and CMP require an operand.
            if (!(instruction == "STP" || instruction == "CMP")) {
                
                // Check whether the operand is a variable
                if (!validateNumbericalOperand(operand)) {
                    
                    // Get address of variable for symbol table
                    operandAddress = getLabelAddress(operand);
                    
                    // Check that the variable has an address
                    if (operandAddress == -1) {
                        string line;
                        stringstream convert;
                        convert << i+1;
                        convert >> line;
                        
                        string msg = "Error on line " + line + ": " + "value of ";
                        msg += operand;
                        msg += " is undefined.";
                        throw msg;
                    }
                    
                    // Convert the address to binary
                    vector<bool> operandVctr = convertDecimalToBinary(operandAddress);
                    
                    // Send the operand to the output buffer :)
                    sendOperandToOutputBuffer(operandVctr, currAddress);
                    
                }
                
            }
            
            // Move to the next instruction
            currAddress++;
        }
    }
    
    // For testing
    cout << "Output buffer:" << endl;
    displayOB();
}

/***************
 * FUNCTIONS RELATING TO SYMBOL TABLE
 ***************/
/*
 * Displays the labels and corresponding addresses currently stored in symbolTable.
 */
void displayST() {
    // Fill in gaps with spaces
    const char separator = ' ';
    // Number of characters to allocate to address
    const int numWidth = 5;
    // Number of characters to allocate to words
    const int wordWidth = 15;
    
    // Display headings
    cout << left << setw(wordWidth) << setfill(separator) << "LABEL";
    cout << left << setw(numWidth) << setfill(separator) << "ADDRESS";
    cout << endl;
    
	for (int i = 0; i < static_cast<int>(symbolTable.size()); i++) {
        cout << left << setw(wordWidth) << setfill(separator) << symbolTable.at(i).at(0);
        cout << left << setw(wordWidth) << setfill(separator) << symbolTable.at(i).at(1);
        cout << endl;
	}
}

/*
 * Adds a label to the symbol table and sets the corresponding address to -1.
 * If the label is already in the symbol table, the function has no effect.
 */
void addToSymbolTable(string label) {
    int index = getLabelIndex(label);
    
    // If label is not in table
    if (index == -1) {
        // Add label to symbol table
        vector<string> newRow = {label, "-1"};
        symbolTable.push_back(newRow);
    }
}

/*
 * Adds a label and address pair to the symbol table.
 * If the label is not already in the table the pair is added to the end of the table.
 * If the label is in the table the address is added at that row.
 */
void addToSymbolTable(string label, int address) {
    // Convert the address to a string so it can be stored in the table
    string strAddress;
    stringstream ss;
    ss << address;
    ss >> strAddress;
    
    int index = getLabelIndex(label);
    // The label is not already in the table
    if (index == -1) {
        // Create the row to add to the table
        vector<string> row = {label, strAddress};
        // Add row to end of table
        symbolTable.push_back(row);
    }
    else {
        // Add address to row
        symbolTable.at(index).at(1) = strAddress;
    }
    
}

/*
 * Searches symbolTable for a label and returns its index
 * Returns -1 if the label is not in the table.
 */
int getLabelIndex(string label) {
    int row = 0;
    
    while (row < static_cast<int>(symbolTable.size())) {
        if (symbolTable.at(row).at(0) == label) {
            return row;
        }
        
        row++;
    }
    return -1;
}

/*
 * Searches symbol table for a string and returns its corresponding address
 * Returns -1 if the string is not in the table or the label does not have an address.
 */
int getLabelAddress(string label) {
    string address = "-1";
    int intAddress;
    int row = 0;
    bool found = false;
    
    while (row < static_cast<int>(symbolTable.size()) && !found) {
        
        // If the label matches
        if (symbolTable.at(row).at(0) == label) {
            address = symbolTable.at(row).at(1);
            found = true;
        }
        
        row++;
    }
    
    // Address is stored in the table as a string
    // so convert it to int
    stringstream convert;
    convert << address;
    convert >> intAddress;
    
    return intAddress;
}

/***************
 * FUNCTIONS RELATING TO OUTPUT BUFFER
 ***************/
/*
 * Displays the current state of the output buffer.
 */
void displayOB() {
    // Fill in gaps with spaces
    const char separator = ' ';
    // Number of characters to allocate to line number
    const int numWidth = 10;
    
    cout << left << setw(numWidth) << setfill(separator) << "ADDRESS";
    cout << "INSTRUCTION" << endl;
    
	for (int i = 0; i < static_cast<int>(outputBuffer.size()); i++) {
        cout << left << setw(numWidth) << i;
		for (int j = 0; j < static_cast<int>(outputBuffer.at(i).size()); j++) {
			cout << outputBuffer.at(i).at(j);
		}
		cout << endl;
	}
}

/*
 * Writes a memory address to a specified line in the output buffer.
 */
void sendOperandToOutputBuffer(vector<bool> operand, int line) {
    for (int i = 0; i < static_cast<int>(operand.size()) && i < 5; i++) {
        outputBuffer.at(line).at(i) = operand.at(i);
    }
}

/*
 * Writes an opcode to a specified line in the output buffer.
 */
void sendInstructionToOutputBuffer(vector<bool> instruction, int line) {
    for (int i = 0; i < static_cast<int>(instruction.size()); i++) {
        outputBuffer.at(line).at(i+13) = instruction.at(i);
    }
}

/*
 * Writes contents of output buffer to a machine code file
 */
void sendOutputBufferToFile() {
    // Get filename from user
    string filename;
    cout << "Enter the name of the machine code file:" << endl;
    cin >> filename;
    
    // Open file for writing
    ofstream file;
    file.open(filename);
    
    if (file.is_open()) {
        for (int row = 0; row < static_cast<int>(outputBuffer.size()); row++) {
            for (int bit = 0; bit < static_cast<int>(outputBuffer.at(row).size()); bit++) {
                file << outputBuffer.at(row).at(bit);
            }
            file << '\n';
        }
    }
    else {
        string msg = "Unable to open " + filename + " for writing.";
        throw msg;
    }
    
}

/***************
 * FUNCTIONS RELATING TO PARSING FILE
 ***************/
/*
 * Displays the contents of the assembly file once it has been parsed.
 */
void displayPF() {
	// Fill in gaps with spaces
	const char separator = ' ';
    // Number of characters to allocate to line number
	const int numWidth = 5;
    // Number of characters to allocate to words
	const int wordWidth = 15;
    
    // Display headings
	cout << left << setw(numWidth) << setfill(separator) << "LINE";
	cout << left << setw(wordWidth) << setfill(separator) << "LABEL";
	cout << left << setw(wordWidth) << setfill(separator) << "INSTRUCTION";
	cout << left << setw(wordWidth) << setfill(separator) << "OPERAND";
	cout << endl;
		
    // Output contents of parsedFile
	for (int i = 0; i < static_cast<int>(parsedFile.size()); i++) {
		cout << left << setw(numWidth) << setfill(separator) << i+1;
		for (int j = 0; j < static_cast<int>(parsedFile.at(i).size()); j++) {
			cout << left << setw(wordWidth) << setfill(separator) << parsedFile.at(i).at(j);
		}
		cout << endl;
	}
}

/*
 * Splits a line of assembly code into a label, instruction operand and comment.
 */
vector<string> parseLine(string line) {
    char currChar;
    char prevChar = 'x';
    int currField = 0;
    
    // Initially all fields are empty.
    // There is no need for a comment field because comments are discarded.
    vector<string> parsedLine = {"","",""};
    
    for (int i = 0; i < static_cast<int>(line.size()) && currField < static_cast<int>(parsedLine.size()); i++) {
        // Get next character
        currChar = line.at(i);
        
        // Special cases
        // Any of these characters signify the end of the line
        // ASCII 13 is a carriage return, sometimes used in place of '/n'
        if (currChar == ';' || currChar == '\n' || static_cast<int>(currChar) == 13) {
            // The rest of the line can be discarded
            return parsedLine;
        }
        // End of field
        else if (currChar == ' ' && prevChar != ' ' && prevChar != ':') {
            currField++;
        }
        // End of label
        else if (currField == 0 && currChar == ':') {
            currField++;
        }
        // General case
        else if (currChar != ' ' && currChar != '\t') {
            parsedLine.at(currField) += currChar;
        }
        
        prevChar = currChar;
    }
    
    return parsedLine;
}

/*
 * Reads an assembly file one line at a time and stores it in a vector for processing.
 */
vector<string> readFile(string fileName) {
    string line;
    vector<string> lines;
    ifstream inputFile(fileName);
    
    if (inputFile.is_open()) {
        
        while ( getline(inputFile, line) ) {
            
            lines.push_back(line);
            
        }
        
        inputFile.close();
        
    }
    
    else {
        string msg = "Unable to open " + fileName + " for reading.";
        throw msg;
    }
    
    return lines;
}

/*
 * Get name of file to assemble from user
 */
string getAssemblyFileName() {
    string file;
    cout << "Enter the name of the file to assemble: " << endl;
    cin >> file;
    return file;
}

/*
 * Takes a vector of lines and splits it into labels, instructions, operands and comments.
 * The result is stored in the parsedFile global variable.
 */
void parseFile(string fileName) {
    // Read assembly file into a vector
    vector<string> lines = readFile(fileName);
    string currLine;
    vector<string> parsedLine;
    
    // Parse each line
    for (int i = 0; i < static_cast<int>(lines.size()); i++) {
        currLine = lines.at(i);
        
        // Parse line
        parsedLine = parseLine(currLine);
        // Store in parsedFile global variable
        parsedFile.push_back(parsedLine);
    }
    
    // For testing
    cout << endl << "Parsed file:" << endl;
    displayPF();
}

/***************
 * FUNCTIONS THAT CONVERT BETWEEN DATA TYPES
 ***************/

/*
 * Converts a decimal integer to a binary vector
 */
vector<bool> convertDecimalToBinary(int decNum) {
	// Vector to store number in binary
	vector<bool> binNum(32);
	
	int remainder;
	
	// Repeatedly divide decNum by two and store remainder as binary digit
	for (int i = 0; i < static_cast<int>(binNum.size()); i++) {
		remainder = decNum % 2;
		decNum /= 2;
		
		binNum.at(i) = remainder;
	}
	
	return binNum;
}

/*
 * Convert a string of 1s and 0s to a vector of bools
 */
vector<bool> convertStringToBoolVector(string str) {
    vector<bool> vctr;
    
    for (int i = 0; i < static_cast<int>(str.size()); i++) {
        if (str.at(i) == '1') {
            vctr.push_back(1);
        }
        else {
            vctr.push_back(0);
        }
    }
    
    return vctr;
}

/***************
 * MISCELLANEOUS FUNCTIONS
 ***************/

/*
 * Converts a mnemonic for an instruction to its corresponding machine code opcode.
 */
vector<bool> decodeInstruction(string instruction) {
	string opcode;
	
	// Translate mneumonic to opcode
	if (instruction == "JMP") {
		opcode = "000";
	}
	else if (instruction == "JRP") {
		opcode = "100";
	}
	else if (instruction == "LDN") {
		opcode = "010";
	}
	else if (instruction == "STO") {
		opcode = "110";
	}
	else if (instruction == "SUB") {
		opcode = "001";
	}
	else if (instruction == "CMP") {
		opcode = "011";
	}
	else if (instruction == "STP") {
		opcode = "111";
	}
	else {
        string msg = "Instruction " + instruction + " not recognised.";
		throw msg;
	}
	
	// Convert opcode from string to vector
	return convertStringToBoolVector(opcode);
	
}

/*
 * Checks that every character in the operand is a digit from 0-9.
 */
bool validateNumbericalOperand(string operand) {
    
    char c;
    for (int i = 0; i < static_cast<int>(operand.size()); i++) {
        c = operand.at(i);
        // If c is not a digit
        if (!(c=='0'||c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9')) {
            return false;
        }
    }
    return true;
}

