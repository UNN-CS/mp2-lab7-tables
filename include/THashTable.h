#ifndef __THASH_TABLE_H__
#define __THASH_TABLE_H__

#include "TTable.h"

class  THashTable : public TTable {
  protected:
    virtual unsigned long HashFunc(const TKey key); // hash-функция
  public:
    THashTable() : TTable() {} //конструктор
};

#endif // __THASH_TABLE_H__
