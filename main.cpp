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

//tests linear probing hash table with given hash table, tablesize, filename of data, and at the given load factor
void testLinearProbing(LinearProbing& hashTable, int tablesize, string filename, double loadFactor) {
	int num;
	string tmpNum;
	ifstream file(filename);

	int toDelete[100];
	int times[100];

	int counter = 0;
	while (hashTable.loadFactor() < loadFactor) {
		getline(file, tmpNum, ',');
		num = stoi(tmpNum);
		toDelete[counter % 100] = num;
		hashTable.insert(num);
		counter++;
	}
	cout << counter << " numbers inserted to bring load factor to " << loadFactor << endl;

	//delete 100 values and record the time each takes
	for (int i = 0; i < 100; i++) {
		auto t1 = std::chrono::high_resolution_clock::now();
		hashTable.deleteValue(toDelete[i]);
		auto t2 = std::chrono::high_resolution_clock::now();
		times[i] = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	}
	double deleteMean = 0;
	double delete_stddev = 0;
	int totalTime = 0;

	//calculate mean
	for (int i = 0; i < 100; i++) {
		totalTime += times[i];
	}
	deleteMean = ((double)totalTime) / 100.0;

	//calculate std dev
	for (int i = 0; i < 100; i++) {
		delete_stddev += pow(((double)times[i]) - deleteMean,2);
	}
	delete_stddev /= 99;

	//insert 100 values and record the time each takes
	for (int i = 0; i < 100; i++) {
		getline(file, tmpNum, ',');
		num = stoi(tmpNum);
		toDelete[i] = num;
		auto t1 = std::chrono::high_resolution_clock::now();
		hashTable.insert(num);
		auto t2 = std::chrono::high_resolution_clock::now();
		times[i] = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	}
	double insertMean = 0;
	double insert_stddev = 0;
	totalTime = 0;
	
	//calculate mean
	for (int i = 0; i < 100; i++) {
		totalTime += times[i];
	}
	insertMean = ((double)totalTime) / 100.0;

	//calculate std dev
	for (int i = 0; i < 100; i++) {
		insert_stddev += pow(((double)times[i]) - deleteMean, 2);
	}
	insert_stddev /= 99;

	//lookup 100 values and record the time each takes
	for (int i = 0; i < 100; i++) {
		auto t1 = std::chrono::high_resolution_clock::now();
		hashTable.lookup(toDelete[i]);
		auto t2 = std::chrono::high_resolution_clock::now();
		times[i] = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	}
	double lookupMean = 0;
	double lookup_stddev = 0;
	totalTime = 0;

	//calculate mean
	for (int i = 0; i < 100; i++) {
		totalTime += times[i];
	}
	lookupMean = ((double)totalTime) / 100.0;

	//calculate std dev
	for (int i = 0; i < 100; i++) {
		lookup_stddev += pow(((double)times[i]) - deleteMean, 2);
	}
	lookup_stddev /= 99;

	cout << "Linear probing at load factor " << loadFactor << ":" << endl;
	cout << "Average delete time: " << deleteMean << " microseconds with " << delete_stddev << " microseconds standard deviation ." << endl;
	cout << "Average insert time: " << insertMean << " microseconds with " << insert_stddev << " microseconds standard deviation ." << endl;
	cout << "Average lookup time: " << lookupMean << " microseconds with " << lookup_stddev << " microseconds standard deviation ." << endl;
	cout << endl;
}

