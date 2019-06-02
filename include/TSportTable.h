#ifndef _SORTTAB_H
#define _SORTTAB_H

#include "TScanTable.h"

enum TSortMethod { INSERT_SORT, MERGE_SORT, QUICK_SORT };

class  TSortTable : public TScanTable {
protected:
	TSortMethod SortMethod; // ìåòîä ñîðòèðîâêè
	void SortData(void);   // ñîðòèðîâêà äàííûõ
	void InsertSort(PTTabRecord *pMem, int DataCount); // ìåòîä âñòàâîê
	void MergeSort(PTTabRecord *pMem, int DataCount);  // ìåòîä ñëèÿíèÿ
	void MergeSorter(PTTabRecord * &pData, PTTabRecord * &pBuff, int Size);
	void MergeData(PTTabRecord *&pData, PTTabRecord *&pBuff, int n1, int n2);
	void QuickSort(PTTabRecord *pMem, int DataCount); // áûñòðàÿ ñîðòèðîâêà
	void QuickSplit(PTTabRecord *pData, int Size, int &Pivot);
public:
	TSortTable(int Size = TabMaxSize) : TScanTable(Size) {};// êîíñòðóêòîð
	TSortTable(const TScanTable &tab); // èç ïðîñìàòðèâàåìîé òàáëèöû
	TSortTable & operator=(const TScanTable &tab); // ïðèñâàèâàíèå
	TSortMethod GetSortMethod(void) { return SortMethod; }    // ïîëó÷èòü ìåòîä ñîðòèðîâêè
	void SetSortMethod(TSortMethod sm) { SortMethod = sm; } // óñòàíîâèòü ìåòîä ñîðòèðîâêè

	// îñíîâíûå ìåòîäû
	virtual PTDatValue FindRecord(TKey k); // íàéòè çàïèñü
	virtual void InsRecord(TKey k, PTDatValue pVal); // âñòàâèòü
	virtual void DelRecord(TKey k);        // óäàëèòü çàïèñü

};
#endif 
