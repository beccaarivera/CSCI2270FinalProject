#include<iostream>
#include "BST.hpp"
#include "math.h"

using namespace std;



treeNode* createNode(int data)
{
	treeNode* newNode = new treeNode;
	newNode->val = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}



/* constructor for hash table
   initializes all indices to NULL */
hashBST::hashBST(int hChoice) {
	choice = hChoice;
	table = new tableNodeBST * [TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++) {
		table[i] = new tableNodeBST;
	}
}

int hashBST::hashCalcBST(int value) {
	// apply hash function
	int key;
	if (choice == 1) {
		return (value % TABLE_SIZE);
	}
	else if (choice == 2) {
		return ((int)floor(((double)value) / ((double)TABLE_SIZE)) % TABLE_SIZE);
	}
}

bool hashBST::isEmptyBST(int key) {
	if (table[key]->root == NULL)
		return true;
	else
		return false;
}
void hashBST::insertBST(int value) {
	table[hashCalcBST(value)]->root=insertBSTHelper(table[hashCalcBST(value)]->root, value);
}
treeNode* hashBST::insertBSTHelper(treeNode* currNode, int data) {
	if (currNode == NULL) {
		return createNode(data);
	}
	else if (currNode->val < data) {
		currNode->right = insertBSTHelper(currNode->right, data);
	}
	else if (currNode->val > data) {
		currNode->left = insertBSTHelper(currNode->left, data);
	}
	return currNode;
}

bool hashBST::lookupBST(int value) {
	return lookupBSTHelper(value, table[hashCalcBST(value)]->root);
}

bool hashBST::lookupBSTHelper(int value, treeNode* currNode) {
	if (currNode == NULL)
		return false;

	if (currNode->val == value)
		return true;

	if (currNode->val > value) {
		cout << "Looking left" << endl;
		return lookupBSTHelper(value, currNode->left);
	}

	cout << "looking right" << endl;
	return lookupBSTHelper(value, currNode->right);
}

treeNode* hashBST::getMinValueNode(treeNode* pres) {
	if (pres->left == NULL) {
		return pres;
	}
	return getMinValueNode(pres->left);
}

void hashBST::deleteBST(int value) {
	table[hashCalcBST(value)]->root=deleteBSTHelper(table[hashCalcBST(value)]->root, value);
}

treeNode* hashBST::deleteBSTHelper(treeNode* currNode, int value) {
	if (currNode == NULL)
	{
		return NULL;
	}
	else if (value < currNode->val)
	{
		currNode->left = deleteBSTHelper(currNode->left, value);
	}
	else if (value > currNode->val)
	{
		currNode->right = deleteBSTHelper(currNode->right, value);
	}
	// We found the node with the value
	else
	{
		//no child
		if (currNode->left == NULL && currNode->right == NULL)
		{
			delete currNode;
			return NULL;
		}
		//Only right child
		else if (currNode->left == NULL)
		{
			treeNode* toReturn = currNode->right;
			delete currNode;
			return toReturn;
		}
		//Only left child
		else if (currNode->right == NULL)
		{
			treeNode* toReturn = currNode->left;
			delete currNode;
			return toReturn;

		}
		//TODO Case: Both left and right child
		else
		{
			///Replace with Minimum from right subtree
			treeNode* toReplaceWith = getMinValueNode(currNode->right);
			int valToReplaceWith = toReplaceWith->val;
			currNode->val = valToReplaceWith;
			currNode->right = deleteBSTHelper(currNode->right, valToReplaceWith);
			return currNode;

		}

	}
	return currNode;
}

/*treeNode* hashBST::deleteHelper(treeNode* pres) {
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
  //treeNode* par = NULL;
  while (pres->val != value){
	//par = pres;
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
	cout << "par=NULL" << endl;
	table[key]->root = deleteHelper(pres);
	cout << "debug" << endl;
  }
  else if (par->left == pres)
	par->left = deleteHelper(pres);
  else
	par->right = deleteHelper(pres);
}*/
