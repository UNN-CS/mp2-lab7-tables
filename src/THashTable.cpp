// THashTable.cpp
#include "THashTable.h"

unsigned long THashTable::HashFunc(const TKey key) {
    unsigned long hashval = 0;
    int len = key.length();
    for (int i = 0; i < len; ++i)
        hashval = (hashval << 3) + key[i];
    return hashval;
}
