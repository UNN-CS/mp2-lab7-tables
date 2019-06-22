#pragma once
#include "TTable.h"

class TTabRecord;

class  THashTable : public TTable {
  protected:
    virtual unsigned long HashFunc(const TKey key); // hash-функция
  public:
    THashTable() : TTable() {}
};	