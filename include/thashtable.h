#ifndef __THASHTABLE_H__
#define __THASHTABLE_H__
#include "ttable.h"

class THashTable : public TTable {
 protected:
    virtual unsigned long HashFunc(const TKey key); // hash-функция
 public:
    THashTable() : TTable() {} //конструктор
};

#endif // __THASHTABLE_H__
