// TTableTestkit.cpp
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include <fstream>
#include "TScanTable.h"
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"
#include "TTreeTable.h"

using namespace std;

int main() {

    vector<string> sur(20);
    TScanTable scan_table;
    TSortTable sort_table;
    TTreeTable tree_table;
    TBalanceTree btree_table;
    TArrayHash ahash_table;
    TListHash lhash_table;
    ifstream in("C:/Users/bykov/OneDrive/Рабочий стол/мда/ваба лаба/mp2-lab7-tables/samples/surnames.txt");
    cout << in.is_open() << endl;
    int size = 15;
    for (int i = 0; i < size; ++i) {
        // ты молодец, все отлично работает, 
        // только нужно поправить файлик тхт
        string s;
        cout << s << endl;
        getline(in, s, '\n');
        sur.push_back(s);
        scan_table.InsRecord(s, nullptr);
        cout << scan_table.GetDataCount() << endl;
        sort_table.InsRecord(s, nullptr);
        cout << sort_table.GetDataCount() << endl;
        tree_table.InsRecord(s, nullptr);
        cout << tree_table.GetDataCount() << endl;
        btree_table.InsRecord(s, nullptr);
        cout << btree_table.GetDataCount() << endl;
        ahash_table.InsRecord(s, nullptr);
        cout << ahash_table.GetDataCount() << endl;
        lhash_table.InsRecord(s, nullptr);
        cout << lhash_table.GetDataCount() << endl;
    }
    in.close();

    cout << "Insert:" << endl;
    cout << "scan_table: " << scan_table.GetEfficiency() << endl;
    cout << "sort_table: " << sort_table.GetEfficiency() << endl;
    cout << "tree_table: " << tree_table.GetEfficiency() << endl;
    cout << "btree_table: " << btree_table.GetEfficiency() << endl;
    cout << "ahash_table: " << ahash_table.GetEfficiency() << endl;
    cout << "lhash_table: " << lhash_table.GetEfficiency() << endl;

    scan_table.ResetEfficiency();
    sort_table.ResetEfficiency();
    tree_table.ResetEfficiency();
    btree_table.ResetEfficiency();
    ahash_table.ResetEfficiency();
    lhash_table.ResetEfficiency();

    int rand_s = 15;//rand() % size;
    cout << rand_s << endl;
    cout << scan_table.GetDataCount() << endl;

    scan_table.FindRecord(sur[rand_s]);
    sort_table.FindRecord(sur[rand_s]);
    tree_table.FindRecord(sur[rand_s]);
    btree_table.FindRecord(sur[rand_s]);
    ahash_table.FindRecord(sur[rand_s]);
    lhash_table.FindRecord(sur[rand_s]);


    cout << "Find: " << sur[rand_s] << endl;
    cout << "scan_table: " << scan_table.GetEfficiency() << endl;
    cout << "sort_table: " << sort_table.GetEfficiency() << endl;
    cout << "tree_table: " << tree_table.GetEfficiency() << endl;
    cout << "btree_table: " << btree_table.GetEfficiency() << endl;
    cout << "ahash_table: " << ahash_table.GetEfficiency() << endl;
    cout << "lhash_table: " << lhash_table.GetEfficiency() << endl;

    scan_table.ResetEfficiency();
    sort_table.ResetEfficiency();
    tree_table.ResetEfficiency();
    btree_table.ResetEfficiency();
    ahash_table.ResetEfficiency();
    lhash_table.ResetEfficiency();

    scan_table.DelRecord(sur[rand_s]);
    sort_table.DelRecord(sur[rand_s]);
    tree_table.DelRecord(sur[rand_s]);
    btree_table.DelRecord(sur[rand_s]);
    ahash_table.DelRecord(sur[rand_s]);
    lhash_table.DelRecord(sur[rand_s]);

    cout << "Delete: " << sur[rand_s] << endl;
    cout << "scan_table: " << scan_table.GetEfficiency() << endl;
    cout << "sort_table: " << sort_table.GetEfficiency() << endl;
    cout << "tree_table: " << tree_table.GetEfficiency() << endl;
    cout << "btree_table: " << btree_table.GetEfficiency() << endl;
    cout << "ahash_table: " << ahash_table.GetEfficiency() << endl;
    cout << "lhash_table: " << lhash_table.GetEfficiency() << endl;

    return 0;
}