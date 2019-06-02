#ifndef __T_SCAN_TABLE_H__
#define __T_SCAN_TABLE_H__

#include "tarraytable.h"

class  TScanTable: public TArrayTable {
  public:
    TScanTable(int Size=TabMaxSize): TArrayTable(Size){};//�����������
    // �������� ������
    virtual PTDatValue FindRecord (TKey k) ;//����� ������
    virtual void InsRecord (TKey k, PTDatValue pVal ) ;//��������
    virtual void DelRecord (TKey k) ;//������� ������

};

#endif // __T_SCAN_TABLE_H__
