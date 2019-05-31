#ifndef __sorttab_h
#define __sorttab_h

#include "TScanTable.h"

enum SortMethod{Insert_Sort,Merge_Sort,Quick_Sort};

class SortTable : public TScanTable {
 protected:
	 SortMethod Sort; // ������ ������ ����������
	 void SortData(); // ���������� ������
	 void InsertSort(PTRecord * pMem, int DataCount); // ����� �������
	 void MergeSort(int l, int r, PTRecord * &pData, PTRecord* &pBuff);
	 void Merge(int L, int Mid, int R, PTRecord * &pData, PTRecord* &pBuff);
	 void QuickSort(PTRecord * pMem, int DataCount); // ������� ����������
	 void QuickSplit(PTRecord * pData, int size, int &pivot);

 public:
	 SortTable(int Size = TabMaxSize ) : TScanTable(Size) { };
	 SortTable(const TScanTable& tab);
	 SortTable& operator=(const TScanTable& tab); // ������������
	 SortMethod GetSort() { return Sort; }
	 void SetSort(SortMethod sm) { Sort = sm; }
	 // �������� ������
	 virtual PTDatValue FindRecord(TKey k); // ����� ������
	 virtual void InsRecord(TKey k, PTDatValue pVal); // ��������
	 virtual void DelRecord(TKey k);        // ������� ������
};
#endif