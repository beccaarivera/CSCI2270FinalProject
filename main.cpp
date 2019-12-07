#include<iostream>
#include "LL.hpp"
#include<string>

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
  // declare class for linked list implementation
  hashLL ll;

  // prompt user to chosse which collision resolution method to use
  mainMenu();
  int mainChoice;
  int hashChoice;
  cin >> mainChoice;

  //int quit = 0;
  //while (quit == 0) {
    switch (mainChoice) {
      // chaining with LL
      case 1:
      // prompt user to choose hash function to implement
        hashMenu();
        cin >> hashChoice;

        switch (hashChoice) {
          // x mod TABLE_SIZE
          case 1:
            if (ll.isEmpty(1))
              cout << "is empty -> works!" << endl;
            else
              cout << "something's wrong" << endl;
          break;

          // Floor(x/TABLE_SIZE) mod TABLE_SIZE
          case 2:

          break;
        }
      break;

      // chaining with BST
      case 2:
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
      break;

      // linear probing
      case 3:
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
      break;

      // cuckoo hashing
      case 4:
        // uses both hash functions by definition
      break;

      // quit
      /*case 5:
        quit++;
      break;*/
    }
  //}
}
