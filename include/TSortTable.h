// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tsorttable.h
//
// ���������� ������������� ������

#ifndef __TSORTTABLE_H
#define __TSORTTABLE_H

#include "TArrayTable.h"
#include "TScanTable.h"

enum TSortMethod {INSERT_SORT, MERGE_SORT, QUIQ_SORT};
class  TSortTable: public TScanTable {
  protected: 
    TSortMethod SortMethod; // ����� ����������
    void SortData (void);   // ���������� ������
    void InsertSort (PTTabRecord *pMem, int DataCount); // ����� �������
    void MergeSort (PTTabRecord *pMem, int DataCount);  // ����� �������
    void MergeSorter (PTTabRecord * &pData,int left,int right);
    void MergeData (PTTabRecord *&pData,int left,int mid,int right);
    void QuiqSort (PTTabRecord *pMem, int DataCount); // ������� ����������
    void QuiqSplit (PTTabRecord *&pData, int low, int high);
  public:
    TSortTable(int Size=TabMaxSize): TScanTable(Size){};// �����������
    TSortTable(const TScanTable &tab); // �� ��������������� �������
    TSortTable & operator=(const TScanTable &tab); // ������������
    TSortMethod GetSortMethod(void);    // �������� ����� ����������
    void SetSortMethod (TSortMethod sm);// ���������� ����� ����������
    // �������� ������
    virtual PTDatValue FindRecord (TKey k) ; // ����� ������
    virtual void InsRecord (TKey k, PTDatValue pVal ) ; // ��������
    virtual void DelRecord (TKey k) ;        // ������� ������
};

#endif