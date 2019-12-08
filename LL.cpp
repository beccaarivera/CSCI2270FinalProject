#include<iostream>
#include "LL.hpp"
#include "math.h"


using namespace std;

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

void hashLL::insertLL(int value, int choice) {
  // apply hash function
  int key;
  if (choice == 1) {
    key = value % TABLE_SIZE;
  }
  else if (choice == 2) {
    key = (int)floor(value/TABLE_SIZE) % TABLE_SIZE;
  }
  // create linked list node with value val
  LLnode* node = new LLnode;
  node->val = value;
  // case for if hash location is empty
  if (isEmpty(key)) {
    table[key]->head = node;
  }
  // if hash location already has values, add to end of linked list
  else {
    LLnode* pres = table[key]->head;
    LLnode* prev = NULL;
    // traverse to end of linked list
    while (pres != NULL) {
      prev = pres;
      pres = pres->next;
    }
    prev->next = node;
    node->next = NULL;
  }
}

void hashLL::lookupLL(int value, int choice) {
  // apply hash function
  int key;
  if (choice == 1) {
    key = value % TABLE_SIZE;
  }
  else if (choice == 2) {
    key = (int)floor(value/TABLE_SIZE) % TABLE_SIZE;
  }
  // case for if searched value is head
  if (table[key]->head->val == value) {
    cout << "found!" << endl;
    return;
  }
  else {
    // traverse linked list at hash location
    LLnode* pres = table[key]->head;
    LLnode* prev = NULL;
    while (pres->next != NULL) {
      prev = pres;
      pres = pres->next;
      if (pres->val == value)
        cout << "found!" << endl;
        return;
    }
  }
  cout << "not found :(" << endl;
}

void hashLL::deleteLL(int value, int choice) {
  // apply hash function
  int key;
  if (choice == 1) {
    key = value % TABLE_SIZE;
  }
  else if (choice == 2) {
    key = (int)floor(value/TABLE_SIZE) % TABLE_SIZE;
  }
  // case to delete head
  if (table[key]->head->val == value) {
    LLnode* tmp = table[key]->head->next;
    delete table[key]->head;
    table[key]->head = tmp;
    return;
  }
  else {
    // traverse linked list at hash location
    LLnode* pres = table[key]->head;
    LLnode* prev = NULL;
    while (pres->next != NULL) {
      prev = pres;
      pres = pres->next;
      if (pres->val == value)
        prev->next = pres->next;
        delete pres;
        cout << "deleted" << endl;
        return;
    }
  }
  cout << "not found" << endl;
}
