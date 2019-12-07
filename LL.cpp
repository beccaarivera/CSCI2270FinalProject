#include<iostream>
#include "LL.hpp"

using namespace std;

/* constructor for linked list node
   initialized head to NULL */
/*LL::LL() {
  head = NULL;
}*/

/* constructor for hash table
   initializes all indices to NULL */
hashLL::hashLL() {
  table = new tableNode* [TABLE_SIZE];
  for (int i = 0; i < TABLE_SIZE; i++) {
    table[i] = new tableNode;
  }
}

// checks if the hash table location for a given key is empty
bool hashLL::isEmpty(int key) {
  if (table[key]->head == NULL)
    return true;
  else
    return false;
}

/*void hashLL::insertLL(int val, int choice) {
  // apply hash function
  if (choice == 1) {
    key = val % TABLE_SIZE;
  }
  else if (choice == 2) {
    key = floor(val/TABLE_SIZE) % TABLE_SIZE;
  }
  // case for if hash location is empty



}*/
