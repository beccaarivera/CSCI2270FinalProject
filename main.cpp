#include<iostream>
#include<string>
#include <fstream>
#include <sstream>
#include "CuckooHashing.h"
#include "LinearProbing.h"

using namespace std;

void mainMenu() {
	cout << "Choose collision resolution method:" << endl;
	cout << "1. Chaining with LL" << endl;
	cout << "2. Chaining with BST" << endl;
	cout << "3. Linear Probing" << endl;
	cout << "4. Cuckoo Hashing" << endl;
	//cout << "5. Quit" << endl;
}

void hashMenu() {
	cout << "Choose which hash function to implement:" << endl;
	cout << "1. x mod TABLE_SIZE" << endl;
	cout << "2. Floor(x/TABLE_SIZE) mod TABLE_SIZE" << endl;
}

int main() {
	// prompt user to chosse which collision resolution method to use
	mainMenu();
	int mainChoice;
	int hashChoice;
	cin >> mainChoice;


	//int quit = 0;
	//while(quit == 0){
	if (mainChoice == 1) {
		// prompt user to choose hash function to implement
		hashMenu();
		cin >> hashChoice;

		switch (hashChoice) {
			// x mod TABLE_SIZE
		case 1:
			cout << "in hash 1" << endl; // delete couts later
			break;

			// Floor(x/TABLE_SIZE) mod TABLE_SIZE
		case 2:
			cout << "in hash 2" << endl;
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
		break;

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
		break;
	}
	}else{
		cout << "Please enter a number 1-5" << endl;
	}
	//}
}

