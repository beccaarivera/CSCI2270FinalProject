#pragma once
class LinearProbing
{
public:
	void insert(int toInsert);
	void deleteValue(int toDelete);
	bool lookup(int toLookup);
	double loadFactor();
	LinearProbing(int hashFunction, int tablesize);
	~LinearProbing();
	void clearTable();

private:
	int TABLE_SIZE;
	int hashFunc;
	int** hashTable;

	int hashFunc1(int toHash);
	int hashFunc2(int toHash);
};

