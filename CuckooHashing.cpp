#include "CuckooHashing.h"
#include <iostream>
#include <math.h>
using namespace std;

//checks if a number is prime (used in rehashing to find new table size)
bool isPrime(int N) {
	//check if N is even
	if (N % 2 == 0) {
		return false;
	}

	//now check if i is divisible by any odd number less than half of it 
	//since N will never be divisible by 2 once we get here, we don't need to check N/2
	for (int i = 3; i < ((double)N) / 2; i += 2) {
		if (N % i == 0) {
			return false;
		}
	}
	return true;
}

//constructor initializes all the necessary components of the cuckoo hash table
CuckooHashing::CuckooHashing(int tablesize) {
	TABLE_SIZE = tablesize;
	TABLE_SIZE_INCREMENT = (int)(((double)TABLE_SIZE) * 0.1); //arbitrary number, other values may make performance better or worse
	rehashCounter = 0;
	hashTable1 = new CuckooBin * [TABLE_SIZE];
	hashTable2 = new CuckooBin * [TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++) {
		hashTable1[i] = NULL;
		hashTable2[i] = NULL;
	}
}

//counts the number of entries in the tables
int CuckooHashing::numEntries() {
	int toReturn = 0;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable1[i] != NULL) {
			toReturn++;
		}
		if (hashTable2[i] != NULL) {
			toReturn++;
		}
	}
	return toReturn;
}

//clears the tables of data without deleting them entirely (useful for debugging)
void CuckooHashing::clearTables() {
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
}

CuckooHashing::~CuckooHashing() {
	deleteTables(); //tables are the only dynamically allocated memory so we only need to delete them
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

	//get the two addresses it could be at
	int address1 = hashFunc1(toInsert);
	int address2 = hashFunc2(toInsert);


	//cannot insert existing number
	if (hashTable1[address1] != NULL && hashTable1[address1]->value == toInsert) {
		return true;
	}
	if (hashTable2[address2] != NULL && hashTable2[address2]->value == toInsert) {
		return true;
	}

	if (hashTable1[address1] == NULL) {
		//we can put the value into the first hash table without collision
		hashTable1[address1] = new CuckooBin(toInsert, false);
	}
	else if (hashTable2[address2] == NULL) {
		//we can put the value into the second hash table without collision
		hashTable2[address2] = new CuckooBin(toInsert, false);
	}
	else if (swap(address1, 1)) {
		//we can move the number at the first address without rehashing
		hashTable1[address1] = new CuckooBin(toInsert, false);
	}
	else if (swap(address2, 2)) {
		//we can move the number at the second address without rehashing
		hashTable2[address2] = new CuckooBin(toInsert, false);
	}
	else {
		//rehash :(
		return false;
	}
	return true;
}

//wrapper for insertHelper, calls rehash if insert fails with current tables
void CuckooHashing::insert(int toInsert) {

	if (!insertHelper(toInsert)) {
		//if the insert fails, we need to rehash
		rehash(toInsert);
	}
}

//prints out how many rehashes have ocurred
void CuckooHashing::countRehashes() {
	cout << "Cuckoo hash table has rehashed " << rehashCounter << " times." << endl;
}

//deletes a value from the tables
void CuckooHashing::deleteValue(int toDelete) {
	//value will be at one of two locations
	int address1 = hashFunc1(toDelete);
	int address2 = hashFunc2(toDelete);

	if (hashTable1[address1] != NULL && hashTable1[address1]->value == toDelete) {
		delete hashTable1[address1];
		hashTable1[address1] = NULL;
	}
	else if (hashTable2[address2] != NULL && hashTable2[address2]->value == toDelete) {
		delete hashTable2[address2];
		hashTable2[address2] = NULL;
	}
	else {
		std::cout << "Error deleting value " << toDelete << ": value not found." << std::endl;
	}
}

