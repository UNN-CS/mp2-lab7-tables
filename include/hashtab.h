#ifndef __hash_
#define __hash_

#include "ttable.h"

class HashTable :public TTable {
protected:
	virtual unsigned long HashFunc(const TKey key);
public:
	HashTable():TTable(){}
};
#endif