#pragma once

#include "ttable.hpp"

enum TDataPos
{
    FIRST_POS,
    CURRENT_POS,
    LAST_POS
};

class TArrayTable : public TTable
{
protected:
    PTTabRecord *pRecs; // record memory
    int TabSize;        // max records count
    int CurrPos;        // current record number
public:
    TArrayTable(int Size = TABMAXSIZE);
    ~TArrayTable();

    // misc methods
    virtual int IsFull() const override;
    int GetTabSize() const;
    // access
    virtual TKey GetKey() const override;
    virtual PTDatValue GetValuePtr() const override;
    virtual TKey GetKey(TDataPos mode) const;
    virtual PTDatValue GetValuePtr(TDataPos mode) const;
    // core methods
    virtual PTDatValue FindRecord(TKey k) override = 0;
    virtual void InsRecord(TKey k, PTDatValue pVal) override = 0;
    virtual void DelRecord(TKey k) override = 0;
    // navigation
    virtual int Reset() override;
    virtual int IsTabEnded() const override;
    virtual int GoNext() override;

    virtual int SetCurrentPos(int pos);
    int GetCurrentPos() const;

    friend class TSortTable;
};
