#ifndef __T_HASH_TABLE__
#define __T_HASH_TABLE__

class  THashTable : public TTable {
  protected:
    virtual unsigned long HashFunc(const Tkey key); // hash-функция
  public:
    THashTable() : TTable() {} //конструктор
};

#endif // __T_HASH_TABLE__
