#include <iostream>
#include <fstream>
#include "tscantable.h"
#include "tsorttaable.h"
#include "ttreenode.h"
#include "ttreetable.h"
#include "tbalancenode.h"
#include "tbalancetree.h"
#include "tarrayhash.h"
#include "tlisthash.h"
#include "tword.h"
#include <vector>
#include <random>
#include <ctime>
using namespace std;

int main() {
    const int n = 1000;
    vector<string>s;
    vector<TWord>m;
    ifstream f("D:\\Works\\LAB_7\\mp2-lab7-tables\\samples\\names.txt");
    for(int i = 0; i < n; i++) {
        string str;
        getline(f, str, '\n');
        s.push_back(str);
    }
    const int number_of_subjects = 5;
    const int number_of_groups = 1;
    ifstream f2("D:\\Works\\LAB_7\\mp2-lab7-tables\\samples\\marks.txt");
    f.close();
    f2.close();
    for(int i = 0; i < n; i++) {
        string str;
        getline(f2, str, '\n');
        m.push_back((TWord)str);
    }
    f.close();
    freopen("D:\\Works\\LAB_7\\mp2-lab7-tables\\samples\\output.txt", "w", stdout);
    TScanTable scan_table(n);
    TSortTable sort_table(n);
    TTreeTable tree_table;
    TBalanceTree balance_tree_table;
    TArrayHash array_hash_table(n);
    TListHash list_hash_table(n);
    if(s.size() != m.size())
        return cout<<"ALYARMA!!!", 1;
    for(int i = 0; i < n; i++) {
        scan_table.InsRecord(s[i], &m[i]);
        sort_table.InsRecord(s[i], &m[i]);
        tree_table.InsRecord(s[i], &m[i]);
        balance_tree_table.InsRecord(s[i], &m[i]);
        array_hash_table.InsRecord(s[i], &m[i]);
        list_hash_table.InsRecord(s[i], &m[i]);
    }
    std::cout<<scan_table.GetEfficiency()<<" ";
    std::cout<<sort_table.GetEfficiency()<<" ";
    std::cout<<tree_table.GetEfficiency()<<" ";
    std::cout<<balance_tree_table.GetEfficiency()<<" ";
    std::cout<<array_hash_table.GetEfficiency()<<" ";
    std::cout<<list_hash_table.GetEfficiency()<<"\n";
    scan_table.ResetEfficiency();
    sort_table.ResetEfficiency();
    tree_table.ResetEfficiency();
    balance_tree_table.ResetEfficiency();
    array_hash_table.ResetEfficiency();
    list_hash_table.ResetEfficiency();
    for(int i = 0; i < n; i++) {
        scan_table.FindRecord(s[i]);
        sort_table.FindRecord(s[i]);
        tree_table.FindRecord(s[i]);
        balance_tree_table.FindRecord(s[i]);
        array_hash_table.FindRecord(s[i]);
        list_hash_table.FindRecord(s[i]);
    }
    std::cout<<scan_table.GetEfficiency()<<" ";
    std::cout<<sort_table.GetEfficiency()<<" ";
    std::cout<<tree_table.GetEfficiency()<<" ";
    std::cout<<balance_tree_table.GetEfficiency()<<" ";
    std::cout<<array_hash_table.GetEfficiency()<<" ";
    std::cout<<list_hash_table.GetEfficiency()<<"\n";
    scan_table.ResetEfficiency();
    sort_table.ResetEfficiency();
    tree_table.ResetEfficiency();
    balance_tree_table.ResetEfficiency();
    array_hash_table.ResetEfficiency();
    list_hash_table.ResetEfficiency();
    mt19937 mt(time(0));
    for(int i = 0; i < n; i++) {
        std::uniform_int_distribution<int> r(0, n-i-1);
        int id = r(mt);
        scan_table.DelRecord(s[id]);
        sort_table.DelRecord(s[id]);
        tree_table.DelRecord(s[id]);
        array_hash_table.DelRecord(s[id]);
        list_hash_table.DelRecord(s[id]);
        s[id] = s[n-i-1];
        s.pop_back();
    }
    std::cout<<scan_table.GetEfficiency()<<" ";
    std::cout<<sort_table.GetEfficiency()<<" ";
    std::cout<<tree_table.GetEfficiency()<<" ";
    std::cout<<array_hash_table.GetEfficiency()<<" ";
    std::cout<<list_hash_table.GetEfficiency()<<"\n";
    return 0;
}
