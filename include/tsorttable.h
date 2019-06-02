#ifndef __SORTTABLE_H__
#define __SORTTABLE_H__

#include "tscantable.h"

enum TSortMethod { INSERT_SORT, MERGE_SORT, QUICK_SORT };

class TSortTable: public TScanTable {
protected:
    TSortMethod SortMethod;
    void SortData();
    void InsertSort(PTTabRecord* pMem, int DataCount);
    void MergeSort(PTTabRecord* pMem, int DataCount);
    void MergeSorter(PTTabRecord*& pData, PTTabRecord*& pBuff, int Size);
    void MergeData(PTTabRecord*& pData, PTTabRecord*& pBuff, int n1, int n2);
    void QuickSort(PTTabRecord* pMem, int DataCount);
    void QuickSplit(PTTabRecord* pData, int l, int r);
public:
    TSortTable(int Size = TabMaxSize): TScanTable(Size) {};
    TSortTable(const TScanTable& tab, TSortMethod sm = QUICK_SORT);
    TSortTable& operator=(const TScanTable& tab);
    TSortMethod GetSortMethod();
    void SetSortMethod(TSortMethod sm);
    virtual PTDatValue FindRecord(TKey k);
    virtual void InsRecord(TKey k, PTDatValue pVal);
    virtual void DelRecord(TKey k);
};

#endif
