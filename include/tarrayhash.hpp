#pragma once

#include "thashtable.hpp"

#define TABHESHSTEP 1

class TArrayHash : public THashTable
{
protected:
    PTTabRecord *pRecs;
    int TabSize;
    int HashStep;
    int FreePos;
    int CurrPos;
    PTTabRecord pMark;

    int GetNextPos(int pos) { return (pos + HashStep) % TabSize; };

public:
    TArrayHash(int Size = TABMAXSIZE, int Step = TABHESHSTEP);
    ~TArrayHash();
    // misc methods
    virtual int IsFull() const override;
    // access
    virtual TKey GetKey() const override;
    virtual PTDatValue GetValuePtr() const override;
    // core methods
    virtual PTDatValue FindRecord(TKey k) override;
    virtual void InsRecord(TKey k, PTDatValue pVal) override;
    virtual void DelRecord(TKey k) override;
    // navigation
    virtual int Reset() override;
    virtual int IsTabEnded() const override;
    virtual int GoNext() override;
};
