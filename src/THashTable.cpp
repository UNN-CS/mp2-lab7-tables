#include "THashTable.h"

unsigned long THashTable::HashFunc(const TKey key)
{
	unsigned long tmpval = 0;
	int Len = key.length();
	for (int i = 0;i < Len;i++)
		tmpval = (tmpval << 3) + key[i];
	return tmpval;
}