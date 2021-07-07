#pragma once

#include "defines.h"

#include "arraytable.h"

class TScanTable : public TArrayTable {
  public:
    TScanTable(int size = TabMaxSize);

    virtual PTDatValue FindRecord(TKey k) override;
    virtual void InsRecord(TKey k, PTDatValue pVal) override;
    virtual void DelRecord(TKey k) override;
};
