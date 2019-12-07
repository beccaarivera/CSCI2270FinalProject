#include<iostream>
#include<string>
#include <fstream>
#include <sstream>
#include "CuckooHashing.h"
#include "LinearProbing.h"
#include <chrono>
#include "LL.hpp"

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

int main() {
	// prompt user to chosse which collision resolution method to use
	int mainChoice;
	int hashChoice;
	string filename = "dataSetA.csv";
	fstream csvfile;
	csvfile.open(filename);

  hashLL ll;


	//int quit = 0;
	//while(quit == 0){
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
				if (ll.isEmpty(0))
          cout << "is empty, worked!" << endl;
        else
          cout << "somethin's wrong" << endl;

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
				cout << "in hash 1" << endl;
				break;

				// Floor(x/TABLE_SIZE) mod TABLE_SIZE
			case 2:
				cout << "in hash 2" << endl;
				break;
			}

			// linear probing
		}
		else if (mainChoice == 3) {
			// prompt user to choose hash function to implement
			hashMenu();
			while (true) {
				cin >> hashChoice;
				if (hashChoice == 1) {
					LinearProbing hashTable = LinearProbing(1);

					break;
				}
				else if (hashChoice == 2) {
					LinearProbing hashTable = LinearProbing(2);

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
