class  THashTable : public TTable {
  protected:
    virtual unsigned long HashFunc(const Tkey key); // hash-�������
  public:
    THashTable() : TTable() {} //�����������
};	