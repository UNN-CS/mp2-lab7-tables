#include "hashtable.h"

THashTable::THashTable() : TTable() {}

uint64_t THashTable::HashFunc(const TKey k) {
    uint64_t hash = 0;

    for (char ch : k) {
        hash = ((hash << 5) + hash) + (uint64_t)ch;
    }

    return hash;
}
