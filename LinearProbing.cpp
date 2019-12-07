#include "LinearProbing.h"
#include <iostream>

LinearProbing::LinearProbing(int hashFunction) {
	TABLE_SIZE = 1019;
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
			std::cout << "Error inserting value: hash table full." << std::endl;
		}
	}
	hashTable[key] = &toInsert;

}

void LinearProbing::deleteValue(int toDelete) {
	int key = -1;
	if (hashFunc == 1) {
		key = hashFunc1(toDelete);
	}
	else {
		key = hashFunc2(toDelete);
	}

	if (*hashTable[key] == toDelete) {
		hashTable[key] = NULL;
		return;
	}

	int originalKey = key;

	//if we reach an empty bin (or the original location is empty), the value will not be found
	while (hashTable[key]!=NULL) {
		//increment the key and take the modulus of it to avoid inefficiency by having to compute the modulus of it in other steps
		key=(key+1)%TABLE_SIZE;

		//if we reach the original location, the value will not be found
		if (key==originalKey) {
			break;
		}

		//delete entry and return if found
		if (*hashTable[key] == toDelete) {
			hashTable[key] = NULL;
			return;
		}
	}

	std::cout << "Error deleting value: value not in table" << std::endl;

}

void LinearProbing::lookup(int toLookup) {

	int key = -1;
	if (hashFunc == 1) {
		key = hashFunc1(toLookup);
	}
	else {
		key = hashFunc2(toLookup);
	}

	if (*hashTable[key] == toLookup) {
		std::cout << "Value " << toLookup << " found at key " << key << std::endl;
		return;
	}

	int originalKey = key;

	//if we reach an empty bin (or the original location is empty), the value will not be found
	while (hashTable[key] != NULL) {
		//increment the key and take the modulus of it to avoid inefficiency by having to compute the modulus of it in other steps
		key = (key + 1) % TABLE_SIZE;

		//if we reach the original location, the value will not be found
		if (key == originalKey) {
			break;
		}

		//print and return if found
		if (*hashTable[key] == toLookup) {
			std::cout << "Value " << toLookup << " found at key " << key << std::endl;
			return;
		}
	}

	std::cout << "Error looking up value: value not in table" << std::endl;
}

int LinearProbing::hashFunc1(int toHash) {
	return toHash % TABLE_SIZE;
}

int LinearProbing::hashFunc2(int toHash) {
	return floor(toHash / TABLE_SIZE);
}