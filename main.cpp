#include<iostream>
#include<string>
#include <fstream>
#include <sstream>
#include "CuckooHashing.h"
#include "LinearProbing.h"
#include <chrono>
#include "LL.hpp"
#include "BST.hpp"

using namespace std;

void mainMenu() {
	cout << "Choose collision resolution method:" << endl;
	cout << "1. Chaining with LL" << endl;
	cout << "2. Chaining with BST" << endl;
	cout << "3. Linear Probing" << endl;
	cout << "4. Cuckoo Hashing" << endl;
	cout << "5. Quit" << endl;
}

void hashMenu() {
	cout << "Choose which hash function to implement:" << endl;
	cout << "1. x mod TABLE_SIZE" << endl;
	cout << "2. Floor(x/TABLE_SIZE) mod TABLE_SIZE" << endl;
}

void testLinearProbing(LinearProbing& hashTable, int tablesize, string filename, double loadFactor) {
	int num;
	string tmpNum;
	ifstream file(filename);

	int toDelete[100];

	//get load factor to 0.1
	int counter = 0;
	while (hashTable.loadFactor() < loadFactor) {
		getline(file, tmpNum, ',');
		num = stoi(tmpNum);
		toDelete[counter % 100] = num;
		hashTable.insert(num);
		counter++;
	}

	auto t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		hashTable.deleteValue(toDelete[i]);
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	auto durationDelete = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		getline(file, tmpNum, ',');
		num = stoi(tmpNum);
		toDelete[i] = num;
		hashTable.insert(num);
	}
	t2 = std::chrono::high_resolution_clock::now();
	auto durationInsert = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();


	t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100; i++) {
		hashTable.lookup(toDelete[i]);
	}
	t2 = std::chrono::high_resolution_clock::now();
	auto durationLookup = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	cout << "Linear probing at load factor " << loadFactor << ":" << endl;
	cout << "Delete 100 numbers: " << durationDelete << " microseconds." << endl;
	cout << "Insert 100 numbers: " << durationInsert << " microseconds." << endl;
	cout << "Lookup 100 numbers: " << durationLookup << " microseconds." << endl;
	cout << endl;
}

int main() {
	// prompt user to chosse which collision resolution method to use
	int mainChoice;
	int hashChoice;

	// read csv file
	/*int num;
	string tmpNum;
	ifstream file("dataSetA.csv");
	while (file.good()){
		getline(file,tmpNum,',');
		num = stoi(tmpNum);
		cout << num << endl;
	}*/

	// declare class for linked list implementation
	hashLL ll;

	while (true) {
		mainMenu();
		cin >> mainChoice;
		if (mainChoice == 1) {
			// prompt user to choose hash function to implement
			hashMenu();
			cin >> hashChoice;

			switch (hashChoice) {
				// x mod TABLE_SIZE
			case 1:

				break;

				// Floor(x/TABLE_SIZE) mod TABLE_SIZE
			case 2:

				break;
			}

			// chaining with BST
		}
		else if (mainChoice == 2) {
			// prompt user to choose hash function to implement
			hashMenu();

			cin >> hashChoice;

			switch (hashChoice) {
				// x mod TABLE_SIZE
			case 1:

				break;

				// Floor(x/TABLE_SIZE) mod TABLE_SIZE
			case 2:

				break;
			}

			// linear probing
		}
		else if (mainChoice == 3) {
			// prompt user to choose hash function to implement
			hashMenu();
			int tablesize = 10009;
			while (true) {
				cin >> hashChoice;
				if (hashChoice == 1) {
					LinearProbing hashTable = LinearProbing(1);
					testLinearProbing(hashTable, tablesize, "dataSetA.csv", 0.1);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, "dataSetA.csv", 0.2);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, "dataSetA.csv", 0.5);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, "dataSetA.csv", 0.7);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, "dataSetA.csv", 1);
					break;
				}
				else if (hashChoice == 2) {
					LinearProbing hashTable = LinearProbing(2);
					testLinearProbing(hashTable, tablesize, "dataSetA.csv", 0.1);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, "dataSetA.csv", 0.2);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, "dataSetA.csv", 0.5);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, "dataSetA.csv", 0.7);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, "dataSetA.csv", 1);
					break;
				}
				else {
					cout << "Invalid hash choice." << endl;
					hashMenu();
				}
			}
			// cuckoo hashing
		}
		else if (mainChoice == 4) {
			// uses both hash functions by definition
			CuckooHashing hashTable;
		}
		else if (mainChoice == 5) {
			cout << "Quitting..." << endl;
			return 0;
		}
		else {
			cout << "Please enter a number 1-5" << endl;
		}
	}
}




//cuckoo hashing test
/*
			int tablesize = 5;
			//fill up the table
			for (int i = 0; i < tablesize; i++) {
				hashTable.insert(i);
				hashTable.insert(i * tablesize + i);
			}

			//cause rehash
			hashTable.insert(tablesize*tablesize+tablesize);
			hashTable.countRehashes();

			hashTable.printValues();

			cout << "Deleting all values except " << tablesize*tablesize+tablesize << endl;
			for (int i = 0; i < tablesize; i++) {
				hashTable.deleteValue(i);
				hashTable.deleteValue(i * tablesize + i);
			}
			hashTable.printValues();
			hashTable.lookup(tablesize * tablesize + tablesize);*/