/* Authors: Freya Murphy 170004881
	    Cerys Kelly  160016475
*/


#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

/* Use vectors to store parent and child generations
   This allows the width to be changed.*/
vector<bool> parent;
vector<bool> child;

// A 2D vector is needed to store the whole picture
vector< vector<bool> > picture;

// rule should always have size 8 since 2^3=8 (3 bits with 2 options each)
vector<bool> rule(8);

// Characters to output in picture
const char* char1 = "\u25A0";
const char* char2 = "  ";

/* Get an integer from the user and return it */
int getWidth() {
	int width;

	cout << "How many columns would you like in the picture?" << endl;
	cin >> width;

	// Input validation
	while (!cin || width <= 0) {
		cerr << "Invalid input." << endl;
		cout << "How many columns would you like in the picture?" << endl;

		// Clear the stream and try again.
		cin.clear();
		cin.ignore(256, '\n');
		cin >> width;
	}

	return width;
}

/* Get an integer from the user and return it */
int getHeight()
{
	int height;

	cout << "How many rows would you like in the picture?" << endl;
	cin >> height;

	// Input validation
	while (!cin || height <= 0) {
		cerr << "Invalid input." << endl;
		cout << "How many rows would you like in the picture?" << endl;

		// Clear the stream and try again.
		cin.clear();
		cin.ignore(256, '\n');
		cin >> height;
	}
	return height;
}

/* Get user to enter a series of 1s and 0s to be the first row in the picture. */
vector<bool> userGeneratedRow()
{
	int userInput;
	vector<bool> userGeneratedRow;

	// Ask user how long they want the row to be
	int width = getWidth();

	cout << "Inputting first row:" << endl;

	// Get input
	for(int i =0;i<width;i++)
	{
		cout<<"Please enter a 1 or a 0 and press 'Enter'"<<endl;
		cin>>userInput;

		// Input validation
		while (!(userInput == 1 || userInput == 0) || !cin) {

			// Failed to read input, probably because user entered a string
			if (!cin) {
				// Clear error flags
				cin.clear();
				// Ignore characters that caused error
				cin.ignore(256, '\n');
			}

			cout << "Invalid input." << endl;
			cout << "Please enter a 1 or a 0 and press 'Enter'" << endl;
			cin >> userInput;
		}

		// Add bit to vector
		userGeneratedRow.push_back(userInput);
	}
	return userGeneratedRow;

}

/* Randomly select a series of 1s and 0s to be the first row in the picture.*/
vector<bool> randomParentGeneration()
{
	// The next bit to add to the row
	bool bit;

	vector<bool> randomGeneration;

	// Ask user how long they want the row to be.
	int width = getWidth();
	// Initialise random seed
	srand(time(NULL));

	for (int i = 0; i < width; i++)
	{
		// randomly choose 1 or 0
		bit = rand() % 2;
		// Add bit to row
		randomGeneration.push_back(bit);
	}
	return randomGeneration;
}

/* Set values of first row in picture */
void initParent()
{

	// Reset the row
	parent.clear();

	//Small menu for choosing how the parent is generated.
	int userInput;
	cout<<"Please choose from the following: "<<endl;
	cout<<"1. Use a randomly generated first row."<<endl;
	cout<<"2. Enter a first row."<<endl;
	cin>>userInput;

	// Input validation for menu
	while (userInput < 1 || userInput > 2 || !cin) {

		// Failed to read input, probably because user entered a string
		if (!cin) {
			// Clear error flags
			cin.clear();
			// Ignore characters that caused error
			cin.ignore(256, '\n');
		}

		cout << "Invalid input. Please try again." << endl;
		cout<<"Please choose from the following: "<<endl;
		cout<<"1. Use a randomly generated first row."<<endl;
		cout<<"2. Enter a first row."<<endl;
		cin>>userInput;
	}

	// Call relevant function
	switch(userInput)
	{
		case 1:	parent = randomParentGeneration();
			break;
		case 2: parent = userGeneratedRow();
			break;
	}
}

/* Converts a decimal number to an 8 bit binary number */
vector<bool> convertDecimalToBinary(int decNum) {
	// Vector to store rule in binary
	vector<bool> binNum(8);

	int remainder;

	// Repeatedly divide decNum by two and store remainder as binary digit
	for (int i = 1; i < binNum.size()+1; i++) {
		// Get remainder after division by 2
		remainder = decNum % 2;
		// Divide by 2
		decNum /= 2;

		// Store remainder in vector
		if (binNum.size()-i >= 0) {
			binNum[binNum.size() - i] = remainder;
		}
	}

	return binNum;
}

