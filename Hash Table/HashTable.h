#ifndef MY_HASH_TABLE
#define MY_HASH_TABLE

#include "HashNode.h"
#include <vector>
#include <string>
#include <sstream>

// temporary
#include <iostream>

using namespace std;

enum HashTableError { OUT_OF_MEMORY, KEY_NOT_FOUND, DUPLICATE_KEY, EMPTY_SLOT_NOT_FOUND }; // extend if necessary

template <class KeyType, class ValueType>
class HashTable {
    typedef vector <HashNode<KeyType,ValueType> > Table;
    Table *table; // size of table (# of buckets) is stored in the Table data structure
    size_t num;   // number of entries stored in the HashTable;

public:
    HashTable();        // constructor, initializes table of size 11;
    HashTable(size_t);  // constructor, requires size of table as arg
    ~HashTable();       // deconstructor

    size_t size();      // returns size of the hash table (number of buckets)
    size_t hash_function(KeyType);  // the table's hash function
    ValueType getValue(KeyType);    // find and return data associated with key

    void insert(KeyType,ValueType); // insert data associated with key into table
    void erase(KeyType);            // remove key and associated data from table

    void rehash(size_t); // sets a new size for the hash table, rehashes the hash table
  
    // extend if necessary
    double getLoadFactor(); // Returns load factor of hash table
    bool keyIsInTable(KeyType); // Returns whether or not a key is stored in the table
    vector<HashNode<string, int> > sort(int); // Sorts hash table in descending order
  
};

template <class KeyType, class ValueType>
size_t HashTable<KeyType,ValueType>::size() {
  return table->size();
}

/* Implement the
- Constructors, Destructor
- hash_function, insert, getValue methods
- erase, and rehash methods 
*/

/*
 * Constructors
 */
template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable() {
	try {
		// Create table
		table = new Table();
	
		// Fill table with empty nodes
		for (int n = 0; n < 11; n++) {
			HashNode<KeyType, ValueType>* node = new HashNode<KeyType, ValueType>;
			table->push_back(*node);
		}
	}
	catch (bad_alloc&) {
		throw OUT_OF_MEMORY;
	}
	
	// There are no keys stored in the table
	num = 0;
}

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable(size_t num) {
	try {
		// Create table
		table = new Table();
	
		// Fill table with empty nodes
		for (int n = 0; n < static_cast<int>(num); n++) {
			HashNode<KeyType, ValueType>* node = new HashNode<KeyType, ValueType>;
			table->push_back(*node);
		}
	}
	catch (bad_alloc&) {
		throw OUT_OF_MEMORY;
	}
	
	// There are no keys in the table
	this->num = 0;
}

/*
 * Destructor
 */
template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::~HashTable() {
	cout << "Table destroyed" << endl;
}

/*
 * hash_function
 * Based on Bernstein hash from lecture slides
 */
template <class KeyType, class ValueType>
size_t HashTable<KeyType, ValueType>::hash_function(KeyType key) {
	size_t hash = 0;
	int prime = 33;
	size_t tableSize = size();
	int asciiCode;
	
	// The string stream converts the key to a string
	// This means the hash function can be used for any primitive data type
	string strKey;
	stringstream ss;
	ss << key;
	ss >> strKey;

	// Hash the string
	for (int i = 0; i < static_cast<int>(strKey.size()); i++) {
		// Convert each character of the string to an integer
		asciiCode = static_cast<int>(strKey.at(i));
		// Add the character code to the hash and multiply by a prime number
		// Mod by tableSize to keep the hash within the size of the table.
		hash = (prime * hash + asciiCode) % tableSize;
	}

	return hash;
	
}

/*
 * getValuec++ check if function does not throw error
 * Find and return the data associated with a key
 */
template <class KeyType, class ValueType>
ValueType HashTable<KeyType, ValueType>::getValue(KeyType key) {
	// Hash key to find where it is in the table
	size_t hash = hash_function(key);

	// Search table for key
	while (table->at(hash).isEmpty() || table->at(hash).getKey() != key) {
	
		// The key is not in the table
		if (table->at(hash).isEmpty() && !table->at(hash).wasDeleted()) {
			cout << "Key not found in getValue." << endl;
			throw KEY_NOT_FOUND;
		}
	
		// Use a linear probing sequence
		hash+=1;
		hash %= size();
		

	}
	
	// Get the required node from the hash table
	HashNode<KeyType, ValueType> node = table->at(hash);

	// Get the value from the node
	ValueType value = node.getValue();

	return value;
}

