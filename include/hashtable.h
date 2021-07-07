#pragma once

#include "defines.h"

#include "table.h"

class THashTable : public TTable {
  public:
    THashTable();

  protected:
    virtual uint64_t HashFunc(const TKey key);
};
