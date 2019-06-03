#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include "ttable.h"

class THashTable: public TTable {
protected:
    virtual unsigned long HashFunc(const TKey key);
public:
    THashTable(): TTable() {}
};

#endif
