#pragma once
#include <string>
class LinearProbing
{
public:
	void insert(int toInsert);
	void deleteValue(int toDelete);
	void lookup(int toLookup);
	double loadFactor();
	LinearProbing(int hashFunction);
	~LinearProbing();

private:
	int TABLE_SIZE;
	int hashFunc;
	int** hashTable;
	int hashFunc1(int toHash);
	int hashFunc2(int toHash);
};

