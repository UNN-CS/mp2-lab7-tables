#include <iostream>

#include "tword.h"
#include "sorttab.h"
#include "treetab.h"
#include "baltree.h"
#include "arrhash.h"
#include "listhash.h"

int main()
{
    string s = "zxc";

    TScanTable scan_table;
    TSortTable sort_table;
    TTreeTable tree_table;
    TBalanceTree btree_table;
    TArrayHash ahash_table;
    TListHash lhash_table;

    scan_table.InsRecord(s, nullptr);
    sort_table.InsRecord(s, nullptr);
    tree_table.InsRecord(s, nullptr);
    btree_table.InsRecord(s, nullptr);
    ahash_table.InsRecord(s, nullptr);
    lhash_table.InsRecord(s, nullptr);

    scan_table.FindRecord(s);
    sort_table.FindRecord(s);
    tree_table.FindRecord(s);
    btree_table.FindRecord(s);
    ahash_table.FindRecord(s);
    lhash_table.FindRecord(s);
  
    return 0;
}









