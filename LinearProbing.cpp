#include "LinearProbing.h"
#include <iostream>
using namespace std;

LinearProbing::LinearProbing(int hashFunction) {
	TABLE_SIZE = 10009;
	hashFunc = hashFunction;
	hashTable = new int* [TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashTable[i] = NULL;
	}
}

LinearProbing::~LinearProbing() {
	delete hashTable;
}

void LinearProbing::insert(int toInsert) {
	cout << "Adding " << toInsert << endl;
	int key = -1;
	if (hashFunc == 1) {
		key = hashFunc1(toInsert);
	}
	else {
		key = hashFunc2(toInsert);
	}
	int originalKey = key;
	while (hashTable[key] != NULL) {
		key = (key + 1) % TABLE_SIZE;
		if (key == originalKey) {
			cout << "Error inserting value: hash table full." << endl;
			return;
		}
	}
	hashTable[key] = &toInsert;
	cout << "Added at " << key << "." << endl;

}

void LinearProbing::deleteValue(int toDelete) {
	cout << "Deleting " << toDelete << endl;
	int key = -1;
	if (hashFunc == 1) {
		key = hashFunc1(toDelete);
	}
	else {
		key = hashFunc2(toDelete);
	}

	if (hashTable[key] != NULL && *hashTable[key] == toDelete) {
		hashTable[key] = NULL;
		cout << "Deleted from " << key << "." << endl;
		return;
	}

	int originalKey = key;
	key = (key + 1 % TABLE_SIZE);

	//if we reach the original location, the value will not be found
	while (key != originalKey) {
		//print and return if found
		if (hashTable[key] != NULL && *hashTable[key] == toDelete) {
			hashTable[key] = NULL;
			cout << "Value " << toDelete << " deleted from key " << key << endl;
			return;
		}
		//increment the key
		key = (key + 1) % TABLE_SIZE;
	}

	cout << "Error deleting value: value not in table" << endl;

}

void LinearProbing::lookup(int toLookup) {

	int key = -1;
	if (hashFunc == 1) {
		key = hashFunc1(toLookup);
	}
	else {
		key = hashFunc2(toLookup);
	}

	if (hashTable[key] != NULL && *hashTable[key] == toLookup) {
		cout << "Value " << toLookup << " found at key " << key << endl;
		return;
	}

	int originalKey = key;
	key = (key + 1 % TABLE_SIZE);

	//if we reach the original location, the value will not be found
	while (key!=originalKey) {
		//print and return if found
		if (hashTable[key]!=NULL && *hashTable[key] == toLookup) {
			cout << "Value " << toLookup << " found at key " << key << endl;
			return;
		}
		//increment the key
		key = (key + 1) % TABLE_SIZE;
	}

	cout << "Error looking up value: value not in table" << endl;
}

int LinearProbing::hashFunc1(int toHash) {
	return toHash % TABLE_SIZE;
}

int LinearProbing::hashFunc2(int toHash) {
	return floor(toHash / TABLE_SIZE);
}