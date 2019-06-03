#include "thashtable.hpp"

unsigned long THashTable::HashFunc(const TKey key)
{
    long long hash = 0;
    long long koef = 1;

    for (char i:key)
    {
        hash = (koef * i + hash) % 15000000001;
        koef = (koef * 1009) % 15000000001;
    }
    
    return hash;
}
