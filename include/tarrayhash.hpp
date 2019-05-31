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
    virtual int IsFull() const;
    // access
    virtual TKey GetKey() const;
    virtual PTDatValue GetValuePtr() const;
    // core methods
    virtual PTDatValue FindRecord(TKey k);
    virtual void InsRecord(TKey k, PTDatValue pVal);
    virtual void DelRecord(TKey k);
    // navigation
    virtual int Reset();
    virtual int IsTabEnded() const;
    virtual int GoNext();
};
