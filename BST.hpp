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
	hashBST(int hChoice);
	tableNodeBST** table;
	int hashCalcBST(int value);
	bool isEmptyBST(int key);
	void insertBST(int value);
	treeNode* insertBSTHelper( treeNode* currNode, int data);
	bool lookupBST(int value);
	bool lookupBSTHelper(int value, treeNode* root);
	treeNode* deleteBSTHelper(treeNode* pres, int value);
	void deleteBST(int value);
	//void deleteBST(int value, int choice);
	//treeNode* deleteHelper(treeNode* pres);
	treeNode* getMinValueNode(treeNode* pres);
private:
	int TABLE_SIZE = 10009;
	int choice;
};
