#include<iostream>

using namespace std;

// node structure for linked list
struct LLnode {
  LLnode(int k, int v, LLnode* next) {
    this->key = k;
    this->val = v;
    this->next = NULL;
  }

  int key; // index location in hash table
  int val; // value
  struct LLnode* next;
};

/*class LL {
  private:
    LLnode* head;
  public:
    LL();
    bool isEmptyLL();
};*/

// node structure for hash table
struct tableNode {
  LLnode* head = NULL;
};


class hashLL {
  public:
    hashLL();
    bool isEmpty(int key);
    void insertLL(int val, int choice);
    void lookupLL(int val, int choice);
    void deleteLL(int val, int choice);
  private:
    tableNode** table;
	int TABLE_SIZE = 10009;
};
