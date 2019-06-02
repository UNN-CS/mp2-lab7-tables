#ifndef __T_TABLE_H__
#define __T_TABLE_H__

#include <iostream>
#include "ttabrecord.h"

#define TabEmpty -101
#define TabFull -102
#define TabNoRec -103
#define TabRecDbl -104
#define TabNoMem -105

class  TTable {
  protected:
    int DataCount;  // ���������� ������� � �������
    int Efficiency; // ���������� ������������� ���������� ��������
  public:
    TTable(){ DataCount=0; Efficiency=0;} // �����������
    virtual ~TTable() {}; // ����������
    // �������������� ������
    int GetDataCount () const {return DataCount;}    // �-�� �������
    int GetEfficiency () const {return Efficiency;} // �������������
    void ResetEfficiency() {Efficiency = 0;}
    int IsEmpty () const {return DataCount == 0;}   //�����?
    virtual int IsFull () const = 0;                 // ���������?
    // ������
    virtual TKey GetKey () const = 0;
    virtual PTDatValue GetValuePtr () const = 0;
    // �������� ������
    virtual PTDatValue FindRecord (TKey k) = 0; // ����� ������
    virtual void InsRecord (TKey k, PTDatValue pVal ) =0; // ��������
    virtual void DelRecord (TKey k) = 0;        // ������� ������
    // ���������
    virtual int Reset () = 0; // ���������� �� ������ ������
    virtual int IsTabEnded () const = 0; // ������� ���������?
    virtual int GoNext () = 0; // ������� � ��������� ������
    // (=1 ����� ���������� ��� ��������� ������ �������)
};

#endif // __T_TABLE_H__
