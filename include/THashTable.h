// базовый класс для таблиц с вичислимым входом
#ifndef _THASHTABLE_H
#define _THASHTABLE_H

#include "TTable.h"

class  THashTable : public TTable {
protected:
    virtual unsigned long HashFunc(const TKey key); 
public:
    THashTable() : TTable() {} 
};

#endif //_THASHTABLE_H