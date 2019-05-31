#pragma once

#include "tarraytable.hpp"

class TScanTable : public TArrayTable
{
public:
    TScanTable(int Size = TABMAXSIZE) : TArrayTable(Size){};
    // core methods
    virtual PTDatValue FindRecord(TKey k) override;
    virtual void InsRecord(TKey k, PTDatValue pVal) override;
    virtual void DelRecord(TKey k) override;
};
