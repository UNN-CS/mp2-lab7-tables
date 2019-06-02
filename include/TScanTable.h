// ��������������� �������
#ifndef _TSCANTABLE_H
#define _TSCANTABLE_H

#include "TArrayTable.h"

class  TScanTable : public TArrayTable {
public:
    TScanTable(int Size = TabMaxSize) : TArrayTable(Size) {};
	//�������� ������
    virtual PTDatValue FindRecord(TKey k);
    virtual void InsRecord(TKey k, PTDatValue pVal);
    virtual void DelRecord(TKey k);
};

#endif //_TSCANTABLE_H