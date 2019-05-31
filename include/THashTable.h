#ifndef __T_HASH_TABLE_H__
#define __T_HASH_TABLE_H__

#include "TTable.h"
#include "TTabRecord.h"

class  THashTable : public TTable {
  protected:
    virtual unsigned long HashFunc(const TKey key); // hash-�������
  public:
    THashTable() : TTable() {} //�����������
};

#endif //__T_HASH_TABLE_H__