//tests cuckoo hash table with given hash table, tablesize, filename of data, and at the given load factor
void testCuckooHashing(CuckooHashing& hashTable, int tablesize, string filename, double loadFactor) {
	int num;
	string tmpNum;
	ifstream file(filename);

	int toDelete[100];
	int times[100];

	//get load factor to desired value
	int counter = 0;

	//read in data until desired load factor is reached
	while (hashTable.numEntries() < 2 * loadFactor * ((double)tablesize)) { //we multiply table size by 2 to account for both sides
		if (!file.good()) {
			//prevent error by ensuring the file is still good
			cout << "Reached end of file." << endl;
			return;
		}
		getline(file, tmpNum, ',');
		num = stoi(tmpNum);
		toDelete[counter % 100] = num;
		hashTable.insert(num);
		counter++;

	}
	//delete 100 entries and record each time it takes
	for (int i = 0; i < 100; i++) {
		auto t1 = std::chrono::high_resolution_clock::now();
		hashTable.deleteValue(toDelete[i]);
		auto t2 = std::chrono::high_resolution_clock::now();
		times[i] = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	}

	double deleteMean = 0;
	double delete_stddev = 0;
	int totalTime = 0;

	//calculate mean
	for (int i = 0; i < 100; i++) {
		totalTime += times[i];
	}
	deleteMean = ((double)totalTime) / 100.0;

	//calculate std dev
	for (int i = 0; i < 100; i++) {
		delete_stddev += pow(((double)times[i]) - deleteMean, 2);
	}
	delete_stddev /= 99;

	//insert 100 entries and record each time it takes
	for (int i = 0; i < 100; i++) {
		getline(file, tmpNum, ',');
		num = stoi(tmpNum);
		toDelete[i] = num;

		auto t1 = std::chrono::high_resolution_clock::now();
		hashTable.insert(num);
		auto t2 = std::chrono::high_resolution_clock::now();
		times[i] = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	}
	double insertMean = 0;
	double insert_stddev = 0;
	totalTime = 0;

	//calculate mean
	for (int i = 0; i < 100; i++) {
		totalTime += times[i];
	}
	insertMean = ((double)totalTime) / 100.0;

	//calculate std dev
	for (int i = 0; i < 100; i++) {
		insert_stddev += pow(((double)times[i]) - insertMean, 2);
	}
	insert_stddev /= 99;


	//lookup 100 entries and record each time it takes
	for (int i = 0; i < 100; i++) {
		auto t1 = std::chrono::high_resolution_clock::now();
		hashTable.lookup(toDelete[i]);
		auto t2 = std::chrono::high_resolution_clock::now();
		times[i] = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	}
	double lookupMean = 0;
	double lookup_stddev = 0;
	totalTime = 0;

	//calculate mean
	for (int i = 0; i < 100; i++) {
		totalTime += times[i];
	}
	lookupMean = ((double)totalTime) / 100.0;

	//calculate stddev
	for (int i = 0; i < 100; i++) {
		lookup_stddev += pow(((double)times[i]) - lookupMean, 2);
	}
	lookup_stddev /= 99;

	cout << "Cuckoo hashing at load factor " << loadFactor << ":" << endl;
	cout << "Average delete time: " << deleteMean << " microseconds with " << delete_stddev << " microseconds standard deviation ." << endl;
	cout << "Average insert time: " << insertMean << " microseconds with " << insert_stddev << " microseconds standard deviation ." << endl;
	cout << "Average lookup time: " << lookupMean << " microseconds with " << lookup_stddev << " microseconds standard deviation ." << endl;
	hashTable.countRehashes();
	cout << endl;
}


