#ifndef __THASH_TABLE_H__
#define __THASH_TABLE_H__

#include "TTable.h"

class  THashTable : public TTable {
protected:
	virtual unsigned long HashFunc(const TKey key);
public:
	THashTable() : TTable() {} 
};

#endif // __THASH_TABLE_H__