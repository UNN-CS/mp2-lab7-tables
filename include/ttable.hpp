#pragma once

#include "ttabrecord.hpp"

#define TABMAXSIZE 500

class TTable
{
protected:
    int DataCount;  // records count
    int Efficiency; // efficiency of the current operation
public:
    TTable()
    {
        DataCount = 0;
        Efficiency = 0;
    }
    virtual ~TTable(){};
    // misc metods
    int GetDataCount() const { return DataCount; }
    int GetEfficiency() const { return Efficiency; }
    void ResetEfficiency() { Efficiency = 0; }

    int IsEmpty() const { return DataCount == 0; }
    virtual int IsFull() const = 0;
    // access
    virtual TKey GetKey() const = 0;
    virtual PTDatValue GetValuePtr() const = 0;
    // core methods
    virtual PTDatValue FindRecord(TKey k) = 0;
    virtual void InsRecord(TKey k, PTDatValue pVal) = 0;
    virtual void DelRecord(TKey k) = 0;
    // navigation
    virtual int Reset() = 0;            // set pointer to the first record
    virtual int IsTabEnded() const = 0; // is table finished
    virtual int GoNext() = 0;           // switch to the next record(returns 1 on the last record)
};