/* Convert an 8 bit binary number to a decimal value */
int convertBinaryToDecimal(vector<bool> binNum) {
	int decNum = 0;
	int binDigit;
	int powerOfTwo = 1;

	for (int i = binNum.size()-1; i >= 0; i--) {
		// Get binary digit
		binDigit = binNum.at(i);

		// Multiply digit by appropriate power of 2 and add this to the total
		decNum += binDigit*powerOfTwo;

		// The power of 2 increases with each column
		powerOfTwo *= 2;
	}

	return decNum;
}

/* Chooses a random rule from 0 to 255 and converts it to binary.*/
vector<bool> getRandomRule() {
	// This line is needed to make the numbers appear more random
	srand(time(NULL));

	// Choose random number from 0 to 256
	int decRule = rand() % 256;
	cout << "Rule " << decRule << endl;

	// Convert this rule to binary
	vector<bool> binRule = convertDecimalToBinary(decRule);

	return binRule;
}

/* Gets user to input their own rule in binary */
vector<bool> getUserRule()
{
	vector<bool> binRule;
	int usrInput;

	// User enters rule bit by bit
	for(int i =0;i<8;i++)
	{
		cout<<"Please enter a 1 or a 0 and press 'Enter'"<<endl;
		cin>>usrInput;

		// Input validation
		while (!(usrInput == 1 || usrInput == 0) || !cin) {

			// Failed to read input, probably because user entered a string
			if (!cin) {
				// Clear error flags
				cin.clear();
				// Ignore characters that caused error
				cin.ignore(256, '\n');
			}

			cout << "Invalid input." << endl;
			cout << "Please enter a 1 or a 0 and press 'Enter'" << endl;
			cin >> usrInput;
		}

		// Add bit to rule vector
		binRule.push_back(usrInput);
	}
	int decNum = convertBinaryToDecimal(binRule);
	cout<<"Rule " << decNum<<endl;
	return binRule;
}

/* Gets the user to input their own rule in decimal */
vector<bool> getUserDecRule()
{
	int userInput;
	vector<bool> decRule;
	cout<<"Please enter a value from 0 to 255: "<<endl;
	cin>>userInput;

	// Input validation
	while (userInput < 0 || userInput > 255 || !cin) {

		// Failed to read input, probably because user entered a string
		if (!cin) {
			// Clear error flags
			cin.clear();
			// Ignore characters that caused error
			cin.ignore(256, '\n');
		}

		cout << "Invalid input." << endl;
		cout << "Please enter a value from 0 to 255." << endl;
		cin >> userInput;
	}

	cout<< "You have entered Rule "<< userInput<<endl;

	// Convert the rule to binary
	decRule = convertDecimalToBinary(userInput);
	return decRule;
}

/* Set value of rule vector */
void setRule() {
	// Vector to store rule as binary number
	vector<bool> binRule(8);
	//use case statement for menu
	int userInput;
	cout<<"Please choose from the following: "<<endl;
	cout<<"1. Use a random rule."<<endl;
	cout<<"2. Enter a rule in binary."<<endl;
	cout<<"3. Enter a rule in decimal."<<endl;
	cin>>userInput;

	// Input validation
	while (userInput < 1 || userInput > 3 || !cin) {

		// Failed to read input, probably because user entered a string
		if (!cin) {
			// Clear error flags
			cin.clear();
			// Ignore characters that caused error
			cin.ignore(256, '\n');
		}

		cout << "Invalid input. Please try again." << endl;
		cout<<"Please choose from the following: "<<endl;
		cout<<"1. Use a random rule."<<endl;
		cout<<"2. Enter a rule in binary."<<endl;
		cout<<"3. Enter a rule in decimal."<<endl;
		cin >> userInput;
	}

	switch(userInput)
	{
		case 1: binRule = getRandomRule();
			break;
		case 2: binRule = getUserRule();
			break;
		case 3:	binRule = getUserDecRule();
			break;
	}
	// Reset rule
	rule.clear();

	// Copy values into rule vector
	rule = binRule;
}

/* Calculates the contents of child row based on parent row
   mode=0 sets out of bounds neightbour cells to 0
   mode=1 wraps cells around when calculating neighbours */
