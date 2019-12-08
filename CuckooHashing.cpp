#include "CuckooHashing.h"
#include <iostream>
#include <math.h>
using namespace std;

CuckooHashing::CuckooHashing() {
	TABLE_SIZE = 5;
	rehashCounter = 0;
	hashTable1 = new CuckooBin * [TABLE_SIZE];
	hashTable2 = new CuckooBin * [TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashTable1[i] = NULL;
		hashTable2[i] = NULL;
	}
}

CuckooHashing::~CuckooHashing() {
	deleteTables();
}

int CuckooHashing::hashFunc1(int toHash) {
	return toHash % TABLE_SIZE;
}

int CuckooHashing::hashFunc2(int toHash) {
	return ((int)floor(toHash / TABLE_SIZE)) % TABLE_SIZE;
}

//insertHelper is here so that rehashing won't call itself if the new table size doesn't work
//returns false if we need to rehash
bool CuckooHashing::insertHelper(int toInsert) {
	int address1 = hashFunc1(toInsert);
	int address2 = hashFunc2(toInsert);
	if (hashTable1[address1] == NULL) {
		//we can put the value into the first hash table without collision
		hashTable1[address1] = new CuckooBin(toInsert, false);
		//cout << toInsert << " inserted at " << address1 << " in table 1" << "(address " << hashTable1[address1] << ")" << endl;
	}
	else if (hashTable2[address2] == NULL) {
		//we can put the value into the second hash table without collision
		hashTable2[address2] = new CuckooBin(toInsert, false);
		//cout << toInsert << " inserted at " << address2 << " in table 2" << endl;
	}
	else if (swap(address1, 1)) {
		//we can move the number at the first address without rehashing
		hashTable1[address1] = new CuckooBin(toInsert, false);
		//cout << toInsert << " inserted at " << address1 << " in table 1 after swapping the previous occupant" << endl;
	}
	else if (swap(address2, 2)) {
		//we can move the number at the second address without rehashing
		hashTable2[address2] = new CuckooBin(toInsert, false);
		//cout << toInsert << " inserted at " << address2 << " in table 2 after swapping the previous occupant" << endl;
	}
	else {
		//rehash :(
		return false;
	}
	return true;
}

void CuckooHashing::insert(int toInsert) {

	if (!insertHelper(toInsert)) {
		rehash(toInsert);
	}
}

void CuckooHashing::countRehashes() {
	cout << "Hash table has rehashed " << rehashCounter << " times." << endl;
}

void CuckooHashing::deleteValue(int toDelete) {
	//value will be at one of two locations
	int address1 = hashFunc1(toDelete);
	int address2 = hashFunc2(toDelete);
	if (hashTable1[address1] != NULL && hashTable1[address1]->value == toDelete) {
		//cout << "Deleting " << toDelete << " from " << address1 << " in table 1." << endl;
		delete hashTable1[address1];
		hashTable1[address1] = NULL;
	}
	else if (hashTable2[address2] != NULL && hashTable2[address2]->value == toDelete) {
		//cout << "Deleting " << toDelete << " from " << address2 << " in table 2." << endl;
		delete hashTable2[address2];
		hashTable2[address2] = NULL;
	}
	else {
		std::cout << "Error deleting value " << toDelete << ": value not found." << std::endl;
	}
}

bool CuckooHashing::lookup(int toLookup) {
	//value will be at one of two locations
	int address1 = hashFunc1(toLookup);
	int address2 = hashFunc2(toLookup);
	if (hashTable1[address1] != NULL && hashTable1[address1]->value == toLookup) {
		//std::cout << "Value found at index " << address1 << " in hash table 1." << std::endl;
		return true;
	}
	else if (hashTable2[address2] != NULL && hashTable2[address2]->value == toLookup) {
		//std::cout << "Value found at index " << address2 << " in hash table 2." << std::endl;
		return true;
	}
	else {
		std::cout << "Error looking up value " << toLookup << ": value not found." << std::endl;
		return false;
	}
}

