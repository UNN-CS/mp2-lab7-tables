#include "thashtable.h"


unsigned long THashTable::HashFunc(const TKey key) {
    unsigned long hashVal = 0;
    int len = key.length();
    for (int i = 0; i < len; i++)
        hashVal = (hashVal << 3) + key[i];
    return hashVal;
}       /*================================================*/
