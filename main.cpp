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

void actionMenu() {
	cout << "Choose operation for hash table" << endl;
	cout << "1. Insert new entry" << endl;
	cout << "2. Lookup entry" << endl;
	cout << "3. Delete entry" << endl;
	cout << "4. Quit linked list implementation" << endl;
}

void testLinearProbing(LinearProbing& hashTable, int tablesize, string filename, double loadFactor) {
	int num;
	string tmpNum;
	ifstream file(filename);

	int toDelete[100];

	int counter = 0;
	while (hashTable.loadFactor() < loadFactor) {
		getline(file, tmpNum, ',');
		num = stoi(tmpNum);
		toDelete[counter % 100] = num;
		hashTable.insert(num);
		counter++;
	}
	cout << counter << " numbers inserted to bring load factor to " << loadFactor << endl;

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

void testCuckooHashing(CuckooHashing& hashTable, int tablesize, string filename, double loadFactor) {
	int num;
	string tmpNum;
	ifstream file(filename);

	int toDelete[100];

	//get load factor to desired value
	int counter = 0;
	while (((double)counter) < 2 * loadFactor * ((double)tablesize)) { //we multiply table size by 2 to account for both sides
		getline(file, tmpNum, ',');
		num = stoi(tmpNum);
		toDelete[counter % 100] = num;
		hashTable.insert(num);
		counter++;
	}
	cout << counter << " numbers inserted to bring load factor to " << loadFactor << endl;

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

	cout << "Cuckoo hashing at load factor " << loadFactor << ":" << endl;
	cout << "Delete 100 numbers: " << durationDelete << " microseconds." << endl;
	cout << "Insert 100 numbers: " << durationInsert << " microseconds." << endl;
	cout << "Lookup 100 numbers: " << durationLookup << " microseconds." << endl;
	hashTable.countRehashes();
	cout << endl;
}

int main(int argc, char* argv[]) {
	// command line args
	string filename = argv[1];
	string tmpHashChoice = argv[2];
	int hashChoice = stoi(tmpHashChoice);
	if (hashChoice > 2 || hashChoice < 1) {
		cout << "Please enter 1 or 2 as second argument" << endl;
		return 0;
	}
	// class for linked list implementation
  hashLL ll;
	// class for BST implementation
  hashBST bst;

	// initialize variables for user input
  int mainChoice;
	int actionChoice;
	int toInsert;
	int toLookup;
	int toDelete;

	while (true) {
		// prompt user to choose collision resolution method
		mainMenu();
		cin >> mainChoice;

		// chaining with linked list
		if (mainChoice == 1) {
			// read csv file
			int num;
			string tmpNum;
			ifstream file(filename);
			if (!file.is_open())
				cout << "failed to open file" << endl << "\n";

			//int i = 0;
			while (file.good()){
				getline(file,tmpNum,',');
				num = stoi(tmpNum);
				// insert into hash table
				//i++;
				//cout << "inserting: " << i << "th element" << endl;
				ll.insertLL(num, hashChoice);
			}
			cout << "done populating hash table" << endl << "\n";

			// hash table is now populated, ask user for action
			int quit = 0;
			while (quit == 0) {
				actionMenu();
				cin >> actionChoice;
				// insert new entry
				if (actionChoice == 1) {
					cout << "Enter value to insert into hash table: " << endl;
					cout << ">> ";
					cin >> toInsert;
					ll.insertLL(toInsert, hashChoice);
				}
				// lookup entry
				else if (actionChoice == 2) {
					cout << "Enter value to lookup" << endl;
					cout << ">> ";
					cin >> toLookup;
					ll.lookupLL(toLookup, hashChoice);
				}
				else if (actionChoice == 3) {
					cout << "Enter value to delete" << endl;
					cout << ">> ";
					cin >> toDelete;
					ll.deleteLL(toDelete, hashChoice);
				}
				else if (actionChoice == 4) {
					quit++;
					cout << "quitting action menu" << endl << "\n";
				}
			}
		}

		// chaining with BST
		else if (mainChoice == 2) {
			// read csv file
			int num;
			string tmpNum;
			ifstream file(filename);
			if (!file.is_open())
				cout << "failed to open file" << endl << "\n";

			//int i = 0;
			while (file.good()){
				getline(file,tmpNum,',');
				num = stoi(tmpNum);
				// insert into hash table
				//i++;
				//cout << "inserting: " << i << "th element" << endl;
				bst.insertBST(num, hashChoice);
			}
			cout << "done populating hash table" << endl << "\n";

			// hash table is now populated, ask user for action
			int quit = 0;
			while (quit == 0) {
				actionMenu();
				cin >> actionChoice;
				// insert new entry
				if (actionChoice == 1) {
					cout << "Enter value to insert into hash table: " << endl;
					cout << ">> ";
					cin >> toInsert;
					bst.insertBST(toInsert, hashChoice);
				}
				// lookup entry
				else if (actionChoice == 2) {
					cout << "Enter value to lookup" << endl;
					cout << ">> ";
					cin >> toLookup;
					bst.lookupBST(toLookup, hashChoice);
				}
				else if (actionChoice == 3) {
					cout << "Enter value to delete" << endl;
					cout << ">> ";
					cin >> toDelete;
					bst.deleteBST(toDelete, hashChoice);
				}
				else if (actionChoice == 4) {
					quit++;
					cout << "quitting action menu" << endl << "\n";
				}
			}
		}

		// linear probing
		else if (mainChoice == 3) {
			// prompt user to choose hash function to implement

			int tablesize = 10009;
			while (true) {
				cin >> hashChoice;
				if (hashChoice == 1) {
					string filename = "dataSetA.csv";
					LinearProbing hashTable = LinearProbing(1, tablesize);
					testLinearProbing(hashTable, tablesize, filename, 0.1);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, filename, 0.2);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, filename, 0.5);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, filename, 0.7);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, filename, 1);
					break;
				}
				else if (hashChoice == 2) {
					string filename = "dataSetA.csv";
					LinearProbing hashTable = LinearProbing(2, tablesize);
					testLinearProbing(hashTable, tablesize, filename, 0.1);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, filename, 0.2);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, filename, 0.5);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, filename, 0.7);
					hashTable.clearTable();

					testLinearProbing(hashTable, tablesize, filename, 1);
					break;
				}
				else {
					cout << "Invalid hash choice." << endl;
					//hashMenu();
				}
			}
			// cuckoo hashing
		}
		else if (mainChoice == 4) {
			// uses both hash functions by definition
			int tablesize = 10009;
			CuckooHashing hashTable(tablesize);
			string filename = "dataSetA.csv";
			testCuckooHashing(hashTable, tablesize, filename, 0.1);
			hashTable.clearTables();

			testCuckooHashing(hashTable, tablesize, filename, 0.2);
			hashTable.clearTables();

			testCuckooHashing(hashTable, tablesize, filename, 0.5);
			hashTable.clearTables();

			testCuckooHashing(hashTable, tablesize, filename, 0.7);
			hashTable.clearTables();

			testCuckooHashing(hashTable, tablesize, filename, 1);
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
