#include "listhash.h"
#include "arraytable.h"
#include "balancetree.h"
#include "arrayhash.h"
#include "sorttable.h"
#include "scantable.h"
#include "word.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

enum TabType {SCAN = 1, SORT, TREE, BALANCE, HASHARR, HASHLIST} type;

int tabSize;
int dataCount;
PTTable tab = nullptr;
string* keys;


void init();
void destr();
string* generateKeys(int count);
PTTable createScan();
PTTable createSort();
PTTable createTree();
PTTable createBalance();
PTTable createHasharr();
PTTable createHashlist();
void fillTable();
void printAvgs(int count);

int main() {
    srand(time(nullptr));
    init();
    destr();
    return 0;
}

void init() {
    int choise;
    cout << "Choose table" << endl <<
            "1. Scan table" << endl <<
            "2. Sort table" << endl <<
            "3. Tree table" << endl <<
            "4. Balance tree table" << endl <<
            "5. Hash array table" << endl <<
            "6. Hash list table" << endl;
    cin >> choise;
    type = (TabType)choise;

    switch (type) {
      case SCAN:
        /* cout << "SCAN" << endl; */
        tab = createScan();
        break;
      case SORT:
        /* cout << "SORT" << endl; */
        tab = createSort();
        break;
      case TREE:
        /* cout << "TREE" << endl; */
        tab = createTree();
        break;
      case BALANCE:
        tab = createBalance();
        /* cout << "BALANCE" << endl; */
        break;
      case HASHARR:
        /* cout << "HASHARR" << endl; */
        tab = createHasharr();
        break;
      case HASHLIST:
        tab = createHashlist();
        /* cout << "HASHLIST" << endl; */
        break;
      default:
        exit(-1);
        break;
    }

    fillTable();

    int iters;
    cout << "How many iterations: ";
    cin >> iters;
    printAvgs(iters);
}


void destr() {
    delete tab;
}

string* generateKeys(int c) {
    string *res = new string[c];

    for (int i = 0; i < c; ++i) {
        res[i] = string("000000");
        for (int j = 0; j < 6; ++j) {
            res[i][j] = '0' + rand() % 10;
        }
    }

    return res;
}

PTTable createScan() {
    cout << "Enter table size: ";
    cin >> tabSize;

    tab = new TScanTable(tabSize);

    return tab;
}

PTTable createSort() {
    cout << "Enter table size: ";
    cin >> tabSize;

    tab = new TSortTable(tabSize);

    return tab;
}

PTTable createTree() {
    tab = new TTreeTable;

    return tab;
}

PTTable createBalance() {
    tab = new TBalanceTree;

    return tab;
}

PTTable createHasharr() {
    cout << "Enter table size: ";
    cin >> tabSize;

    tab = new TArrayHash(tabSize);

    return tab;
}

PTTable createHashlist() {
    cout << "Enter table size: ";
    cin >> tabSize;

    tab = new TListHash(tabSize);

    return tab;
}

void fillTable() {
    cout << "Enter records count: ";
    cin >> dataCount;

    keys = generateKeys(dataCount);

    for (int i = 0; i < dataCount; ++i) {
        tab->InsRecord(keys[i], nullptr);
    }
}

void printAvgs(int c) {
    if (c < 1) {
        exit(-1);
    }
    double insAvg = 0.0, findAvg = 0.0, delAvg = 0.0;
    string k("000000");

    for (int i = 0; i < 6; ++i) {
        k[i] = '0' + rand() % 10;
    }

    for (int i = 0; i < c; ++i) {
        tab->ResetEfficiency();
        tab->InsRecord(k, nullptr);
        insAvg += (double)tab->GetEfficiency();

        tab->ResetEfficiency();
        tab->FindRecord(k);
        findAvg += (double)tab->GetEfficiency();

        tab->ResetEfficiency();
        tab->DelRecord(k);
        delAvg += (double)tab->GetEfficiency();
    }

    insAvg /= c;
    findAvg /= c;
    delAvg /= c;

    cout << "Efficiency" << endl <<
            "Insert: " << insAvg << endl <<
            "Find:   " << findAvg << endl <<
            "Delete: " << delAvg << endl;
}


