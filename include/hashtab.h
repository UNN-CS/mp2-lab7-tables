#ifndef __HASHTAB_H
#define __HASHTAB_H

#include "ttable.h"

class  THashTable : public TTable {
protected:
    virtual unsigned long HashFunc(const TKey key); // hash-функция
public:
    THashTable() : TTable() {} //конструктор
};

#endif
