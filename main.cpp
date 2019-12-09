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
			//hashMenu();
			while (true) {
				cin >> hashChoice;
				if (hashChoice == 1) {
					LinearProbing hashTable = LinearProbing(1);
					string toAdd;
					//while (getline(csvfile, toAdd,',')) {
						//hashTable.insert(stoi(toAdd));
					//}
					break;
				}
				else if (hashChoice == 2) {
					LinearProbing hashTable = LinearProbing(2);

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
			CuckooHashing hashTable;

			//fill up the table
			for (int i = 0; i < 1019; i++) {
				hashTable.insert(i);
				hashTable.insert(i * 1019 + i);
			}

			//cause rehash
			hashTable.insert(1020);
			hashTable.countRehashes();

			for (int i = 0; i < 1019; i++) {
				if (!hashTable.lookup(i)) {
					cout << "Failure :(" << endl;
					break;
				}
				if (!hashTable.lookup(i * 1019 + i)) {
					cout << "Failure :(" << endl;
					break;
				}
			}
			if (!hashTable.lookup(1020)) {
				cout << "Failure :(" << endl;
			}
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
