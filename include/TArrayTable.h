// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tarraytable.h
//
// ����������� ����� ��� ������ � ����������� �������, ������ ��� ���������� ���������� �������� 

#ifndef __TARRAYTABLE_H
#define __TARRAYTABLE_H

#include "TTable.h"

#define TabMaxSize 50
enum TDataPos {FIRST_POS, CURRENT_POS, LAST_POS};

class TSortTable;

class  TArrayTable : public TTable {
  protected:
    PTTabRecord *pRecs; // ������ ��� ������� �������
    int TabSize;        // ����. ����.���������� ������� � �������
    int CurrPos;        // ����� ������� ������ (��������� � 0)
  public:
    TArrayTable(int Size = TabMaxSize); // �����������
    ~TArrayTable( ) {};                // ����������
    // �������������� ������
    virtual int IsFull ( ) const ; // ���������?
    int GetTabSize( ) const ;      // �-�� �������
    // ������
    virtual TKey GetKey (void) const;
    virtual PTDatValue GetValuePTR (void) const;
    virtual TKey GetKey (TDataPos mode) const;
    virtual PTDatValue GetValuePTR (TDataPos mode) const;
    // �������� ������
    virtual PTDatValue FindRecord (TKey k) = 0; // ����� ������
    virtual void InsRecord (TKey k, PTDatValue pVal ) = 0; // ��������
    virtual void DelRecord (TKey k) = 0;        // ������� ������
    //���������
    virtual int Reset (void);   // ���������� �� ������ ������
    virtual int IsTabEnded (void) const; // ������� ���������?
    virtual int GoNext (void) ; // ������� � ��������� ������
    //(=1 ����� ���������� ��� ��������� ������ �������)
    virtual int SetCurrentPos (int pos);// ���������� ������� ������
    int GetCurrentPos (void) const;     //�������� ����� ������� ������
  friend TSortTable;
};

#endif