/*
 * keyIsInTable
 * Returns true if key is in table
 */
template <class KeyType, class ValueType>
bool HashTable<KeyType, ValueType>::keyIsInTable(KeyType key) {
	size_t hash = hash_function(key);
	
	while (table->at(hash).isEmpty() || table->at(hash).getKey() != key) {
		if (table->at(hash).isEmpty() && !table->at(hash).wasDeleted()) {
			return false;
		}
		
		hash+=1;
		hash%=size();
	}
	return true;
}

/*
 * insert
 * Inserts a node into the table using linear probing
 */
template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::insert(KeyType key, ValueType value) {
	
	// Check if key is already stored in table.
	if (keyIsInTable(key)) {
		throw DUPLICATE_KEY;
	}

	// Check if the table is getting too full.
	if (getLoadFactor() <= 0.5) {

		// Hash key to find its location in the table
		size_t hash = hash_function(key);
		// Store the original hash for future reference
		size_t origHash = hash;
	
	
		if (!table->at(hash).isEmpty()) {
			hash += 1;
			hash %= size();
		}
	
		// Look for an empty slot in the table
		while (!table->at(hash).isEmpty()) {
	
			if (hash == origHash) {
				cout << "Cannot find empty slot." << endl;
				throw EMPTY_SLOT_NOT_FOUND;
			}
	
			hash+=1;
			hash %= size();
		}

		// Update table with new key-value pair
		table->at(hash).assign(key, value);
	
		// Increase the numbers of keys stored by 1
		num++;
	}
	else {
		rehash(size()*2);
		insert(key, value);
	}
	
}

/*
 * erase
 * Removes key and associated data from table.
 */
template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::erase(KeyType key) {

	// Hash key to find where it is in the table
	size_t hash = hash_function(key);

	// Search table for key
	while (table->at(hash).getKey() != key) {
		if (table->at(hash).isEmpty() && !table->at(hash).wasDeleted()) {
			cout << "Key not found in erase" << endl;
			throw KEY_NOT_FOUND;
		}
	
		hash+=1;
		hash %= size();
	}
	
	// Erase the node
	table->at(hash).erase();
	
	num--;
}

/*
 * rehash
 * Sets a new size for the hash table
 * Rehashes the hash table
 */
template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::rehash(size_t size) {
	// Store pointer to old table
	Table* oldTable = table;
	
	try {
		// Create a new table
		table = new Table();
	
		// Fill new table with empty nodes
		for (int n = 0; n < static_cast<int>(size); n++) {
			HashNode<KeyType, ValueType>* node = new HashNode<KeyType, ValueType>;
			table->push_back(*node);
		}
	}
	catch (bad_alloc&) {
		throw OUT_OF_MEMORY;
	}
	
	num = 0;

	
	//size_t hash;
	KeyType key;
	ValueType value;
	// Copy each node to the new table
	for (int i = 0; i < static_cast<int>(oldTable->size()); i++) {
		
		// Don't bother copying empty nodes
		if (!(oldTable->at(i).isEmpty())) {
		
			// Store key and value from node to be copied
			key = oldTable->at(i).getKey();
			value = oldTable->at(i).getValue();
			
			// Insert into new table
			// The hash function will automatically change to
			// accomodate the new table size
			insert(key, value);
		}
	}
}

/*
 * getLoadFactor
 * Returns number of elements in table / size of table
 */
template <class KeyType, class ValueType>
double HashTable<KeyType, ValueType>::getLoadFactor() {
	double lf = static_cast<double>(num) / static_cast<double>(size());
	return lf;
}

/*
 * Sorts table in descending order and stores the sorted nodes in a vector.
 * Only the top n nodes will be stored.
 */
template<>
vector< HashNode<string, int> > HashTable<string, int>::sort(int n) {
    int maxValue;
    string maxKey;
    for (int i = 0; i < size(); i++) {
        if (!table->at(i).isEmpty() && table->at(i).getValue() > maxValue) {
            maxValue = table->at(i).getValue();
            maxKey = table->at(i).getKey();
        }
    }
}
#endif
