#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
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
    TScanTable tbScan(dataCount);
    TSortTable tbSort(dataCount);
    TArrayHash tbHashArr(dataCount);
    TListHash tbHashList(dataCount);
    for (int i = 0; i < dataCount; i++)
    {
        fin.getline(buff, 4);
        keys.push_back(buff);
    }
    cout << "efficiency insert in scan table = " << insert_table_efficiency(tbScan, keys, dataCount) / dataCount << endl;
    cout << "efficiency insert in sort table = " << insert_table_efficiency(tbSort, keys, dataCount) / dataCount << endl;
    cout << "efficiency insert in hash arr table = " << insert_table_efficiency(tbHashArr, keys, dataCount) / dataCount << endl;
    cout << "efficiency insert in hash list table = " << insert_table_efficiency(tbHashList, keys, dataCount) / dataCount << endl << endl;

    cout << "efficiency find in scan table = " << find_table_efficiency(tbScan, keys, dataCount) / dataCount << endl;
    cout << "efficiency find in sort table = " << find_table_efficiency(tbSort, keys, dataCount) / dataCount << endl;
    cout << "efficiency find in hash arr table = " << find_table_efficiency(tbHashArr, keys, dataCount) / dataCount << endl;
    cout << "efficiency find in hash list table = " << find_table_efficiency(tbHashList, keys, dataCount) / dataCount << endl << endl;

    cout << "efficiency delete in scan table = " << delete_table_efficiency(tbScan, keys, dataCount) / dataCount << endl;
    cout << "efficiency delete in sort table = " << delete_table_efficiency(tbSort, keys, dataCount) / dataCount << endl;
    cout << "efficiency delete in hash arr table = " << delete_table_efficiency(tbHashArr, keys, dataCount) / dataCount << endl;
    cout << "efficiency delete in hash list table = " << delete_table_efficiency(tbHashList, keys, dataCount) / dataCount << endl;

    return 0;
}