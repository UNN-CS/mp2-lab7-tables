#ifndef __TTABRECORD_H
#define __TTABRECORD_H

#include "datvalue.h"

using namespace std;

typedef string TKey; // ��� ����� ������

// ����� ��������-�������� ��� ������� �������
class TTabRecord : public TDatValue {  
 protected:    // ����    
    TKey Key;   // ���� ������
    PTDatValue pValue;   // ��������� �� ��������
 public:  // ������
     TTabRecord(TKey k = "", PTDatValue pVal = nullptr) : Key(k), pValue(pVal) {} // �����������
     void SetKey(TKey k) { Key = k; } // ���������� �������� �����
     TKey GetKey(void) { return Key; }  // �������� �������� �����
     void SetValuePtr(PTDatValue p) { pValue = p; } // ���������� ��������� �� ������
     PTDatValue GetValuePtr(void) { return pValue; } // �������� ��������� �� ������
     virtual TDatValue * GetCopy(); // ���������� �����
     TTabRecord & operator = (TTabRecord &tr);// ������������
     virtual int operator == (const TTabRecord &tr) { return Key == tr.Key; } // ��������� =
     virtual int operator < (const TTabRecord &tr) { return Key > tr.Key; }  // ��������� �<�
     virtual int operator > (const TTabRecord &tr) { return Key < tr.Key; }  // ��������� �>�
  //������������� ������ ��� ��������� ����� ������, ��. �����
     friend class TArrayTable;
     friend class TScanTable;
     friend class TSortTable;
     friend class TTreeNode;
     friend class TTreeTable;
     friend class TArrayHash;
     friend class TListHash;
};

typedef TTabRecord* PTTabRecord;

#endif 

