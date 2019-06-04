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

	vector<string> num;
	num.resize(15);
	TScanTable scan_table;
	TSortTable sort_table;
	TTreeTable tree_table;
	TBalanceTree btree_table;
	TArrayHash ahash_table;
	TListHash lhash_table;
	ifstream in("D:/numbers.txt");
	if (!in.is_open()) return 0;
	int size = 14;
	for (int i = 0; i < size; ++i) {
		string s;
		getline(in, s, '\n');
		cout << s << endl;
		num[i] = s;
		scan_table.InsRecord(s, nullptr);
		sort_table.InsRecord(s, nullptr);
		tree_table.InsRecord(s, nullptr);
		btree_table.InsRecord(s, nullptr);
		ahash_table.InsRecord(s, nullptr);
		lhash_table.InsRecord(s, nullptr);
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

	for (int i = 0; i < size; ++i) {
		scan_table.FindRecord(num[i]);
		sort_table.FindRecord(num[i]);
		tree_table.FindRecord(num[i]);
		btree_table.FindRecord(num[i]);
		ahash_table.FindRecord(num[i]);
		lhash_table.FindRecord(num[i]);
	}

	cout << "Find: " << endl;
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
	for (int i = 0; i < size; i++) {
		scan_table.DelRecord(num[i]);
		sort_table.DelRecord(num[i]);
		tree_table.DelRecord(num[i]);
		btree_table.DelRecord(num[i]);
		ahash_table.DelRecord(num[i]);
		lhash_table.DelRecord(num[i]);
	}
	cout << "Delete: " << endl;
	cout << "scan_table: " << scan_table.GetEfficiency() << endl;
	cout << "sort_table: " << sort_table.GetEfficiency() << endl;
	cout << "tree_table: " << tree_table.GetEfficiency() << endl;
	cout << "btree_table: " << btree_table.GetEfficiency() << endl;
	cout << "ahash_table: " << ahash_table.GetEfficiency() << endl;
	cout << "lhash_table: " << lhash_table.GetEfficiency() << endl;

	return 0;
}