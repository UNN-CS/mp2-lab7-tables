#ifndef __T_ARRAY_TABLE_H__
#define __T_ARRAY_TABLE_H__

#include "ttable.h"

#define TabMaxSize 25
enum TDataPos {FIRST_POS, CURRENT_POS, LAST_POS};

class TArrayTable : public TTable {
  protected:
    PTTabRecord *pRecs; // ������ ��� ������� �������
    int TabSize;        // ����. ����.���������� ������� � �������
    int CurrPos;        // ����� ������� ������ (��������� � 0)
  public:
    TArrayTable(int Size=TabMaxSize); // �����������
    ~TArrayTable();                // ����������
    // �������������� ������
    virtual int IsFull () const ; // ���������?
    int GetTabSize() const ;      // �-�� �������
    // ������
    virtual TKey GetKey () const;
    virtual PTDatValue GetValuePtr () const;
    virtual TKey GetKey (TDataPos mode) const;
     virtual PTDatValue GetValuePtr (TDataPos mode) const;
    // �������� ������
    virtual PTDatValue FindRecord (TKey k) = 0; // ����� ������
    virtual void InsRecord (TKey k, PTDatValue pVal ) = 0; // ��������
    virtual void DelRecord (TKey k) = 0;        // ������� ������
    //���������
    virtual int Reset ();   // ���������� �� ������ ������
    virtual int IsTabEnded () const; // ������� ���������?
    virtual int GoNext () ; // ������� � ��������� ������
    //(=1 ����� ���������� ��� ��������� ������ �������)
    virtual int SetCurrentPos (int pos);// ���������� ������� ������
    int GetCurrentPos () const;     //�������� ����� ������� ������
  friend class TSortTable;
};

#endif // __T_ARRAY_TABLE_H__
