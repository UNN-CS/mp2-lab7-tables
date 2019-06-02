#ifndef __TABLE_H__
#define __TABLE_H__

#include "ttabrecord.h"

#define TabMaxSize 25

class TTable {
protected:
    int DataCount;
    int Efficiency;
public:
    TTable() {
        DataCount = 0;
        Efficiency = 0;
    }
    virtual ~TTable() {};
    int GetDataCount() const { return DataCount; }
    int GetEfficiency() const { return Efficiency; }
    void ResetEfficiency() { Efficiency = 0; }
    int IsEmpty() const { return DataCount == 0; }
    virtual int IsFull() const = 0;
    virtual TKey GetKey() const = 0;
    virtual PTDatValue GetValuePtr() const = 0;
    virtual PTDatValue FindRecord(TKey k) = 0;
    virtual void InsRecord(TKey k, PTDatValue pVal) = 0;
    virtual void DelRecord(TKey k) = 0;
    virtual int Reset() = 0;
    virtual int IsTabEnded() const = 0;
    virtual int GoNext() = 0;
};

#endif
