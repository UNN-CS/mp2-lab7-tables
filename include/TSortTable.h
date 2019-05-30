﻿#ifndef __T_SORT_TABLE__
#define __T_SORT_TABLE__

#include "TScanTable.h"

enum TSortMethod {INSERT_SORT, MERGE_SORT, QUICK_SORT};
class  TSortTable: public TScanTable {
  protected:
    TSortMethod SortMethod; // метод сортировки
    void SortData (void);   // сортировка данных
    void InsertSort (PTTabRecord *pMem, int DataCount); // метод вставок
    void MergeSort (PTTabRecord *pMem, int DataCount);  // метод слияния
    void MergeSorter (PTTabRecord * &pData,PTTabRecord * &pBuff,int Size);
    void MergeData (PTTabRecord *&pData,PTTabRecord *&pBuff,int n1,int n2);
    void QuickSort (PTTabRecord *pMem, int DataCount); // быстрая сортировка
    void QuickSplit (PTTabRecord *pData, int Size, int &Pivot);
  public:
    TSortTable(int Size = TabMaxSize): TScanTable(Size){}// конструктор
    TSortTable(const TScanTable &tab); // из просматриваемой таблицы
    TSortTable & operator=(const TScanTable &tab); // присваивание
    TSortMethod GetSortMethod(void);    // получить метод сортировки
    void SetSortMethod (TSortMethod sm);// установить метод сортировки
    // основные методы
    virtual PTDatValue FindRecord (TKey k) ; // найти запись
    virtual void InsRecord (TKey k, PTDatValue pVal ) ; // вставить
    virtual void DelRecord (TKey k) ;        // удалить запись
};

#endif //__T_SCAN_TABLE__
