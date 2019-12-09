#pragma once
#include<iostream>

using namespace std;

// node structure for BST
struct treeNode {
  int val;
  treeNode* left = NULL;
  treeNode* right = NULL;
  //treeNode* parent = NULL;
};

// node structure for hash table
struct tableNodeBST {
  treeNode* root = NULL;
};

class hashBST {
  public:
    tableNodeBST** table;
    hashBST();
    int hashCalcBST(int value, int choice);
    bool isEmptyBST(int key);
    void insertBST(int value, int key);
    void lookupBST(int value, int key);
    treeNode* deleteBST(treeNode* pres, int value);
    //void deleteBST(int value, int choice);
    //treeNode* deleteHelper(treeNode* pres);
    treeNode* getMinValueNode(treeNode* pres);
  private:
    int TABLE_SIZE = 10009;
};
