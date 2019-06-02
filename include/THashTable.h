#pragma once

#include "TTable.h"

class THashTable : public TTable
{
protected:
  virtual unsigned long HashFunc(const TKey key);

public:
  THashTable() : TTable() {}
};
