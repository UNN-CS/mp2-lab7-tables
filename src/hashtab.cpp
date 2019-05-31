#include "hashtab.h"
#include "string.h"

unsigned long HashTable::HashFunc(const TKey key) {
	unsigned long hashlvl = 0;
	int Len = key.length();
	for (int i = 0; i < Len; ++i)
		hashlvl = (hashlvl << 3) + key[i];
	return hashlvl;
}