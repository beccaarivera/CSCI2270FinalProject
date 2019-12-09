#include<iostream>

using namespace std;

// node structure for BST
struct treeNode {
  int val;
  treeNode* left = NULL;
  treeNode* right = NULL;
  treeNode* parent = NULL;
};

// node structure for hash table
struct tableNodeBST {
  treeNode* root = NULL;
};

class hashBST {
  public:
    hashBST();
    int hashCalcBST(int value, int choice);
    bool isEmptyBST(int key);
    void insertBST(int value, int choice);
    void lookupBST(int value, int choice);
    void deleteBST(int value, int choice);
    treeNode* deleteHelper(treeNode* pres);
    treeNode* getMinValueNode(treeNode* pres);
  private:
    tableNodeBST** table;
    int TABLE_SIZE = 10009;
};
