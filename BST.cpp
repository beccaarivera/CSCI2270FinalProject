#include<iostream>
#include "BST.hpp"
#include "math.h"

using namespace std;

/* constructor for hash table
   initializes all indices to NULL */
hashBST::hashBST() {
  table = new tableNodeBST* [TABLE_SIZE];
  for (int i = 0; i < TABLE_SIZE; i++) {
    table[i] = new tableNodeBST;
  }
}

int hashBST::hashCalcBST(int value, int choice) {
  // apply hash function
  int key;
  if (choice == 1) {
    return (value % TABLE_SIZE);
  }
  else if (choice == 2) {
    return ((int)floor(value/TABLE_SIZE) % TABLE_SIZE);
  }
}

bool hashBST::isEmptyBST(int key) {
  if (table[key]->root == NULL)
    return true;
  else
    return false;
}

void hashBST::insertBST(int value, int choice) {
  int key = hashCalcBST(value, choice);
  // create BST node with value val
  treeNode* node = new treeNode;
  node->val = value;
  // case for if hash location is empty
  if (isEmptyBST(key)){
    table[key]->root = node;
    //cout << "added root" << endl;
  }
  else {
    // if hash location already has values, traverse BST to find insert location
    treeNode* pres = table[key]->root;
    treeNode* prev = NULL;
    while (pres != NULL) {
      prev = pres;
      // value is larger
      if (value > pres->val)
        pres = pres->right;
      // value is smaller
      else if (value < pres->val)
        pres = pres->left;
    }
    // once at leaf node, insert new node
    if (node->val > prev->val){
      prev->right = node;
      //cout << "added right child" << endl;
    }
    else if (node->val < prev->val){
      prev->left = node;
      //cout << "added left child" << endl;
    }
  }
}

void hashBST::lookupBST(int value, int choice) {
  int key = hashCalcBST(value, choice);
  // check if tree is empty at hash location
  if (isEmptyBST(key)) {
    cout << "tree empty at this location, not found" << endl << "\n";
    return;
  }
  // check if root at hash table location matches value
  if (table[key]->root->val == value) {
    cout << "found!" << endl << "\n";
    return;
  }
  else {
    // traverse tree
    treeNode* pres = table[key]->root;
    while (pres->val != value) {
      // value is larger
      if (value > pres->val && pres->right != NULL)
        pres = pres->right;
      // value is smaller
      else if (value < pres->val && pres->left != NULL)
        pres = pres->left;
      // if reached leaf node
      else if (pres->right == NULL && pres->left == NULL){
        cout << "not found" << endl << "\n";
        return;
      }
    }
  }
  // assume node found
  cout << "found!" << endl << "\n";
}

treeNode* hashBST::getMinValueNode(treeNode* pres) {
  if (pres->left == NULL)
    return pres;
  return getMinValueNode(pres->left);
}

treeNode* hashBST::deleteHelper(treeNode* pres) {
  // delete leaf
  if (pres->left && pres->right == NULL) {
    delete pres;
    return NULL;
  }
  // only left child
  else if (pres->right == NULL) {
    treeNode* tmp = pres;
    pres->left->parent = pres->parent;
    pres = pres->left;
    delete tmp;
    return pres;
  }
  // only right child
  else if (pres->left == NULL) {
    treeNode* tmp = pres;
    pres->right->parent = pres->parent;
    pres = pres->right;
    delete tmp;
    return pres;
  }
  // left and right child
  else {
    // replace with min value from right subtree
    treeNode* min = getMinValueNode(pres->right);
    treeNode* par = min->parent;
    par->left = min->right;
    if (min->right != NULL)
      min->right->parent = par;
    min->left = pres->left;
    min->right = pres->right;
    min->parent = pres->parent;
    return min;
  }
}

void hashBST::deleteBST(int value, int choice) {
  int key = hashCalcBST(value, choice);
  // check if tree is empty at hash location
  if (isEmptyBST(key)) {
    cout << "tree empty at this location, cannot delete" << endl << "\n";
    return;
  }
  // traverse tree to find node to delete
  treeNode* pres = table[key]->root;
  while (pres->val != value){
    // value is larger
    if (value > pres->val && pres->right != NULL)
      pres = pres->right;
    // value is smaller
    else if (value < pres->val && pres->left != NULL)
      pres = pres->left;
    else if (pres->right == NULL && pres->left == NULL) {
      cout << "not found, cannot delete" << endl << "\n";
      return;
    }
  }
  // node found
  //cout << "found node to delete: " << pres->val << endl;
  treeNode* par = pres->parent;
  //cout << "debug" << endl;
  //
  if (par == NULL) {
    table[key]->root = deleteHelper(pres);
    cout << "debug" << endl;
  }
  else if (par->left == pres)
    par->left = deleteHelper(pres);
  else
    par->right = deleteHelper(pres);
}
