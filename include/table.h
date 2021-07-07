#pragma once

#include "defines.h"

class TTable {
  public:
    TTable();
    virtual ~TTable();

    virtual bool IsFull() const = 0;

    virtual TKey GetKey() const = 0;
    virtual PTDatValue GetValuePtr() const = 0;

    virtual PTDatValue FindRecord(TKey k) = 0;
    virtual void InsRecord(TKey k, PTDatValue pVal) = 0;
    virtual void DelRecord(TKey k) = 0;

    virtual bool Reset() = 0;
    virtual bool IsTabEnded() const = 0;
    virtual bool GoNext() = 0;

    void ResetEfficiency() {
        efficiency = 0;
    }

    int GetDataCount() const;
    int GetEfficiency() const;
    bool IsEmpty() const;

  protected:
    int dataCount;
    int efficiency;
};
