#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include "TTable.h"

class  THashTable : public TTable {
protected:
	virtual unsigned long HashFunc(const TKey key); // hash-функция
public:
	THashTable() : TTable() {} //конструктор
};

#endif