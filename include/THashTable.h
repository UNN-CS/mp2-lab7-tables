// ����, ���, ���� "������ ����������������-2", �++, ���
//
// thashtable.h
//
// ������� ����� ��� ������ � ���������� ������

#ifndef __THASHTABLE_H
#define __THASHTABLE_H

#include "TTable.h"

class  THashTable : public TTable {
  protected:
    virtual unsigned long HashFunc(const TKey key); // hash-�������
  public:
    THashTable() : TTable() {} //�����������
};

#endif