#ifndef MY_HASH_NODE
#define MY_HASH_NODE

using namespace std;

template <class KeyType, class ValueType>
class HashNode {
  KeyType key;     // The hash node's key
  ValueType value; // The key's associated data

  /* extend if necessary */
  bool empty;
  bool deleted;

public:

  HashNode();  // constructor

  KeyType getKey() { return key; }
  ValueType getValue() { return value; }
  void assign(KeyType key, ValueType value); 

  // extend if necessary

  bool isEmpty();
  void erase();
  bool wasDeleted();
  
};

/* 
   Implement the constructor, the assign method 
   and any methods that you may additionally need for the HashTable to work.
*/

template <class KeyType, class ValueType>
HashNode<KeyType, ValueType>::HashNode() {
	empty = true;
	deleted = false;
}

/*
 *Assign values to key and value fields
 */
template <class KeyType, class ValueType>
void HashNode<KeyType, ValueType>::assign(KeyType key, ValueType value) {
	this->key = key;
	this->value = value;
	empty = false;
}

/*
 * Accessor method for empty field
 */
template <class KeyType, class ValueType>
bool HashNode<KeyType, ValueType>::isEmpty() {
	return empty;
}

/*
 * Accessor method for deleted field
 */
template <class KeyType, class ValueType>
bool HashNode<KeyType, ValueType>::wasDeleted() {
	return deleted;
}

/*
 * Deletes node
 */
template <class KeyType, class ValueType>
void HashNode<KeyType, ValueType>::erase() {
	empty = true;
	deleted = true;
}


#endif
