#ifndef __SORTTABLE_H__
#define __SORTTABLE_H__

#include "TScanTable.h"
#include <algorithm>

enum TSortMethod { INSERT_SORT, MERGE_SORT, QUIQ_SORT };

class  TSortTable : public TScanTable {
protected:
	TSortMethod SortMethod; // метод сортировки
	void SortData();   // сортировка данных
	void InsertSort(PTTabRecord *pMem, int DataCount); // метод вставок
	void MergeSort(PTTabRecord *pMem, int DataCount);  // метод слияния
	void MergeSorter(PTTabRecord * & pData, int low, int high);
	void MergeData(PTTabRecord * & pData, int low, int high, int mid);
	void QuiqSort(PTTabRecord *pMem, int DataCount); // быстрая сортировка
	void QuiqSplit(PTTabRecord *pData, int Size, int &Pivot);
public:
	TSortTable(int Size = TabMaxSize);// конструктор
	TSortTable(const TScanTable &tab); // из просматриваемой таблицы
	TSortTable & operator=(const TScanTable &tab); // присваивание
	TSortMethod GetSortMethod();    // получить метод сортировки
	void SetSortMethod(TSortMethod sm);// установить метод сортировки
	// основные методы
	virtual PTDatValue FindRecord(TKey k); // найти запись
	virtual void InsRecord(TKey k, PTDatValue pVal); // вставить
	virtual void DelRecord(TKey k);        // удалить запись

	void Print();
};

#endif