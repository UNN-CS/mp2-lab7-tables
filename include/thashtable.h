#ifndef __T_HASH_TABLE__
#define __T_HASH_TABLE__

#include "ttable.h"

class  THashTable : public TTable {
  protected:
    virtual unsigned int HashFunc(const TKey key); // hash-�������
  public:
    THashTable() : TTable() {} //�����������
};

#endif // __T_HASH_TABLE__