//tests linear probing hash table with given hash table, tablesize, filename of data, and at the given load factor
void testBST(hashBST& hashTable, int tablesize, string filename, double loadFactor) {
	int num;
	string tmpNum;
	ifstream file(filename);

	int toDelete[100];
	int times[100];

	int counter = 0;
	while (counter <  ceil(((double) tablesize)*((double)loadFactor))) {
		getline(file, tmpNum, ',');
		num = stoi(tmpNum);
		toDelete[counter % 100] = num;
		hashTable.insertBST(num);
		counter++;
	}
	cout << counter << " numbers inserted to bring load factor to " << loadFactor << endl;

	//delete 100 values and record the time each takes
	for (int i = 0; i < 100; i++) {
		auto t1 = std::chrono::high_resolution_clock::now();
		hashTable.deleteBST(toDelete[i]);
		auto t2 = std::chrono::high_resolution_clock::now();
		times[i] = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	}
	double deleteMean = 0;
	double delete_stddev = 0;
	int totalTime = 0;

	//calculate mean
	for (int i = 0; i < 100; i++) {
		totalTime += times[i];
	}
	deleteMean = ((double)totalTime) / 100.0;

	//calculate std dev
	for (int i = 0; i < 100; i++) {
		delete_stddev += pow(((double)times[i]) - deleteMean,2);
	}
	delete_stddev /= 99;

	//insert 100 values and record the time each takes
	for (int i = 0; i < 100; i++) {
		getline(file, tmpNum, ',');
		num = stoi(tmpNum);
		toDelete[i] = num;
		auto t1 = std::chrono::high_resolution_clock::now();
		hashTable.insertBST(num);
		auto t2 = std::chrono::high_resolution_clock::now();
		times[i] = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	}
	double insertMean = 0;
	double insert_stddev = 0;
	totalTime = 0;
	
	//calculate mean
	for (int i = 0; i < 100; i++) {
		totalTime += times[i];
	}
	insertMean = ((double)totalTime) / 100.0;

	//calculate std dev
	for (int i = 0; i < 100; i++) {
		insert_stddev += pow(((double)times[i]) - deleteMean, 2);
	}
	insert_stddev /= 99;

	//lookup 100 values and record the time each takes
	for (int i = 0; i < 100; i++) {
		auto t1 = std::chrono::high_resolution_clock::now();
		hashTable.lookupBST(toDelete[i]);
		auto t2 = std::chrono::high_resolution_clock::now();
		times[i] = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	}
	double lookupMean = 0;
	double lookup_stddev = 0;
	totalTime = 0;

	//calculate mean
	for (int i = 0; i < 100; i++) {
		totalTime += times[i];
	}
	lookupMean = ((double)totalTime) / 100.0;

	//calculate std dev
	for (int i = 0; i < 100; i++) {
		lookup_stddev += pow(((double)times[i]) - deleteMean, 2);
	}
	lookup_stddev /= 99;

	cout << "BST chaining at load factor " << loadFactor << ":" << endl;
	cout << "Average delete time: " << deleteMean << " microseconds with " << delete_stddev << " microseconds standard deviation ." << endl;
	cout << "Average insert time: " << insertMean << " microseconds with " << insert_stddev << " microseconds standard deviation ." << endl;
	cout << "Average lookup time: " << lookupMean << " microseconds with " << lookup_stddev << " microseconds standard deviation ." << endl;
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
	hashBST bst(hashChoice);

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
			while (file.good()) {
				getline(file, tmpNum, ',');
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
			int tablesize = 10009;
			hashBST hashTable(hashChoice);
			testBST(hashTable, tablesize, filename, 0.1);
			hashTable.clearTable();

			testBST(hashTable, tablesize, filename, 0.2);
			hashTable.clearTable();

			testBST(hashTable, tablesize, filename, 0.5);
			hashTable.clearTable();

			testBST(hashTable, tablesize, filename, 0.7);
			hashTable.clearTable();

			testBST(hashTable, tablesize, filename, 1);

			break;
			
		}

		// linear probing
		else if (mainChoice == 3) {
			int tablesize = 10009;
			while (true) {
				if (hashChoice == 1) {
					//create hash table and then test at desired load factors
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
					//create hash table and then test at desired load factors
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
			}
		}

		// cuckoo hashing
		else if (mainChoice == 4) {
			//create hash table and then test at desired load factors
			//we use smaller load factors as the data sets have enough duplicate entries that 0.7 takes a prohibitive amount of time to achieve, if it would get there at all
			int tablesize = 10009;
			CuckooHashing hashTable(tablesize);

			testCuckooHashing(hashTable, tablesize, filename, 0.1);

			testCuckooHashing(hashTable, tablesize, filename, 0.2);

			testCuckooHashing(hashTable, tablesize, filename, 0.3);

			testCuckooHashing(hashTable, tablesize, filename, 0.4);

			testCuckooHashing(hashTable, tablesize, filename, 0.5);

			testCuckooHashing(hashTable, tablesize, filename, 0.6);
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

/*
int num;
			string tmpNum;
			ifstream file(filename);
			if (!file.is_open())
				cout << "failed to open file" << endl << "\n";

			//int i = 0;
			while (file.good()) {
				getline(file, tmpNum, ',');
				num = stoi(tmpNum);
				// insert into hash table
				//i++;
				//cout << "inserting: " << i << "th element" << endl;
				bst.insertBST(num);
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
					bst.insertBST(toInsert);
				}
				// lookup entry
				else if (actionChoice == 2) {
					cout << "Enter value to lookup" << endl;
					cout << ">> ";
					cin >> toLookup;
					if (bst.lookupBST(toLookup)) {
						cout << endl <<"lookup successful!" << endl;
					}
					else {
						cout << "lookup failure :(" << endl;
					}
				}
				// delete entry
				else if (actionChoice == 3) {
					cout << "Enter value to delete" << endl;
					cout << ">> ";
					cin >> toDelete;
					int hashKey = bst.hashCalcBST(toDelete);
					cout << "value of node input into delete function" << bst.table[hashKey]->root->val << endl;
					bst.deleteBST(toDelete);
				}
				else if (actionChoice == 4) {
					quit++;
					cout << "quitting action menu" << endl << "\n";
				}
			}*/