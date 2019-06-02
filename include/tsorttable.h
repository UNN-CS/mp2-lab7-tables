// Упорядоченные таблицы

#pragma once

#include "tscantable.h"

#define NoSortMethod -1

enum TSortMethod {INSERT_SORT, MERGE_SORT, QUIQ_SORT};

class  TSortTable: public TScanTable {
  protected: 
    TSortMethod SortMethod;                                                     // метод сортировки
    void SortData ();                                                           // сортировка данных
    void InsertSort (PTTabRecord *pMem, int dataCount);                         // метод вставок
    void MergeSort (PTTabRecord *pMem, int dataCount);                          // метод слияния
    void MergeSorter (PTTabRecord *&pData, PTTabRecord *&pBuff, int left, int right);
    void MergeData (PTTabRecord *&pData, PTTabRecord *&pBuff, int left, int middle, int right);
    void QuiqSort (PTTabRecord *pMem, int DataCount);                           // быстрая сортировка
    void QuiqSplit (PTTabRecord *pData, int left, int right);

  public:
    TSortTable(int size = TabMaxSize): TScanTable(size) {};                     // конструктор
    TSortTable(const TScanTable &tab);                                          // из просматриваемой таблицы
    TSortTable & operator = (const TScanTable &tab);                            // присваивание
    TSortMethod GetSortMethod();                                                // получить метод сортировки
    void SetSortMethod (TSortMethod sm);                                        // установить метод сортировки

    // основные методы
    virtual PTDatValue FindRecord (TKey k);                                     // найти запись
    virtual void InsRecord (TKey k, PTDatValue pVal );                          // вставить
    virtual void DelRecord (TKey k) ;                                           // удалить запись
};
