#include "sorttab.h"

SortTable::SortTable(const TScanTable& tab)
{
	*this = tab;
}

SortTable& SortTable::operator=(const TScanTable& tab)
{
	if (pRecs != NULL) {
		for (int i = 0; i < DataCount; ++i) delete pRecs[i];
		delete[] pRecs;
		pRecs = NULL;
	}
	TabSize = tab.GetTabSize();
	DataCount = tab.GetDataCount();
	pRecs = new PTRecord[TabSize];
	for (int i = 0; i < DataCount; ++i) pRecs[i] = PTRecord(tab.pRecs[i]->GetCopy());
	//Sort = Merge_Sort;
	SortData();
	CurrPos = 0;
	return *this;
}

void SortTable::SortData() {
	Efficiency = 0;
	cout << "sort = " << Sort << endl;
	switch (Sort) {
	case Insert_Sort:
		InsertSort(pRecs, DataCount);
		break;
	case Merge_Sort: {
		PTRecord* buff = new PTRecord[DataCount];
		MergeSort(0, DataCount - 1, pRecs, buff);
		delete[] buff;
		break;
	}
	case Quick_Sort:
		QuickSort(pRecs, DataCount);
		break;
	}
}

// сортировка вставками
void SortTable::InsertSort(PTRecord * pRecs, int DataCount) {
	PTRecord tmp;
	Efficiency = DataCount;
	for (int i = 1; i < DataCount; ++i) {
		tmp = pRecs[i];  //  вставляемый элемент
		int j;
		for ( j=i-1;j>-1;j--)
			if (pRecs[j]->GetKey() > tmp->GetKey()) {
				pRecs[j + 1] = pRecs[j];
				Efficiency++;
			}
			else break;
		pRecs[j + 1] = tmp;
	}
}

// сортировка слиянием
void SortTable::MergeSort(int l, int r, PTRecord * &pData, PTRecord* &pBuff) {
	int mid = (l + r) / 2;
	if (l == r)
		return;
	MergeSort(l, mid, pData, pBuff);
	MergeSort(mid + 1, r, pData, pBuff);
	Merge(l, mid, r, pData, pBuff);
	//cout << l << " " << r << endl;
	for (int i = l; i <= r; ++i)
		pData[i] = pBuff[i];
}

void SortTable::Merge(int L, int Mid, int R, PTRecord * &a, PTRecord* &tmp) {
	int i = L;
	int j = Mid + 1;
	int k = L;
	for (k; k <= R; ++k)
	{
		if ((i>Mid) || (j <= R && a[j]->GetKey() <= a[i]->GetKey()))
			tmp[k] = a[j++];
		else tmp[k] = a[i++];
	}
}

//быстрая сортировка 
void SortTable::QuickSort(PTRecord *tmp, int DataCount)
{
	int pivot; // индекс ведущего элемента
	int n1, n2; // размеры разделенных блоков данных
	if (DataCount > 1)
	{
		QuickSplit(tmp, DataCount, pivot); // разделение 
		n1 = pivot + 1;
		n2 = DataCount - n1;
		QuickSort(tmp, n1 - 1);
		QuickSort(tmp + n1, n2);
	}
}

// быстрая сортировка - выбор ведущего элемента и разделение данных
void SortTable::QuickSplit(PTRecord * pData, int size, int &pivot) {
	PTRecord ppivot = pData[0], pTemp;
	int i1 = 1, i2 = size - 1;
	while (i1 <= i2)
	{
		while ((i1 < size) && !(pData[i1]->GetKey() > ppivot->GetKey())) i1++;
		while (pData[i2]->GetKey() > ppivot->GetKey()) i2--;
		if (i1 < i2)
		{
			pTemp = pData[i1];
			pData[i1] = pData[i2];
			pData[i2] = pTemp;
		}
	}
	pData[0] = pData[i2];
	pData[i2] = ppivot;
	pivot = i2;
	Efficiency += size;
}
// вставка
void SortTable::InsRecord(TKey k, PTDatValue pVal) {
	if (IsFull()) SetRetCode(TabFull);
	else
	{
		PTDatValue tmp = FindRecord(k);
		if (RetCode == TabOK) SetRetCode(TabRecDbl);
		else
		{
			SetRetCode(TabOK);
			for (int i = DataCount; i > CurrPos; i--) pRecs[i] = pRecs[i - 1];
			pRecs[CurrPos] = new TRecord(k, pVal);
			DataCount++;
		}
	}
}

// поиск записи
PTDatValue SortTable::FindRecord(TKey k) {
	int i, l = 0, r = DataCount-1;
	SetRetCode(TabOK);
	if (DataCount == 0) {
		SetRetCode(TabNoRec);
		return NULL;
	}
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (pRecs[mid]->GetKey() == k)
		{
			CurrPos = mid;
			return pRecs[l]->GetValuePtr();
		}
		if (pRecs[mid]->GetKey() > k) r = mid-1;
		else l = mid+1;
	}
	CurrPos = l;
	SetRetCode(TabNoRec);
	return NULL;
}

// удаление записи
void SortTable::DelRecord(TKey k) {
	PTDatValue tmp = FindRecord(k);
	if (tmp == NULL)
		SetRetCode(TabNoRec);
	else
	{
		SetRetCode(TabOK);
		//cout << CurrPos<<" "<<DataCount<<" "<<*pRecs[CurrPos]<<*pRecs[CurrPos+1]<<endl;
		PTRecord tmp = pRecs[CurrPos];
		for (int i = CurrPos; i < DataCount - 1; i++) pRecs[i] = pRecs[i+1];
		delete tmp;
		DataCount--;
	}
}