//looks up a value and returns true if found, false otherwise
bool CuckooHashing::lookup(int toLookup) {
	//value will be at one of two locations
	int address1 = hashFunc1(toLookup);
	int address2 = hashFunc2(toLookup);

	if (hashTable1[address1] != NULL && hashTable1[address1]->value == toLookup) {
		//we found it
		return true;
	}
	else if (hashTable2[address2] != NULL && hashTable2[address2]->value == toLookup) {
		//we found it
		return true;
	}
	else {
		std::cout << "Error looking up value " << toLookup << ": value not found." << std::endl;
		return false;
	}
}

//resizes the tables to new sizes after a value that cannot fit is inserted
void CuckooHashing::rehash(int toInsert) {

	//copy current tables over to variables while they are resized
	CuckooBin** hashTable1Old = hashTable1;
	CuckooBin** hashTable2Old = hashTable2;
	int originalSize = TABLE_SIZE;
	
	bool toContinue;

	while (true) {
		toContinue = false;

		//find new table size
		TABLE_SIZE += TABLE_SIZE_INCREMENT;
		if (TABLE_SIZE % 2 == 0) {
			TABLE_SIZE++;
		}
		//increment table size by 2 (since evens aren't prime) until we reach another prime
		while (!isPrime(TABLE_SIZE)) {
			TABLE_SIZE += 2;
		}

		//increment the rehash counter since we are trying to rehash
		rehashCounter++;

		//create new tables and initialize them empty
		hashTable1 = new CuckooBin * [TABLE_SIZE];
		hashTable2 = new CuckooBin * [TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++) {
			hashTable1[i] = NULL;
			hashTable2[i] = NULL;
		}

		//insert new value
		insertHelper(toInsert);

		//try to insert all the values from the old array to the new one. if it won't work, we increase the size again
		for (int i = 0; i < originalSize; i++) {
			if (hashTable1Old[i] != NULL) {
				if (!(insertHelper(hashTable1Old[i]->value))) {
					//we need to up the table size, this size will not work
					toContinue = true;
					break;
				}
			}
			if (hashTable2Old[i] != NULL) {
				if (!(insertHelper(hashTable2Old[i]->value))) {
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
	
	//everything is copied over so we can delete the old tables
	delete[] hashTable1Old;
	delete[] hashTable2Old;
}

//main function for swapping, begins recursive swapHelper call and then calls markAllUnvisited before returning the swapHelper return value
bool CuckooHashing::swap(int toSwapKey, int tableNum) {
	bool toReturn = swapHelper(toSwapKey, tableNum);
	markAllUnvisited();
	return toReturn;
}

//recursively swaps toSwapKey to its alternate slot, and if that one is full to its alternate, etc.
//we use visited to identify infinite loops
bool CuckooHashing::swapHelper(int toSwapKey, int tableNum) {
	if (tableNum == 1) {
		hashTable1[toSwapKey]->visited = true; //mark the current value as visited

		int toSwapToKey = hashFunc2(hashTable1[toSwapKey]->value);//location we are going to swap to in table 2

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
			if (swapHelper(toSwapToKey, 2)) {
				//if the recursive swapHelper call returns true we can swap now
				hashTable2[toSwapToKey] = hashTable1[toSwapKey]; 
				return true;
			}
			else {
				//otherwise we cannot swap
				return false;
			}
		}
	}
	else {
		//set this bucket to visited
		hashTable2[toSwapKey]->visited = true; //mark the current value as visited

		int toSwapToKey = hashFunc1(hashTable2[toSwapKey]->value);//location we are going to swap to in table 2

		if (hashTable1[toSwapToKey] == NULL) {
			//swap
			hashTable1[toSwapToKey] = hashTable2[toSwapKey];
			return true;
		}
		else if (hashTable1[toSwapToKey]->visited == true) {
			//rehash
			return false;
		}
		else {
			//recurse
			if (swapHelper(toSwapToKey, 1)) {
				//if the recursive swapHelper call returns true we can swap now
				hashTable1[toSwapToKey] = hashTable2[toSwapKey];
				return true;
			}
			else {
				//otherwise we cannot swap
				return false;
			}
		}
	}
}

//marks all values in both tables unvisited (called by swap after swapHelper to reset state of all values)
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

//prints all values in the tables (useful for debugging)
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

//deletes all values in both tables, then deletes the tables themselves. 
//called by destructor and rehash function
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
