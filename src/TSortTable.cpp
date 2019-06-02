#include "TSortTable.h"

void TSortTable::SortData()
{
	switch (SortMethod)
	{
	case INSERT_SORT:
		InsertSort(pRecs, DataCount);
		break;
	case MERGE_SORT:
		MergeSort(pRecs, DataCount);
		break;
	case QUIQ_SORT:
		QuiqSort(pRecs, DataCount);
		break;
	default:
		throw -1;
	}
}

void TSortTable::InsertSort(PTTabRecord *pMem, int DataCount)
{
	int i,j;
	PTTabRecord tmp;
	for (i = 1;i < DataCount;i++)
	{
		tmp = pMem[i];
		j = i - 1;

		while (j >= 0 && pMem[j]->GetKey() > tmp->GetKey()) {
			Efficiency += 1;
			pMem[j + 1] = pMem[j];
			j = j - 1;
		}
		pMem[j + 1] = tmp;
	}
	Efficiency += i + 1;
}

void TSortTable::MergeSort(PTTabRecord *pMem, int DataCount)
{
	MergeSorter(pMem, 0, DataCount - 1);
}

void TSortTable::MergeSorter(PTTabRecord * & pData, int low, int high)
{
		int mid;
		if (low < high)
		{
			mid = (low + high) / 2;

			MergeSorter(pData, low, mid);
			MergeSorter(pData, mid + 1, high);

			MergeData(pData, low, high, mid);
		}
}

void TSortTable::MergeData(PTTabRecord * & pData, int low, int high, int mid)
{
	int i, j, k;
	PTTabRecord *pBuff = new PTTabRecord[high - low + 1];
	i = low;
	k = 0;
	j = mid + 1;

	while (i <= mid && j <= high)
	{
		if (pData[i]->GetKey() < pData[j]->GetKey())
		{
			pBuff[k] = pData[i];
			k++;
			i++;
		}
		else
		{
			pBuff[k] = pData[j];
			k++;
			j++;
		}
		Efficiency++;
	}

	while (i <= mid)
	{
		pBuff[k] = pData[i];
		k++;
		i++;
		Efficiency++;
	}

	while (j <= high)
	{
		pBuff[k] = pData[j];
		k++;
		j++;
		Efficiency++;
	}

	for (i = low; i <= high; i++)
		pData[i] = pBuff[i - low];
	Efficiency += i + 1;
}


void TSortTable::QuiqSort(PTTabRecord *pMem, int DataCount)
{
	int pivot, n1, n2;
	if (DataCount > 1) {
		QuiqSplit(pMem, DataCount, pivot);
		n1 = pivot + 1;
		n2 = DataCount - n1;
		QuiqSort(pMem, n1 - 1);
		QuiqSort(pMem + n1, n2);
	}
}

void TSortTable::QuiqSplit(PTTabRecord *pData, int Size, int &Pivot)
{
	PTTabRecord pPivot = pData[0];
	int i1 = 1, i2 = Size - 1;
	while (i1 <= i2) {
		while ((i1 < Size) && !(pData[i1]->GetKey() > pPivot->GetKey()))
			i1++;
		while (pData[i2]->GetKey() > pPivot->GetKey())
			i2--;
		if (i1 < i2)
			std::swap(pData[i1], pData[i2]);
	}
	pData[0] = pData[i2];
	pData[i2] = pPivot;
	Pivot = i2;
	Efficiency += Size;
}

TSortTable::TSortTable(int Size): TScanTable(Size) {
	SetSortMethod(QUIQ_SORT);
}

TSortTable::TSortTable(const TScanTable &tab): TScanTable(tab.TabSize)
{
	DataCount = tab.DataCount;
	CurrPos = tab.CurrPos;
	for (int i = 0; i < DataCount; i++)
		pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
	SetSortMethod(QUIQ_SORT);
	SortData();
}

TSortTable &TSortTable::operator=(const TScanTable &tab)
{
	if (pRecs != nullptr)
	{
		for (int i = 0; i < DataCount; ++i)
			delete pRecs[i];
		delete[] pRecs;
	}
	pRecs = nullptr;
	TabSize = tab.TabSize;
	DataCount = tab.DataCount;
	CurrPos = tab.CurrPos;
	pRecs = new PTTabRecord[TabSize];
	for (int i = 0; i < DataCount; i++)
		pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
	SortData();

	return *this;
}

TSortMethod TSortTable::GetSortMethod()
{
	return SortMethod;
}

void TSortTable::SetSortMethod(TSortMethod sm)
{
	SortMethod = sm;
}

PTDatValue TSortTable::FindRecord(TKey k)
{
	if (!IsEmpty())
	{
		int l = 0, mid, r = DataCount - 1;
		while (l <= r)
		{
			Efficiency++;
			mid = l + (r-l) / 2;
			if (pRecs[mid]->GetKey() == k)
			{
				CurrPos = mid;
				return pRecs[mid]->GetValuePTR();
			}
			if (pRecs[mid]->GetKey() < k)
				l = mid + 1;
			else
				r = mid - 1;
		}
		CurrPos = ++mid;
		return nullptr;
	}
	else 
		return nullptr;
}

void TSortTable::InsRecord(TKey k, PTDatValue pVal)
{
	if (IsFull())
		throw -1;
	else
	{
		if (FindRecord(k) != nullptr)
			return;
		else
		{
			int i;
			for (i = DataCount;i > CurrPos;i--)
				pRecs[i] = pRecs[i - 1];
			pRecs[CurrPos] = new TTabRecord(k, pVal);
			Efficiency += DataCount - i + 1;
			DataCount++;
		}
	}
}

void TSortTable::DelRecord(TKey k)
{
	if(!IsEmpty())
	{
		if (FindRecord(k) == nullptr)
			return;
		else
		{
			int i;
			for (i = CurrPos;i < DataCount - 1;i++)
				pRecs[i] = pRecs[i + 1];
			pRecs[i] = nullptr;
			Efficiency += i + 1;
			DataCount--;
		}
	}
}

void TSortTable::Print() {
	for (Reset();!IsTabEnded();GoNext())
		std::cout << GetKey()<<" ";
}

