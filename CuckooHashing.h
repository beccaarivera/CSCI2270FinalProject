#pragma once

struct CuckooBin {
	int value;
	bool visited;
	CuckooBin(int val, bool vis) {
		value = val;
		visited = vis;
	}
};
class CuckooHashing
{
public:
	void insert(int toInsert);
	void deleteValue(int toDelete);
	bool lookup(int toLookup);
	CuckooHashing(int tablesize);
	~CuckooHashing();
	void countRehashes();
	void printValues();
	void clearTables();
	int numEntries();

private:
	int TABLE_SIZE;
	CuckooBin** hashTable1;
	CuckooBin** hashTable2;
	int rehashCounter;
	int TABLE_SIZE_INCREMENT;

	int hashFunc1(int toHash);
	int hashFunc2(int toHash);
	bool swap(int toSwapKey, int tableNum);
	bool swapHelper(int toSwapKey, int tableNum);
	bool insertHelper(int toInsert);
	void rehash(int toInsert);
	void markAllUnvisited();
	void deleteTables();
};

