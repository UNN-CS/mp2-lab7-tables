#pragma once

#include "defines.h"

#include "table.h"

class TArrayTable : public TTable {
  public:
    TArrayTable(int size = TabMaxSize);
    virtual ~TArrayTable();

    virtual bool IsFull() const override;
    virtual TKey GetKey() const override;
    virtual PTDatValue GetValuePtr() const override;

    virtual bool Reset() override;
    virtual bool IsTabEnded() const override;
    virtual bool GoNext() override;

    int GetTabSize() const;

    virtual TKey GetKey(TDataPos mode) const;
    virtual PTDatValue GetValuePtr(TDataPos mode) const;

    // virtual PTDatValue FindRecord(TKey k) = 0;
    // virtual void InsRecord(TKey k, PTDatValue pVal ) = 0;
    // virtual void DelRecord(TKey k) = 0;

    virtual bool SetCurrentPos(int pos);
    int GetCurrentPos() const;

  protected:
    PTTabRecord *pRecs;
    int tabSize;
    int currPos;

    friend TSortTable;
};
