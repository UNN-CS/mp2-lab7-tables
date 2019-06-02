#include "thashtable.h"

unsigned int THashTable::HashFunc(const TKey key) {
    unsigned int hashval = 0;
    int Len = key.length();
    for(int i = 0; i < Len; i++)
        hashval = (hashval<<3) + key[i];
    return hashval;
}
