#include "THashTable.h"

unsigned long THashTable::HashFunc(const TKey key) {
    unsigned long hashlval = 0;
    int Len = key.length();
    for (int i = 0; i < Len; i++)
        hashlval = (hashlval << 3) + key[i];
    return hashlval;
}