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

    vector<string> sur(25);
    TScanTable scant;
    TSortTable sortt;
    TTreeTable treet;
    TBalanceTree btreet;
    TArrayHash ahasht;
    TListHash lhasht;
    ifstream in("C:/Users/м/Desktop/Новая папка/7/mp2-lab7-tables/samples/Surnames.txt");
    if (!in.is_open()) return 0;
    int size = 20;
    for (int i = 0; i < size; ++i) {
        string s;
        getline(in, s, '\n');
        cout << s << endl;
        sur.push_back(s);
        scant.InsRecord(s, nullptr);
        sortt.InsRecord(s, nullptr);
        treet.InsRecord(s, nullptr);
        btreet.InsRecord(s, nullptr);
        ahasht.InsRecord(s, nullptr);
        lhasht.InsRecord(s, nullptr);
    }
    in.close();

    cout << "Insert:" << endl;
    cout << "Scan_Table: " << scant.GetEfficiency() << endl;
    cout << "Sort_Table: " << sortt.GetEfficiency() << endl;
    cout << "Tree_Table: " << treet.GetEfficiency() << endl;
    cout << "BalanceTree_Table: " << btreet.GetEfficiency() << endl;
    cout << "ArrayHash_Table: " << ahasht.GetEfficiency() << endl;
    cout << "ListHash_Table: " << lhasht.GetEfficiency() << endl;

    scant.ResetEfficiency();
    sortt.ResetEfficiency();
    treet.ResetEfficiency();
    btreet.ResetEfficiency();
    ahasht.ResetEfficiency();
    lhasht.ResetEfficiency();

    for (int i = 0; i < size; ++i) {
        scant.FindRecord(sur[i]);
        sortt.FindRecord(sur[i]);
        treet.FindRecord(sur[i]);
        btreet.FindRecord(sur[i]);
        ahasht.FindRecord(sur[i]);
        lhasht.FindRecord(sur[i]);
    }

    cout << "Find: " << endl;
    cout << "Scan_Table: " << scant.GetEfficiency() << endl;
    cout << "Sort_Table: " << sortt.GetEfficiency() << endl;
    cout << "Tree_Table: " << treet.GetEfficiency() << endl;
    cout << "BalanceTree_Table: " << btreet.GetEfficiency() << endl;
    cout << "ArrayHash_Table: " << ahasht.GetEfficiency() << endl;
    cout << "ListHash_Table: " << lhasht.GetEfficiency() << endl;

    scant.ResetEfficiency();
    sortt.ResetEfficiency();
    treet.ResetEfficiency();
    btreet.ResetEfficiency();
    ahasht.ResetEfficiency();
    lhasht.ResetEfficiency();
    for (int i = 0; i < size; i++) {
        scant.DelRecord(sur[i]);
        sortt.DelRecord(sur[i]);
        treet.DelRecord(sur[i]);
        btreet.DelRecord(sur[i]);
        ahasht.DelRecord(sur[i]);
        lhasht.DelRecord(sur[i]);
    }
    cout << "Delete: " << endl;
    cout << "Scan_Table: " << scant.GetEfficiency() << endl;
    cout << "Sort_Table: " << sortt.GetEfficiency() << endl;
    cout << "Tree_Table: " << treet.GetEfficiency() << endl;
    cout << "BalanceTree_Table: " << btreet.GetEfficiency() << endl;
    cout << "ArrayHash_Table: " << ahasht.GetEfficiency() << endl;
    cout << "ListHash_Table: " << lhasht.GetEfficiency() << endl;

    return 0;
}