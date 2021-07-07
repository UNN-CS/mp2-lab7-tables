#pragma once

#include "defines.h"

#include "scantable.h"

class TSortTable : public TScanTable {
  public:
    TSortTable(int size = TabMaxSize);
    TSortTable(const TScanTable &tab);

    virtual PTDatValue FindRecord(TKey k) override;
    virtual void InsRecord(TKey k, PTDatValue pVal) override;
    virtual void DelRecord(TKey k) override;

    TSortTable & operator=(const TScanTable &tab);
    TSortMethod GetSortMethod();
    void SetSortMethod(TSortMethod sm);

  protected:
    void SortData();

    void InsertSort(PTTabRecord *pMem, int dataCount);

    void MergeSort(PTTabRecord *pMem, int dataCount);
    void MergeSorter(PTTabRecord *&pData, PTTabRecord *&pBuff, int size);
    void MergeData(PTTabRecord *&pData, PTTabRecord *&pBuff, int n1, int n2);

    void QuickSort(PTTabRecord *pMem, int dataCount);
    void QuickSplit(PTTabRecord *pData, int size, int &pivot);

    TSortMethod sortMethod;
};
