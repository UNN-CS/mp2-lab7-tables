#ifndef __T_HASH_TABLE_H__
#define __T_HASH_TABLE_H__

#include "TTable.h"

class THashTable : public TTable {
protected:
	virtual unsigned long HashFunc(const TKey key); // hash-ôóíêöèÿ
public:
	THashTable() : TTable() {} //êîíñòðóêòîð
};

#endif //__T_HASH_TABLE_H__
