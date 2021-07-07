#pragma once

#include "defines.h"

#include "hashtable.h"

class TArrayHash : public THashTable {
  public:
    TArrayHash(int size = TabMaxSize, int step = TabHashStep);
    ~TArrayHash();

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
    int GetNextPos(int pos);

    PTTabRecord *pRecs;
    int tabSize;
    int hashStep;
    int freePos;
    int currPos;
    PTTabRecord pMark;
};
