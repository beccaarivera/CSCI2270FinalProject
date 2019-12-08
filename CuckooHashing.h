#pragma once
class CuckooHashing
{
public:
	void insert(int toInsert);
	void deleteValue(int toDelete);
	bool lookup(int toLookup);
	CuckooHashing();
	~CuckooHashing();
	void countRehashes();

private:
	int TABLE_SIZE;

	int** hashTable1;
	int** hashTable2;
	int rehashCounter;

	int hashFunc1(int toHash);
	int hashFunc2(int toHash);
	bool swap(int originalKey, int originalTable, int toSwapKey, int tableNum);
	bool insertHelper(int toInsert);

	void rehash(int toInsert);
};

