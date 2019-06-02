// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tscantable.h
//
// �������, �������������� ���������� ��������������� ������

#ifndef __TSCANTABLE_H
#define __TSCANTABLE_H

#include "TArrayTable.h"

class  TScanTable: public TArrayTable {
  public:
    TScanTable(int Size=TabMaxSize): TArrayTable(Size){};//�����������
    // �������� ������
    virtual PTDatValue FindRecord (TKey k) ;//����� ������
    virtual void InsRecord (TKey k, PTDatValue pVal ) ;//��������
    virtual void DelRecord (TKey k) ;//������� ������
};

#endif