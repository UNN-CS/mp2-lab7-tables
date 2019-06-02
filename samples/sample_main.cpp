#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"
#include "TTreeTable.h"

using namespace std;

int insert_table_efficiency(TTable &tb, vector<string> keys, int n)
{
	for (int i = 0; i < n; ++i)
	{
		tb.InsRecord(keys[i], PTDatValue(1));
	}
	int res = tb.GetEfficiency();
	tb.ResetEfficiency();
	return res;
}

int delete_table_efficiency(TTable &tb, vector<string> keys, int n)
{
	for (int i = 0; i < n; ++i)
	{
		tb.DelRecord(keys[i]);
	}
	int res = tb.GetEfficiency();
	tb.ResetEfficiency();
	return res;
}

int find_table_efficiency(TTable &tb, vector<string> keys, int n)
{
	for (int i = 0; i < n; ++i)
	{
		tb.FindRecord(keys[i]);
	}
	int res = tb.GetEfficiency();
	tb.ResetEfficiency();
	return res;
}

int insert_table_efficiency_rand(TTable &tb, vector<string> keys, int n)
{
	for (int i = 0; i < n; ++i)
	{
		tb.InsRecord(keys[rand() % n], PTDatValue(1));
	}
	int res = tb.GetEfficiency();
	tb.ResetEfficiency();
	return res;
}

int delete_table_efficiency_rand(TTable &tb, vector<string> keys, int n)
{
	for (int i = 0; i < n; ++i)
	{
		tb.DelRecord(keys[rand() % n]);
	}
	int res = tb.GetEfficiency();
	tb.ResetEfficiency();
	return res;
}

int find_table_efficiency_rand(TTable &tb, vector<string> keys, int n)
{
	for (int i = 0; i < n; ++i)
	{
		tb.FindRecord(keys[rand() % n]);
	}
	int res = tb.GetEfficiency();
	tb.ResetEfficiency();
	return res;
}
int main()
{
	ifstream fin;
	char buff[4];
	fin.open("keys.txt");
	int dataCount = 1000;
	srand(time(NULL));
	vector<string> keys;
	TScanTable *tbScan = new TScanTable(dataCount);
	TSortTable *tbSort = new TSortTable(dataCount);
	TArrayHash *tbHashArr = new TArrayHash(dataCount);
	TListHash *tbHashList = new TListHash(dataCount);
	for (int i = 0; i < dataCount; i++)
	{
		fin.getline(buff, 4);
		keys.push_back(buff);
	}
	cout << "efficiency insert in scan table = " << insert_table_efficiency(*tbScan, keys, dataCount) / dataCount << endl;
	cout << "efficiency insert in sort table = " << insert_table_efficiency(*tbSort, keys, dataCount) / dataCount << endl;
	cout << "efficiency insert in hash arr table = " << insert_table_efficiency(*tbHashArr, keys, dataCount) / dataCount << endl;
	cout << "efficiency insert in hash list table = " << insert_table_efficiency(*tbHashList, keys, dataCount) / dataCount << endl
		 << endl;

	cout << "efficiency find in scan table = " << find_table_efficiency(*tbScan, keys, dataCount) / dataCount << endl;
	cout << "efficiency find in sort table = " << find_table_efficiency(*tbSort, keys, dataCount) / dataCount << endl;
	cout << "efficiency find in hash arr table = " << find_table_efficiency(*tbHashArr, keys, dataCount) / dataCount << endl;
	cout << "efficiency find in hash list table = " << find_table_efficiency(*tbHashList, keys, dataCount) / dataCount << endl
		 << endl;

	cout << "efficiency delete in scan table = " << delete_table_efficiency(*tbScan, keys, dataCount) / dataCount << endl;
	cout << "efficiency delete in sort table = " << delete_table_efficiency(*tbSort, keys, dataCount) / dataCount << endl;
	cout << "efficiency delete in hash arr table = " << delete_table_efficiency(*tbHashArr, keys, dataCount) / dataCount << endl;
	cout << "efficiency delete in hash list table = " << delete_table_efficiency(*tbHashList, keys, dataCount) / dataCount << endl;
	delete tbScan;
	delete tbSort;
	delete tbHashArr;
	delete tbHashList;
	tbScan = new TScanTable(dataCount);
	tbSort = new TSortTable(dataCount);
	tbHashArr = new TArrayHash(dataCount);
	tbHashList = new TListHash(dataCount);
	cout << "efficiency insert in scan table (random) = " << insert_table_efficiency_rand(*tbScan, keys, dataCount) / dataCount << endl;
	cout << "efficiency insert in sort table (random) = " << insert_table_efficiency_rand(*tbSort, keys, dataCount) / dataCount << endl;
	cout << "efficiency insert in hash arr table (random) = " << insert_table_efficiency_rand(*tbHashArr, keys, dataCount) / dataCount << endl;
	cout << "efficiency insert in hash list table (random) = " << insert_table_efficiency_rand(*tbHashList, keys, dataCount) / dataCount << endl
		 << endl;

	cout << "efficiency find in scan table (random) = " << find_table_efficiency_rand(*tbScan, keys, dataCount) / dataCount << endl;
	cout << "efficiency find in sort table (random) = " << find_table_efficiency_rand(*tbSort, keys, dataCount) / dataCount << endl;
	cout << "efficiency find in hash arr table (random) = " << find_table_efficiency_rand(*tbHashArr, keys, dataCount) / dataCount << endl;
	cout << "efficiency find in hash list table (random) = " << find_table_efficiency_rand(*tbHashList, keys, dataCount) / dataCount << endl
		 << endl;

	cout << "efficiency delete in scan table (random) = " << delete_table_efficiency_rand(*tbScan, keys, dataCount) / dataCount << endl;
	cout << "efficiency delete in sort table (random) = " << delete_table_efficiency_rand(*tbSort, keys, dataCount) / dataCount << endl;
	cout << "efficiency delete in hash arr table (random) = " << delete_table_efficiency_rand(*tbHashArr, keys, dataCount) / dataCount << endl;
	cout << "efficiency delete in hash list table (random) = " << delete_table_efficiency_rand(*tbHashList, keys, dataCount) / dataCount << endl;

	return 0;
}
