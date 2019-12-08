#include<iostream>

using namespace std;

// node structure for linked list
struct LLnode {
  /*LLnode(int k, int v, LLnode* next) {
    this->key = k;
    this->val = v;
    this->next = NULL;
  }*/

  //int key; // index location in hash table
  int val; // value
  struct LLnode* next;
};

// node structure for hash table
struct tableNodeLL {
  LLnode* head = NULL;
};

class hashLL {
  public:
    hashLL();
    int hashCalcLL(int value, int choice);
    bool isEmptyLL(int key);
    void insertLL(int value, int choice);
    void lookupLL(int value, int choice);
    void deleteLL(int value, int choice);
  private:
    tableNodeLL** table;
    int TABLE_SIZE = 10009;
};
