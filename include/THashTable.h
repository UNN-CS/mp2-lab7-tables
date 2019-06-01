// THashTable.h
#ifndef _HASHTAB_H
#define _HASHTAB_H
#include "TTable.h"
class  THashTable : public TTable {
protected:
    virtual unsigned long HashFunc(const TKey key); // hash-функция
public:
    THashTable() : TTable() {} //конструктор
};

#endif
