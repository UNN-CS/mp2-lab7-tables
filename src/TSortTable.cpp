#include "TSortTable.h"
#include "TWord.h"

TSortTable::TSortTable(const TScanTable& tab) {
	*this = tab;
}

TSortTable& TSortTable::operator=(const TScanTable& tab) {
	if (pRecs != nullptr) {
		for (int i = 0; i < DataCount; i++)
			delete pRecs[i];
		delete[] pRecs;
		pRecs = nullptr;
	}
	TabSize = tab.GetTabSize();
	DataCount = tab.GetDataCount();
	pRecs = new PTTabRecord[TabSize];
	for (int i = 0; i < DataCount; i++)
	{
		pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
	}
	SortData();
	CurrPos = 0;
	return *this;
}

PTDatValue TSortTable::FindRecord(TKey k) {
	int i = 0, i1 = 0, i2 = DataCount - 1;
	CurrPos = DataCount - 1;
	while (i1 <= i2) {
		Efficiency++;
		i = (i1 + i2) / 2;
		if (pRecs[i]->GetKey() == k)
		{
			CurrPos = i;
			return pRecs[i]->GetValuePtr();
		}
		else if (pRecs[i]->GetKey() > k)
			i2 = i - 1;
		else
			i1 = i + 1;
	}
	CurrPos = i1; //???
	return nullptr;
	// >:-/
}

void TSortTable::InsRecord(TKey k, PTDatValue pVal) {
	if (IsFull())
		throw TabFull;
	PTDatValue tmp = FindRecord(k);
	if (tmp != nullptr)
		throw TabRecDbl;
	for (int i = DataCount; i > CurrPos; i--) {
		pRecs[i] = pRecs[i - 1];  // перепаковка
		Efficiency++;
	}
	pRecs[CurrPos] = new TTabRecord(k, pVal);
	DataCount++;
}

void TSortTable::DelRecord(TKey k) {
	if (IsEmpty())
		throw TabEmpty;
	PTDatValue tmp = FindRecord(k);
	if (tmp == nullptr)
		throw TabNoRec;
	for (int i = CurrPos; i < DataCount - 1; i++) {
		Efficiency++;
		pRecs[i] = pRecs[i + 1];
	}
	pRecs[DataCount - 1] = nullptr;
	DataCount--;
	// >:-/
}

TSortMethod TSortTable::GetSortMethod() const {
	return SortMethod;
}

void TSortTable::SetSortMethod(TSortMethod sm) {
	SortMethod = sm;
}

void TSortTable::SortData() {
	Efficiency = 0;
	switch (SortMethod) {
	case INSERT_SORT:
		InsertSort(pRecs, DataCount); break;
	case MERGE_SORT:
		MergeSort(pRecs, DataCount); break;
	case QUICK_SORT:
		QuickSort(pRecs, DataCount); break;
	}
}

void TSortTable::InsertSort(PTTabRecord* pMem, int DataCount) {
	PTTabRecord pR;
	Efficiency = DataCount;
	for (int i = 1; i < DataCount; i++) {
		int j;
		pR = pRecs[i];
		for (j = i - 1; j > -1; j--) {
			if (pRecs[j]->Key > pR->Key) {
				pRecs[j + 1] = pRecs[j];
				Efficiency++;
			}
			else
				break;
		}
		pRecs[j + 1] = pR;
	}
}

void TSortTable::MergeSort(PTTabRecord *pRecs, int DataCount) {
	PTTabRecord* pData = pRecs;
	PTTabRecord* pBuff = new PTTabRecord[DataCount];
	PTTabRecord* pTemp = pBuff;
	MergeSorter(pData, pBuff, DataCount);
	if (pData == pTemp)
		for (int i = 0; i < DataCount; i++)
			pBuff[i] = pData[i];
	delete pTemp;
}

void TSortTable::MergeSorter(PTTabRecord*& pData, PTTabRecord*& pBuff, int Size) {
	int n1 = (Size + 1) / 2;
	int n2 = Size - n1;
	if (Size > 2) {
		PTTabRecord* pData2 = pData + n1, *pBuff2 = pBuff + n1;
		MergeSorter(pData, pBuff, n1);
		MergeSorter(pData2, pBuff2, n2);
	}
	MergeData(pData, pBuff, n1, n2);
}

void TSortTable::MergeData(PTTabRecord*& pData, PTTabRecord*& pBuff, int n1, int n2) {
	int i1 = 0, i2 = n1, id = 0;
	while (id != n2)
	{
		if (i1 == n1)
			pBuff[id++] = pData[i2++];
		else if (i2 == n2)
			pBuff[id++] = pData[i1++];
		else {
			if (pData[i1] < pData[i2])
				pBuff[id++] = pData[i1++];
			else
				pBuff[id++] = pData[i2++];
		}
	}
	for (int i = 0; i < n2; i++)
		std::swap(pData[i], pBuff[i]);
	Efficiency += DataCount + i2 - i1;//????
									  // >:-/
}

void TSortTable::QuickSort(PTTabRecord* pRecs, int DataCount) {
	int pivot;
	int n1, n2;
	if (DataCount > 1) {
		QuickSplit(pRecs, DataCount, pivot);
		n1 = pivot + 1;
		n2 = DataCount - n1;
		QuickSort(pRecs, n1 - 1);
		QuickSort(pRecs + n1, n2);
	}
}

void TSortTable::QuickSplit(PTTabRecord* pData, int Size, int& Pivot) {
	PTTabRecord pPivot = pData[0];
	int i1 = 1, i2 = Size - 1;
	while (i1 <= i2) {
		while (i1 < Size && pData[i1]->Key <= pPivot->Key)
			i1++;
		while (i2 >= 0 && pData[i2]->Key > pPivot->Key)
			i2--;
		if (i1 < i2)
			std::swap(pData[i1], pData[i2]);
	}
	pData[0] = pData[i2];
	pData[i2] = pPivot;
	Pivot = i2;
	Efficiency += Size;
}

std::string TSortTable::KeysToStr() const {
	std::string tmp;
	for (int i = 0; i < DataCount; i++) {
		tmp += pRecs[i]->Key + std::string(" ");
	}
	return tmp;
}
