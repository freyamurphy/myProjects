#include <string>
#include <vector>
// For reading and writing to files
#include <fstream>

using namespace std;

/***************
 * MAIN FUNCTIONS
 ***************/

/*
 * Translates an assembly file into machine code and outputs to a file
 */
void assemble(string fileName);

/*
 * Translates instructions and adds labels and variable names to symbol table.
 */
void firstPass();

/*
 * Fills in blanks in output buffer using symbol table.
 */
void secondPass();

/***************
 * FUNCTIONS RELATING TO SYMBOL TABLE
 ***************/
/*
 * Displays the labels and corresponding addresses currently stored in symbolTable.
 */
void displayST();

/*
 * Adds a label to the symbol table and sets the corresponding address to -1.
 * If the label is already in the symbol table, the function has no effect.
 */
void addToSymbolTable(string label);

/*
 * Adds a label and address pair to the symbol table.
 * If the label is not already in the table the pair is added to the end of the table.
 * If the label is in the table the address is added at that row.
 */
void addToSymbolTable(string label, int address);

/*
 * Searches symbolTable for a label and returns its index
 * Returns -1 if the label is not in the table.
 */
int getLabelIndex(string label);

/*
 * Searches symbol table for a string and returns its corresponding address
 * Returns -1 if the string is not in the table or the label does not have an address.
 */
int getLabelAddress(string label);

/***************
 * FUNCTIONS RELATING TO OUTPUT BUFFER
 ***************/
/*
 * Displays the current state of the output buffer.
 */
void displayOB();

/*
 * Writes a memory address to a specified line in the output buffer.
 */
void sendOperandToOutputBuffer(vector<bool> operand, int line);

/*
 * Writes an opcode to a specified line in the output buffer.
 */
void sendInstructionToOutputBuffer(vector<bool> instruction, int line);

/*
 * Writes a memory address to a specified line in the output buffer.
 */
void sendOperandToOutputBuffer(vector<bool> operand, int line);

/*
 * Writes contents of output buffer to a machine code file
 */
void sendOutputBufferToFile();

/***************
 * FUNCTIONS RELATING TO PARSING FILE
 ***************/
/*
 * Displays the contents of the assembly file once it has been parsed.
 */
void displayPF();

/*
 * Splits a line of assembly code into a label, instruction operand and comment.
 */
vector<string> parseLine(string line);

/*
 * Reads an assembly file one line at a time and stores it in a vector for processing.
 */
vector<string> readFile(string fileName);

/*
 * Get name of file to assemble from user
 */
string getAssemblyFileName();

/*
 * Takes a vector of lines and splits it into labels, instructions, operands and comments.
 * The result is stored in the parsedFile global variable.
 */
void parseFile(string fileName);

/***************
 * FUNCTIONS THAT CONVERT BETWEEN DATA TYPES
 ***************/
/*
 * Converts a decimal integer to a binary vector
 */
vector<bool> convertDecimalToBinary(int decNum);

/*
 * Convert a string of 1s and 0s to a vector of bools
 */
vector<bool> convertStringToBoolVector(string str);

/***************
 * MISCELLANEOUS FUNCTIONS
 ***************/
/*
 * Converts a mnemonic for an instruction to its corresponding machine code opcode.
 */
vector<bool> decodeInstruction(string instruction);

/*
 * Checks that every character in the operand is a digit from 0-9.
 */
bool validateNumbericalOperand(string operand);
