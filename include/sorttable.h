#ifndef SORTTABLE_H_
#define SORTTABLE_H_
#include "scantable.h"

enum TSortMethod {INSERT_SORT, MERGE_SORT, QUICK_SORT};

class TSortTable : public TScanTable {
  protected:
    TSortMethod SortMethod; // метод сортировки
    void SortData();   // сортировка данных
    void InsertSort(PTTabRecord *pMem, int DataCount); // метод вставок
    void MergeSort(PTTabRecord *pMem, int DataCount);  // метод слияния
    void MergeSorter(PTTabRecord *a, PTTabRecord *tmp, int l, int r);
    void MergeData(PTTabRecord *a, PTTabRecord *tmp, int l, int c, int r);
    void QuickSort(PTTabRecord *pMem, int DataCount); // быстрая сортировка
    void QuickSplit(PTTabRecord *pData, int l, int r);
  public:
    TSortTable(int Size = TabMaxSize): TScanTable(Size){};// конструктор
    TSortTable(const TScanTable &tab, TSortMethod sm = QUICK_SORT); // из просматриваемой таблицы
    TSortTable &operator=(const TScanTable &tab); // присваивание
    TSortMethod GetSortMethod();    // получить метод сортировки
    void SetSortMethod(TSortMethod sm);// установить метод сортировки
    // основные методы
    virtual PTDatValue FindRecord(TKey k) override; // найти запись
    virtual void InsRecord(TKey k, PTDatValue pVal) override; // вставить
    virtual void DelRecord(TKey k) override;        // удалить запись
    void Print(std::ostream& out);
};

#endif // SORTTABLE_H_