void CuckooHashing::rehash(int toInsert) {
	//cout << "Rehashing..." << endl;
	CuckooBin** hashTable1Old = hashTable1;
	CuckooBin** hashTable2Old = hashTable2;
	int originalSize = TABLE_SIZE;
	bool toContinue;

	while (true) {
		//cout << "Incrementing table size" << endl;
		toContinue = false;
		TABLE_SIZE++;
		rehashCounter++;

		hashTable1 = new CuckooBin * [TABLE_SIZE];
		hashTable2 = new CuckooBin * [TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++) {
			hashTable1[i] = NULL;
			hashTable2[i] = NULL;
		}

		//insert new value
		insertHelper(toInsert);

		for (int i = 0; i < originalSize; i++) {
			if (hashTable1Old[i] != NULL) {
				if (!insertHelper(hashTable1Old[i]->value)) {
					//we need to up the table size, this size will not work
					toContinue = true;
					break;
				}
			}
			if (hashTable2Old[i] != NULL) {
				if (!insertHelper(hashTable2Old[i]->value)) {
					//we need to up the table size, this size will not work
					toContinue = true;
					break;
				}
			}
		}
		if (toContinue) {
			deleteTables();//prevents memory leak
			continue;
		}
		break;
	}

	delete hashTable1Old;
	delete hashTable2Old;
}

bool CuckooHashing::swap(int toSwapKey, int tableNum) {
	bool toReturn = swapHelper(toSwapKey, tableNum);
	markAllUnvisited();
	return toReturn;
}

//recursively swaps toSwapKey to its alternate slot, and if that one is full to its alternate, etc.
//originalKey will remain the same throughout the recursive callstack because we use it to identify infinite loops
bool CuckooHashing::swapHelper(int toSwapKey, int tableNum) {
	//cout << "Swapping with original key " << originalKey << ", original table " << originalTable << ", to swap key " << toSwapKey << ", and table num " << tableNum << endl;
	//cout << "Swapping " << toSwapKey << " in table " << tableNum;
	if (tableNum == 1) {
		hashTable1[toSwapKey]->visited = true;
		int toSwapToKey = hashFunc2(hashTable1[toSwapKey]->value);
		//cout << " to " << toSwapToKey << " in table 2" << endl;
		if (hashTable2[toSwapToKey] == NULL) {
			//swap
			hashTable2[toSwapToKey] = hashTable1[toSwapKey];
			return true;
		}
		else if (hashTable2[toSwapToKey]->visited == true) {
			//rehash
			return false;
		}
		else {
			//recurse
			//cout << "swap recursing" << endl;
			if (swapHelper(toSwapToKey, 2)) {
				hashTable2[toSwapToKey] = hashTable1[toSwapKey];
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		hashTable2[toSwapKey]->visited = true;
		int toSwapToKey = hashFunc1(hashTable2[toSwapKey]->value);
		//cout << " to " << toSwapToKey << " in table 1" << endl;
		if (hashTable1[toSwapToKey] == NULL) {
			//swap
			hashTable1[toSwapToKey] = hashTable2[toSwapKey];
			return true;
		}
		else if (hashTable1[toSwapToKey]->visited == true) {
			//rehash
			//cout << "Infinite loop found at " << toSwapToKey << "in table 1" << endl;
			return false;
		}
		else {
			//recurse
			//cout << "swap recursing" << endl;
			if (swapHelper(toSwapToKey, 1)) {
				hashTable1[toSwapToKey] = hashTable2[toSwapKey];
				return true;
			}
			else {
				return false;
			}
		}
	}
}

void CuckooHashing::markAllUnvisited() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable1[i] != NULL) {
			hashTable1[i]->visited = false;
		}
		if (hashTable2[i] != NULL) {
			hashTable2[i]->visited = false;
		}
	}
}

void CuckooHashing::printValues() {
	cout << "Printing values..." << endl;
	for (int i = 0; i < TABLE_SIZE; i++) {
		cout << "Line " << i << ": ";
		if (hashTable1[i] != NULL) {
			cout << hashTable1[i]->value;
		}
		else {
			cout << "_";
		}
		cout << " ";
		if (hashTable2[i] != NULL) {
			cout << hashTable2[i]->value << endl;
		}
		else {
			cout << "_" << endl;
		}
	}
	cout << "Done" << endl;
}

void CuckooHashing::deleteTables() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable1[i] != NULL) {
			delete hashTable1[i];
			hashTable1[i] = NULL;
		}
		if (hashTable2[i] != NULL) {
			delete hashTable2[i];
			hashTable2[i] = NULL;
		}
	}
	if (hashTable1 != NULL) {
		delete[] hashTable1;
	}
	if (hashTable2 != NULL) {
		delete[] hashTable2;
	}
}