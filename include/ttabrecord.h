#ifndef __T_TAB_RECORD_H__
#define __T_TAB_RECORD_H__

#include "tdatvalue.h"
#include <iostream>

typedef std::string TKey;     // ��� ����� ������
// ����� ��������-�������� ��� ������� �������
class TTabRecord : public TDatValue {
  protected:    // ����
    TKey Key;   // ���� ������
    PTDatValue pValue;   // ��������� �� ��������
  public:  // ������
    TTabRecord (TKey k="", PTDatValue pVal = nullptr);// �����������
    void SetKey(TKey k);// ���������� �������� �����
    TKey GetKey();  // �������� �������� �����
    void SetValuePtr(PTDatValue p);// ���������� ��������� �� ������
    PTDatValue GetValuePtr (); // �������� ��������� �� ������
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

typedef TTabRecord* PTTabRecord;
#endif // __T_TAB_RECORD_H__
