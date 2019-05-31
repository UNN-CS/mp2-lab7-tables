#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include "table.h"

class THashTable : public TTable {
 protected:
    virtual unsigned long HashFunc(const TKey key); // hash-функция
 public:
    THashTable() : TTable() {} //конструктор
};

#endif // HASHTABLE_H_
