#pragma once

#include "tscantable.hpp"

enum TSortMethod
{
    INSERT_SORT,
    MERGE_SORT,
    QUICK_SORT
};

class TSortTable : public TScanTable
{
protected:
    TSortMethod SortMethod;
    // sort methods
    void SortData();
    void InsertSort(PTTabRecord *pMem, int DataCount);
    void MergeSort(PTTabRecord *pMem, int DataCount);
    void MergeSorter(PTTabRecord *a, PTTabRecord *tmp, int l, int r);
    void MergeData(PTTabRecord *a, PTTabRecord *tmp, int l, int c, int r);
    void QuickSort(PTTabRecord *pMem, int DataCount);
    void QuickSplit(PTTabRecord *pData, int l, int r);

public:
    TSortTable(int Size = TABMAXSIZE) : TScanTable(Size){};
    TSortTable(const TScanTable &tab, TSortMethod sm = QUICK_SORT);
    // misc methods
    TSortMethod GetSortMethod();
    void SetSortMethod(TSortMethod sm);
    // core methods
    virtual PTDatValue FindRecord(TKey k) override;
    virtual void InsRecord(TKey k, PTDatValue pVal) override;
    virtual void DelRecord(TKey k) override;
    void Print(std::ostream &out);
    // comparison methods
    TSortTable &operator=(const TScanTable &tab);
};
