// Упорядоченные таблицы
#ifndef _TSORTTABLE_H
#define _TSORTTABLE_H

//#include "TArrayTable.h"
#include "TScanTable.h"

enum TSortMethod { INSERT_SORT, MERGE_SORT, QUICK_SORT };
class  TSortTable : public TScanTable {
protected:
    TSortMethod SortMethod; 
    void SortData();  
    void InsertSort(PTTabRecord *pMem, int DataCount);  // метод вставок
    void MergeSort(PTTabRecord *pMem, int DataCount);  // метод слияния
    void MergeSorter(PTTabRecord * &pData, PTTabRecord * &pBuff, int Size);
    void MergeData(PTTabRecord *&pData, PTTabRecord *&pBuff, int n1, int n2);
    void QuickSort(PTTabRecord *pMem, int DataCount); //быстрая сортировка
    void QuickSplit(PTTabRecord *pData, int Size, int &Pivot);
public:
    TSortTable(int Size = TabMaxSize) : TScanTable(Size) { SortMethod = TSortMethod::QUICK_SORT; }
    TSortTable(const TScanTable &tab, TSortMethod sm);
    TSortTable & operator=(const TScanTable &tab); 
    TSortMethod GetSortMethod(void) { return SortMethod; }   
    void SetSortMethod(TSortMethod sm) { SortMethod = sm; }
	//основные методы
    virtual PTDatValue FindRecord(TKey k); 
    virtual void InsRecord(TKey k, PTDatValue pVal); 
    virtual void DelRecord(TKey k);       
};

#endif //_TSORTTABLE_H