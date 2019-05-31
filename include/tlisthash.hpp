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
