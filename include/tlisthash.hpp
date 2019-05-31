#pragma once

#include "thashtable.hpp"
#include "tdatlist.hpp"

class TListHash : public THashTable
{
protected:
    PTDatList *pList; // records array pointer memory
    int TabSize;      // records array size
    int CurrList;     // list to search
public:
    TListHash(int Size = TABMAXSIZE);
    ~TListHash();
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
