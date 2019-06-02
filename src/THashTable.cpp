#include "THashTable.h"

unsigned long THashTable::HashFunc(const TKey key)
{
    unsigned long hashVal = 0;
    for (int i = 0; i < key.length(); i++)
        hashVal = (hashVal << 3) + key[i];
    return hashVal;
}