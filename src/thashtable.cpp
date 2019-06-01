#include "thashtable.hpp"

unsigned long THashTable::HashFunc(const TKey key)
{
    unsigned long hashval = 0;

    for (unsigned int i = 0; i < key.size(); ++i)
        hashval = (hashval << 3) + key[i];

    return hashval;
}
