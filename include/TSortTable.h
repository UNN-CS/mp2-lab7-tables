#ifndef __T_SORT_TABLE__
#define __T_SORT_TABLE__

#include "tscantable.h"

enum TSortMethod { INSERT_SORT, MERGE_SORT, QUICK_SORT };

class TSortTable : public TScanTable {
protected:
	TSortMethod SortMethod; // ìåòîä ñîðòèðîâêè
	void SortData();   // ñîðòèðîâêà äàííûõ
	void InsertSort(PTTabRecord *pMem, int DataCount); // ìåòîä âñòàâîê
	void MergeSort(PTTabRecord *pMem, int DataCount);  // ìåòîä ñëèÿíèÿ
	void MergeSorter(PTTabRecord *a, PTTabRecord *tmp, int l, int r);
	void MergeData(PTTabRecord *a, PTTabRecord *tmp, int l, int c, int r);
	void QuickSort(PTTabRecord *pMem, int DataCount); // áûñòðàÿ ñîðòèðîâêà
	void QuickSplit(PTTabRecord *pData, int l, int r);
public:
	TSortTable(int Size = TabMaxSize) : TScanTable(Size) {};// êîíñòðóêòîð
	TSortTable(const TScanTable &tab, TSortMethod sm = QUICK_SORT); // èç ïðîñìàòðèâàåìîé òàáëèöû
	TSortTable &operator=(const TScanTable &tab); // ïðèñâàèâàíèå
	TSortMethod GetSortMethod();    // ïîëó÷èòü ìåòîä ñîðòèðîâêè
	void SetSortMethod(TSortMethod sm);// óñòàíîâèòü ìåòîä ñîðòèðîâêè
									   // îñíîâíûå ìåòîäû
	virtual PTDatValue FindRecord(TKey k) override; // íàéòè çàïèñü
	virtual void InsRecord(TKey k, PTDatValue pVal) override; // âñòàâèòü
	virtual void DelRecord(TKey k) override;        // óäàëèòü çàïèñü
	void Print(std::ostream& out);
};


#endif //__T_SCAN_TABLE__