void calculateChild(bool mode) {
	bool currentVal;
	bool prevVal;
	bool nextVal;

	// Reset child row
	child.clear();

	// Loop through each cell in the row
	for (int i=0; i < parent.size(); i++) {
		currentVal = parent.at(i);

		// There is no previous cell for the first cell in the row.
		if (i <= 0) {
			if (mode==1) {
				prevVal = parent.at(parent.size()-1);
			}
			else {
				prevVal = 0;
			}
		}
		else {
			prevVal = parent.at(i-1);
		}

		// The last cell in the array has no next cell.
		if (i >= parent.size()-1) {
			if (mode==1) {
				nextVal = parent.at(0);
			}
			else {
				nextVal = 0;
			}
		}
		else {
			nextVal = parent.at(i+1);
		}

		// Setting value of child row
		if (prevVal && currentVal && nextVal) {
			child.push_back(rule.at(0));
		}
		else if (prevVal && currentVal && !nextVal) {
			child.push_back(rule.at(1));
		}
		else if (prevVal && !currentVal && nextVal) {
			child.push_back(rule.at(2));
		}
		else if (prevVal && !currentVal && !nextVal) {
			child.push_back(rule.at(3));
		}
		else if (!prevVal && currentVal && nextVal) {
			child.push_back(rule.at(4));
		}
		else if (!prevVal && currentVal && !nextVal) {
			child.push_back(rule.at(5));
		}
		else if (!prevVal && !currentVal && nextVal) {
			child.push_back(rule.at(6));
		}
		else {
			child.push_back(rule.at(7));
		}
	}
}

// Displays current value of parent row
void outputParent() {
	const char* outChar;
	for (int i = 0; i < parent.size(); i++) {
		if (parent.at(i)) {
			outChar = char1;
		}
		else {
			outChar = char2;
		}
		cout << outChar;
	}
	cout << endl;
}

// Displays current value of child row
void outputChild() {
	const char* outChar;
	for (int i = 0; i < child.size(); i++) {
		if (child.at(i)) {
			outChar = char1;
		}
		else {
			outChar = char2;
		}
		cout << outChar;
	}
	cout << endl;
}

// Asks user whether they want edges to wrap around and returns true or false
bool getWrap() {
	char answer;
	cout << "Would you like to wrap the edges of the picture around? [y/n] " << endl;
	cin >> answer;

	// Input validation
	while (!(answer == 'y' || answer == 'n') || !cin) {

		// Reset error flags
		if (!cin) {
			cin.clear();
		}

		// Ignore invalid characters
		cin.ignore(256, '\n');

		cout << "Invalid input. Please try again." << endl;
		cout << "Would you like to wrap the edges of the picture around? [y/n]" << endl;
		cin >> answer;
	}

	if (answer=='y') {
		return 1;
	}
	else {
		return 0;
	}
}

// Output text based picture by repeatedly calling calculateChild()
void outputPicture() {

	// Get options from user
	int height = getHeight();
	bool wrap = getWrap();

	// Print first row
	outputParent();
	// Add parent row to 2D vector in case the user wants to save to a file
	picture.push_back(parent);

	// Generate and print out child rows
	for (int i = 0; i < height; i++) {
		calculateChild(wrap);
		outputChild();
		picture.push_back(child);
		// This child becomes the parent of the next row.
		parent = child;
	}
}

void saveToFile() {
	string fileName;
	cout << "Enter a name for the file:" << endl;
	cin >> fileName;

	// Create file
	ofstream outputFile(fileName);

	// Write to file
	if (outputFile.is_open()) {

		for (int row = 0; row < picture.size(); row++) {

			for (int col = 0; col < picture.at(0).size(); col++) {

				if (picture.at(row).at(col)) {
					outputFile << char1;
				}
				else {
					outputFile << char2;
				}
			}
			outputFile << "\n";
		}
		outputFile.close();
		cout << "The picture was successfully saved to " << fileName << endl;

	}
	else {
		cerr << "Unable to open file.";
	}
}

bool askToSave() {
	char answer;
	cout << "Would you like to save the picture to a file? [y/n]" << endl;
	cin >> answer;

	// input validation
	while (!(answer == 'y' || answer == 'n') || !cin) {

		// Reset error flags
		if (!cin) {
			cin.clear();
		}

		// Ignore invalid characters
		cin.ignore(256, '\n');

		cout << "Invalid input. Please try again." << endl;
		cout << "Would you like to save the picture to a file? [y/n]" << endl;
		cin >> answer;
	}

	if (answer == 'y') {
		return 1;
	}
	else {
		return 0;
	}
}

void runProgram() {
	// Set rule from 0 to 255
	setRule();
	// Set first row of picture
	initParent();
	// Output picture to screen
	outputPicture();

	// Ask the user if they want to save the picture to a file
	if ( askToSave() ) {
		saveToFile();
	}
}

int main() {
	runProgram();
  	return 0;
}
