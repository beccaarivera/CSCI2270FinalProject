#include<iostream>
#include "LL.hpp"
#include "math.h"


using namespace std;

/* constructor for hash table
   initializes all indices to NULL */
hashLL::hashLL() {
  table = new tableNodeLL* [TABLE_SIZE];
  for (int i = 0; i < TABLE_SIZE; i++) {
    table[i] = new tableNodeLL;
  }
}

int hashLL::hashCalcLL(int value, int choice) {
  // apply hash function
  int key;
  if (choice == 1) {
    return (value % TABLE_SIZE);
  }
  else if (choice == 2) {
    return ((int)floor(value/TABLE_SIZE) % TABLE_SIZE);
  }
}

bool hashLL::isEmptyLL(int key) {
  if (table[key]->head == NULL)
    return true;
  else
    return false;
}

void hashLL::insertLL(int value, int choice) {
  int key = hashCalcLL(value, choice);
  // create linked list node with value val
  LLnode* node = new LLnode;
  node->val = value;
  // case for if hash location is empty
  if (isEmptyLL(key)) {
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
  int key = hashCalcLL(value, choice);
  // check if linked list is empty at hash location
  if (isEmptyLL(key)) {
    cout << "Linked List empty at this location, not found" << endl;
    return;
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
  int key = hashCalcLL(value, choice);
  // check if linked list is empty at hash location
  if (isEmptyLL(key)) {
    cout << "Linked List empty at this location, cannot delete" << endl;
    return;
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
