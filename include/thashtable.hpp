#pragma once

#include "ttable.hpp"

class THashTable : public TTable
{
protected:
    virtual unsigned long HashFunc(const TKey key); // hash-function
public:
    THashTable() : TTable() {}
};
