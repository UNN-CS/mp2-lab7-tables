#ifndef __SORTTABLE_H__
#define __SORTTABLE_H__

#include "TScanTable.h"
#include <algorithm>

enum TSortMethod { INSERT_SORT, MERGE_SORT, QUIQ_SORT };

class  TSortTable : public TScanTable {
protected:
	TSortMethod SortMethod; // ����� ����������
	void SortData();   // ���������� ������
	void InsertSort(PTTabRecord *pMem, int DataCount); // ����� �������
	void MergeSort(PTTabRecord *pMem, int DataCount);  // ����� �������
	void MergeSorter(PTTabRecord * & pData, int low, int high);
	void MergeData(PTTabRecord * & pData, int low, int high, int mid);
	void QuiqSort(PTTabRecord *pMem, int DataCount); // ������� ����������
	void QuiqSplit(PTTabRecord *pData, int Size, int &Pivot);
public:
	TSortTable(int Size = TabMaxSize);// �����������
	TSortTable(const TScanTable &tab); // �� ��������������� �������
	TSortTable & operator=(const TScanTable &tab); // ������������
	TSortMethod GetSortMethod();    // �������� ����� ����������
	void SetSortMethod(TSortMethod sm);// ���������� ����� ����������
	// �������� ������
	virtual PTDatValue FindRecord(TKey k); // ����� ������
	virtual void InsRecord(TKey k, PTDatValue pVal); // ��������
	virtual void DelRecord(TKey k);        // ������� ������

	void Print();
};

#endif