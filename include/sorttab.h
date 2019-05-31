#ifndef __sorttab_h
#define __sorttab_h

#include "TScanTable.h"

enum SortMethod{Insert_Sort,Merge_Sort,Quick_Sort};

class SortTable : public TScanTable {
 protected:
	 SortMethod Sort; // индекс метода сортировки
	 void SortData(); // сортировка данных
	 void InsertSort(PTRecord * pMem, int DataCount); // метод вставок
	 void MergeSort(int l, int r, PTRecord * &pData, PTRecord* &pBuff);
	 void Merge(int L, int Mid, int R, PTRecord * &pData, PTRecord* &pBuff);
	 void QuickSort(PTRecord * pMem, int DataCount); // быстрая сортировка
	 void QuickSplit(PTRecord * pData, int size, int &pivot);

 public:
	 SortTable(int Size = TabMaxSize ) : TScanTable(Size) { };
	 SortTable(const TScanTable& tab);
	 SortTable& operator=(const TScanTable& tab); // присваивание
	 SortMethod GetSort() { return Sort; }
	 void SetSort(SortMethod sm) { Sort = sm; }
	 // основные методы
	 virtual PTDatValue FindRecord(TKey k); // найти запись
	 virtual void InsRecord(TKey k, PTDatValue pVal); // вставить
	 virtual void DelRecord(TKey k);        // удалить запись
};
#endif