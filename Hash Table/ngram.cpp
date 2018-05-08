#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
 * readFile
 * Reads file into a vector of characters
 */
vector<char> readFile(string fileName) {
	vector<char> characters;
	char c;

	ifstream file(fileName.c_str());

	if (file.is_open()) {
		while ( file.get(c) ) {
			characters.push_back(c);
		}
		file.close();
	}
	else {
		cout << "Unable to open file.";
	}
	return characters;
}

/*
 * countnGrams
 * Stores all ngrams in a HashTable along with their frequency
 */
void countnGrams(vector<char> characters, int n, HashTable<string, int> &table) {
	string ngram;
	
	for (int i=0; i+(n-1) < static_cast<int>(characters.size()); i++) {
			ngram.clear();

			for (int j=0; j < n; j++) {
				ngram += characters.at(i+j);
			}
			
			cout << ngram << endl;
			
			// Assume this is the first occurence of the ngram
			try {
				table.insert(ngram, 1);
			}
			// The ngram has already been added
			catch (HashTableError) {
				// Store the number of occurences of this ngram
				int occurences = table.getValue(ngram);
				// Remove the ngram from the table
				table.erase(ngram);
				// Re-insert the ngram with new occurences value
				table.insert(ngram, occurences+1);
			}

	}
}

void sortnGrams(HashTable<string, int> &table) {
    vector<string> ngrams(10);
    vector<int> occurrences(10);
    int indexOfMin;
    
    for (int i = 0; i < static_cast<int>(table.size())-1; i++) {
        
    }
}

int main(int argc, char** argv) {
	/*
	IF inputfile.txt exists THEN
		get ngrams from file
		calculate ngram frequency
		sort ngrams by frequency
		output list of top 10 ngrams
	ELSE
		DISPLAY error message
		RETURN 1
	END IF
	*/
    string fileName;
    int N;
    
    if (argc != 3) {
        cout << "Error. " << argv[0] << " takes 2 arguments.";
        cout << "Usage: ./ngram filename N";
        return 1;
    }
    else {
        fileName = argv[1];
        N = static_cast<int>(argv[2]);
    }
	
    try {
        HashTable<string, int>* table = new HashTable<string, int>();
        // Read all the characters from the file into a vector
        vector<char> characters = readFile(fileName);
        
        countnGrams(characters, N, *table);
    }
    catch (const char*) {
        return 1;
    }
	
    return 0;
}
