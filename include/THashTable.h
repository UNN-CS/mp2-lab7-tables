#pragma once

#include "TTable.h"

class  THashTable : public TTable {
protected:
	virtual unsigned int HashFunc(const TKey key); // hash-функция
public:
	THashTable() : TTable() {} //конструктор
};
