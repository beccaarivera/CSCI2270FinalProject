#include "CuckooHashing.h"
#include <iostream>
#include "math.h"


CuckooHashing::CuckooHashing() {
	TABLE_SIZE = 10009;
	rehashCounter = 0;
	hashTable1 = new int* [TABLE_SIZE];
	hashTable2 = new int* [TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashTable1[i] = NULL;
		hashTable2[i] = NULL;
	}
}

CuckooHashing::~CuckooHashing() {
	delete hashTable1;
	delete hashTable2;
}

int CuckooHashing::hashFunc1(int toHash) {
	return toHash % TABLE_SIZE;
}

int CuckooHashing::hashFunc2(int toHash) {
	return floor(toHash / TABLE_SIZE);
}

//insertHelper is here so that rehashing won't call itself if the new table size doesn't work
//returns true if we need to rehash
bool CuckooHashing::insertHelper(int toInsert) {
	int address1 = hashFunc1(toInsert);
	int address2 = hashFunc2(toInsert);
	if (hashTable1[address1] == NULL) {
		//we can put the value into the first hash table without collision
		hashTable1[address1] = &toInsert;
	}
	else if (hashTable2[address2] == NULL) {
		//we can put the value into the second hash table without collision
		hashTable2[address2] = &toInsert;
	}
	else if (swap(address1, address1, 1)) {
		//we can move the number at the first address without rehashing
		hashTable1[address1] = &toInsert;
	}
	else if (swap(address2, address2, 2)) {
		//we can move the number at the second address without rehashing
		hashTable2[address2] = &toInsert;
	}
	else {
		//rehash :(
		rehashCounter++;
		return true;
	}
	return false;
}


void CuckooHashing::insert(int toInsert) {
	if (insertHelper(toInsert)) {
		rehash();
	}
}

void CuckooHashing::deleteValue(int toDelete) {
	//value will be at one of two locations
	int address1 = hashFunc1(toDelete);
	int address2 = hashFunc2(toDelete);
	if (*hashTable1[address1] == toDelete) {
		hashTable1[address1] = NULL;
	}
	else if (*hashTable2[address2] == toDelete) {
		hashTable2[address2] = NULL;
	}
	else {
		std::cout << "Error deleting value " << toDelete << ": value not found." << std::endl;
	}

}

void CuckooHashing::lookup(int toLookup) {
	//value will be at one of two locations
	int address1 = hashFunc1(toLookup);
	int address2 = hashFunc2(toLookup);
	if (*hashTable1[address1] == toLookup) {
		std::cout << "Value found at index " << address1 << " in hash table 1." << std::endl;
	}
	else if (*hashTable2[address2] == toLookup) {
		std::cout << "Value found at index " << address2 << " in hash table 2." << std::endl;
	}
	else {
		std::cout << "Error looking up value " << toLookup << ": value not found." << std::endl;
	}
}


void CuckooHashing::rehash() {
	int** hashTable1Old = hashTable1;
	int** hashTable2Old = hashTable2;
	int originalSize = TABLE_SIZE;
	bool success = false;

	while (true) {
		TABLE_SIZE++;

		hashTable1 = new int* [TABLE_SIZE];
		hashTable2 = new int* [TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++) {
			hashTable1[i] = NULL;
			hashTable2[i] = NULL;
		}

		for (int i = 0; i < originalSize; i++) {
			if (hashTable1[i] != NULL) {
				if (insertHelper(*hashTable1[i])) {
					//we need to up the table size, this size will not work
					continue;
				}
			}

			if (hashTable2[i] != NULL) {
				if (insertHelper(*hashTable2[i])) {
					//we need to up the table size, this size will not work
					continue;
				}
			}
		}
		break;
	}

	delete hashTable1Old;
	delete hashTable2Old;
}

//recursively swaps toSwapKey to its alternate slot, and if that one is full to its alternate, etc.
//originalKey will remain the same throughout the recursive callstack because we use it to identify infinite loops
bool CuckooHashing::swap(int originalKey, int toSwapKey, int tableNum) {
	if (tableNum == 1) {
		int toSwapToKey = hashFunc2(*hashTable1[toSwapKey]);
		if (hashTable2[toSwapToKey] == NULL) {
			//swap
			hashTable2[toSwapToKey] = &*hashTable1[toSwapKey];
			return true;
		}
		else if (toSwapToKey == originalKey) {
			//rehash
			return false;
		}
		else {
			//recurse
			if (swap(originalKey, toSwapToKey, 2)) {
				hashTable2[toSwapToKey] = &*hashTable1[toSwapKey];
			}
			else {
				return false;
			}
		}
	}
	else {
		int toSwapToKey = hashFunc1(*hashTable2[toSwapKey]);
		if (hashTable1[toSwapToKey] == NULL) {
			//swap
			hashTable1[toSwapToKey] = &*hashTable2[toSwapKey];
			return true;
		}
		else if (toSwapToKey == originalKey) {
			//rehash
			return false;
		}
		else {
			//recurse
			if (swap(originalKey, toSwapToKey, 1)) {
				hashTable1[toSwapToKey] = &*hashTable2[toSwapKey];
			}
			else {
				return false;
			}
		}
	}
}
