#include "LinearProbing.h"
#include <iostream>
#include "math.h"
using namespace std;

LinearProbing::LinearProbing(int hashFunction, int tablesize) {
	//initialize the hash function we will use and table size based on what was passed into the constructor
	TABLE_SIZE = tablesize;
	hashFunc = hashFunction;
	hashTable = new int* [TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashTable[i] = NULL;
	}
}

LinearProbing::~LinearProbing() {
	//delete all dynamic memory
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] != NULL) {
			delete hashTable[i];
			hashTable[i] = NULL;
		}
	}
	if (hashTable != NULL) {
		delete[] hashTable;
	}
}

//clears the tables without deleting them
void LinearProbing::clearTable() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] != NULL) {
			delete hashTable[i];
			hashTable[i] = NULL;
		}
	}
}

//function for inserting a value
void LinearProbing::insert(int toInsert) {
	int key = -1;

	//get the key based on which hash function we are using
	if (hashFunc == 1) {
		key = hashFunc1(toInsert);
	}
	else {
		key = hashFunc2(toInsert);
	}

	//if the original key isn't available, we will loop through until we find an available bin or we reach the original location
	int originalKey = key;
	while (hashTable[key] != NULL) {
		key = (key + 1) % TABLE_SIZE;
		if (key == originalKey) {
			//if it is full we return and print an error to avoid overwriting something
			cout << "Error inserting value: hash table full." << endl; 
			return;
		}
	}
	hashTable[key] = new int(toInsert);

}

//deletes a value from the 
void LinearProbing::deleteValue(int toDelete) {
	int key = -1;

	//get the key based on which hash function we are using
	if (hashFunc == 1) {
		key = hashFunc1(toDelete);
	}
	else {
		key = hashFunc2(toDelete);
	}

	//if it is in its default slot, delete it and return
	if (hashTable[key] != NULL && *hashTable[key] == toDelete) {
		delete hashTable[key];
		hashTable[key] = NULL;
		return;
	}

	int originalKey = key;
	key = (key + 1 % TABLE_SIZE);

	//if we reach the original location, the value will not be found
	while (key != originalKey) {

		//print and return if found
		if (hashTable[key] != NULL && *hashTable[key] == toDelete) {
			delete hashTable[key];
			hashTable[key] = NULL;
			return;
		}

		//increment the key and check again
		key = (key + 1) % TABLE_SIZE;
	}

	cout << "Error deleting value: value not in table" << endl;

}

bool LinearProbing::lookup(int toLookup) {
	int key = -1;

	//get the key based on which hash function we are using
	if (hashFunc == 1) {
		key = hashFunc1(toLookup);
	}
	else {
		key = hashFunc2(toLookup);
	}

	//we found it at its default location
	if (hashTable[key] != NULL && *hashTable[key] == toLookup) {
		return true;
	}

	int originalKey = key;
	key = (key + 1 % TABLE_SIZE);

	//if we reach the original location, the value will not be found
	while (key != originalKey) {

		//print and return if found
		if (hashTable[key] != NULL && *hashTable[key] == toLookup) {
			return true;
		}

		//increment the key and check again
		key = (key + 1) % TABLE_SIZE;
	}

	cout << "Error looking up value: value not in table" << endl;
	return false;
}

int LinearProbing::hashFunc1(int toHash) {
	return toHash % TABLE_SIZE;
}

int LinearProbing::hashFunc2(int toHash) {
	return ((int)floor(toHash / TABLE_SIZE)) % TABLE_SIZE;
}

//calculates the current load factor of the table (useful for data gathering)
double LinearProbing::loadFactor() {
	int numFilled = 0;

	//iterate over array and count how many aren't null
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] != NULL) {
			numFilled++;
		}
	}

	//return the number filled over the table size
	return (((double)numFilled) / ((double)TABLE_SIZE));
}