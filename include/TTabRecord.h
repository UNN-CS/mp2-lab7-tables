// ����, ���, ���� "������ ����������������-2", �++, ���
//
// ttabrecord.h
//
// ����� ��������-�������� ��� ������� �������

#ifndef __TTABRECORD_H
#define __TTABRECORD_H

#include <string>
#include "TDatValue.h"

class  TTabRecord;
typedef  TTabRecord *PTTabRecord;

typedef std::string TKey;     // ��� ����� ������

class TTabRecord : public TDatValue {  
protected:    // ����    
	TKey Key;   // ���� ������
    PTDatValue pValue;   // ��������� �� ��������
public:  // ������
    TTabRecord (TKey k = "", PTDatValue pVal = nullptr); // ����������� 
    void SetKey(TKey k);// ���������� �������� �����
    TKey GetKey(void) const;  // �������� �������� �����
    void SetValuePtr(PTDatValue p);// ���������� ��������� �� ������
    PTDatValue GetValuePTR (void) const; // �������� ��������� �� ������
    virtual TDatValue * GetCopy(); // ���������� �����
    TTabRecord & operator = (TTabRecord &tr);// ������������
    virtual int operator == (const TTabRecord &tr); // ��������� =
    virtual int operator < (const TTabRecord &tr);  // ��������� �<�
    virtual int operator > (const TTabRecord &tr);  // ��������� �>�
//������������� ������ ��� ��������� ����� ������, ��. �����
  friend class TArrayTable;
  friend class TScanTable;
  friend class TSortTable;
  friend class TTreeNode;
  friend class TTreeTable;
  friend class TArrayHash;
  friend class TListHash;
};

#endif