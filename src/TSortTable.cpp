#include "TSortTable.h"

TSortTable::TSortTable(const TScanTable &tab) : TScanTable(tab.GetTabSize())
{
	CurrPos = tab.CurrPos;
	for (int i = 0; i < DataCount; ++i)
		pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
	SortMethod = QUIQ_SORT;
	SortData();
}

TSortTable & TSortTable::operator=(const TScanTable &tab)
{
	if (pRecs)
	{
		for (int i = 0; i < DataCount; ++i)
			delete pRecs[i];
		delete[] pRecs;
	}
	TabSize = tab.TabSize;
	DataCount = tab.DataCount;
	CurrPos = tab.CurrPos;
	pRecs = new PTTabRecord[TabSize];
	for (int i = 0; i < DataCount; ++i)
		pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
	SortData();
	return *this;
}

TSortMethod TSortTable::GetSortMethod(void)
{
	return SortMethod;
}

void TSortTable::SetSortMethod(TSortMethod sm)
{
	SortMethod = sm;
}

void TSortTable::SortData(void)
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
	//default:
	//	throw ("Wrong SortMethod");
	}
}

void TSortTable::InsertSort(PTTabRecord *pMem, int DataCount)
{
	Efficiency += DataCount;
	for (int i = 1, j; i < DataCount; ++i)
	{
		PTTabRecord r = pMem[i];
		for (j = i - 1; j >= 0; --j)
			if (r->GetKey() < pMem[j]->GetKey())
			{
				++Efficiency;
				pMem[j + 1] = pMem[j];
			}
			else
				break;
		pMem[j + 1] = r;
	}
}

void TSortTable::MergeSort(PTTabRecord *pMem, int DataCount)
{
	PTTabRecord* r = new PTTabRecord[DataCount];
	for (int i = 0; i < DataCount; ++i)
		r[i] = pMem[i];
	MergeSorter(pMem, r, DataCount);
	delete[] r;
}

void TSortTable::MergeSorter(PTTabRecord * &pData, PTTabRecord * &pBuff, int Size)
{
	int s = Size / 2;
	PTTabRecord* r1 = pBuff + s;
	PTTabRecord* r2 = pData + s;
	if (Size > 1)
	{
		MergeSorter(pBuff, pData, s);
		MergeSorter(r1, r2, Size - s);
		MergeData(pData, pBuff, s, Size);
	}
}

void TSortTable::MergeData(PTTabRecord *&pData, PTTabRecord *&pBuff, int n1, int n2)
{
	int i = 0;
	int j = n1;
	int k = 0;
	while ((i < n1) && (j < n2))
		if (pBuff[i]->GetKey() < pBuff[j]->GetKey())
			pData[k++] = pBuff[i++];
		else
			pData[k++] = pBuff[j++];
	while (i < n1)
		pData[k++] = pBuff[i++];
	while (j < n2)
		pData[k++] = pBuff[j++];
	Efficiency += n2;
}

void TSortTable::QuiqSort(PTTabRecord *pMem, int DataCount)
{
	int p;
	if (DataCount > 1)
	{
		QuiqSplit(pMem, DataCount, p);
		QuiqSort(pMem, p);
		QuiqSort(pMem + p, DataCount - p);
	}
}

void TSortTable::QuiqSplit(PTTabRecord *pData, int Size, int &Pivot)
{
	int bel;
	int sr = Size / 2;
	PTTabRecord x = pData[0];
	PTTabRecord y = pData[sr];
	PTTabRecord z = pData[Size - 1];
	if ((x->GetKey() >= z->GetKey()) && (x->GetKey() >= y->GetKey()))
	{
		if (z->GetKey() >= y->GetKey())
			bel = Size - 1;
		else
			bel = sr;
	}
	else if ((y->GetKey() >= z->GetKey()) && (y->GetKey() >= x->GetKey()))
	{
		if (z->GetKey() >= x->GetKey())
			bel = Size - 1;
		else
			bel = 0;
	}
	else
	{
		if (y->GetKey() >= x->GetKey())
			bel = sr;
		else
			bel = 0;
	}
	int i = 0, j = Size - 1;
	while (i < j)
	{
		while (pData[i]->GetKey() < pData[bel]->GetKey())
			++i;
		while (pData[j]->GetKey() > pData[bel]->GetKey())
			--j;
		if (i < j)
			swap(pData[i++], pData[j--]);
	}
	Pivot = j;
	Efficiency += Size;
}

PTDatValue TSortTable::FindRecord(TKey k)
{
	int i = 0, j = DataCount - 1, c;
	while (i <= j)
	{
		++Efficiency;
		c = (i + j) / 2;
		if (pRecs[c]->GetKey() == k)
			return pRecs[c];
		if (pRecs[c]->GetKey() < k)
			i = c + 1;
		else
			j = c - 1;
	}
	return nullptr;
}

void TSortTable::InsRecord(TKey k, PTDatValue pVal)
{
	PTTabRecord p;
	if ((p = (PTTabRecord)FindRecord(k)) != nullptr)
	{
		p->SetValuePtr(pVal);
		return;
	}
	if (IsFull())
		throw ("Table is full");
	for (int i = 0; i < DataCount; ++i)
	{
		if (pRecs[i]->GetKey() > k)
		{
			for (int j = DataCount; j > i; --j)
				pRecs[j] = pRecs[j - 1];
			++DataCount;
			Efficiency += DataCount;
			pRecs[i] = new TTabRecord(k, pVal);
			return;
		}
	}
	Efficiency += DataCount + 1;
	pRecs[DataCount++] = new TTabRecord(k, pVal);
}

void TSortTable::DelRecord(TKey k)
{
	if (FindRecord(k) != nullptr)
	{
		for (int i = 0; i < DataCount; ++i)
			if (pRecs[i]->GetKey() == k)
			{
				Efficiency += i + 1;
				delete pRecs[i];
				for (int j = i + 1; j < DataCount; ++j)
					pRecs[j - 1] = pRecs[j];
				Efficiency += DataCount;
				--DataCount;
				return;
			}
	}
}