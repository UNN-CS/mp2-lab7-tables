// TSortTable.h 
#ifndef _SORTTAB_H
#define _SORTTAB_H

#include "TArrayTable.h"
#include "TScanTable.h"

enum TSortMethod { INSERT_SORT, MERGE_SORT, QUIQ_SORT };
class  TSortTable : public TScanTable {
protected:
    TSortMethod SortMethod; // метод сортировки
    void SortData();   // сортировка данных
    void InsertSort(PTTabRecord *pMem, int DataCount); // метод вставок
    void MergeSort(PTTabRecord *pMem, int DataCount);  // метод слияния
    void MergeSorter(PTTabRecord * &pData, PTTabRecord * &pBuff, int Size);
    void MergeData(PTTabRecord *&pData, PTTabRecord *&pBuff, int n1, int n2);
    void QuiqSort(PTTabRecord *pMem, int DataCount); // быстрая сортировка
    void QuiqSplit(PTTabRecord *pData, int Size, int &Pivot);
public:
    TSortTable(int Size = TabMaxSize) : TScanTable(Size) { SortMethod = TSortMethod::QUIQ_SORT; }// конструктор
    TSortTable(const TScanTable &tab, TSortMethod sm);
    TSortTable & operator=(const TScanTable &tab); // присваивание
    TSortMethod GetSortMethod(void) { return SortMethod; }   // получить метод сортировки
    void SetSortMethod(TSortMethod sm) { SortMethod = sm; }// установить метод сортировки
    // основные методы
    virtual PTDatValue FindRecord(TKey k); // найти запись
    virtual void InsRecord(TKey k, PTDatValue pVal); // вставить
    virtual void DelRecord(TKey k);        // удалить запись
};

#endif