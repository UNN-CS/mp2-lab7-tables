#ifndef __SCANTAB_H
#define __SCANTAB_H

#include "TArrayTable.h"    

class TScanTable : public TArrayTable {
 public:
 TScanTable (int size = TabMaxSize) : TArrayTable(size) {}
 // �������� ������
 virtual PTDatValue FindRecord (TKey k); // ����� ������ � ������� ��������� �� ��������
 virtual void InsRecord (TKey k, PTDatValue val); // �������� 
 virtual void DelRecord (TKey k); // ������� ������
};
#endif                                                                                                                                                                                                                                                                                                                                                               