#ifndef SCANTABLE_H_
#define SCANTABLE_H_
#include "arraytable.h"

class TScanTable : public TArrayTable {
 public:
    TScanTable(int Size = TabMaxSize): TArrayTable(Size) {};//�����������
    // �������� ������
    virtual PTDatValue FindRecord(TKey k) override; //����� ������
    virtual void InsRecord(TKey k, PTDatValue pVal) override; //��������
    virtual void DelRecord(TKey k) override; //������� ������
};

#endif // SCANTABLE_H_
