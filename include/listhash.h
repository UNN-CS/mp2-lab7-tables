#pragma once

#include "defines.h"

#include "hashtable.h"

class TListHash : public THashTable {
  public:
    TListHash(int size = TabMaxSize);
    ~TListHash();

    virtual bool IsFull() const override;

    virtual TKey GetKey() const override;
    virtual PTDatValue GetValuePtr() const override;

    virtual PTDatValue FindRecord(TKey k) override;
    virtual void InsRecord(TKey k, PTDatValue pVal) override;
    virtual void DelRecord(TKey k) override;

    virtual bool Reset() override;
    virtual bool IsTabEnded() const override;
    virtual bool GoNext() override;

  protected:
    PTDatList *pList;
    int tabSize;
    int currList;
};
