#include "TListHash.h"

TListHash::TListHash(int Size): THashTable()
{
	TabSize = Size;
	pList = new PTDatList[TabSize];
	for (int i = 0;i < TabSize;i++)
		pList[i] = nullptr;
	CurrList = -1;
}

TListHash::~TListHash()
{
	for (int i = 0;i < TabSize;i++)
		delete pList[i];
	delete[] pList;
}

int TListHash::IsFull() const
{
	return 0;
}

TKey TListHash::GetKey() const
{
	if (CurrList > -1 && CurrList <= TabSize)
		return ((PTTabRecord)pList[CurrList]->GetDatValue())->GetKey();
}

PTDatValue TListHash::GetValuePTR() const
{
	if (CurrList > -1 && CurrList <= TabSize)
		return ((PTTabRecord)pList[CurrList]->GetDatValue())->GetValuePTR();
}

PTDatValue TListHash::FindRecord(TKey k)
{
	CurrList = HashFunc(k) % TabSize;
	if (pList[CurrList] == nullptr || pList[CurrList]->IsEmpty())
		return nullptr;
	else
	{
		for (pList[CurrList]->Reset();!(pList[CurrList]->IsListEnded());pList[CurrList]->GoNext())
		{
			Efficiency++;
			if (((PTTabRecord)pList[CurrList]->GetDatValue())->GetKey() == k)
				return ((PTTabRecord)pList[CurrList]->GetDatValue())->GetValuePTR();
		}
		return nullptr;
	}
}

void TListHash::InsRecord(TKey k, PTDatValue pVal)
{
	CurrList = HashFunc(k) % TabSize;
	if (pList[CurrList] == nullptr)
		pList[CurrList] = new TDatList;
	if (FindRecord(k) == nullptr)
	{
		pList[CurrList]->InsLast(new TTabRecord(k, pVal));
		DataCount++;
		Efficiency++;
	}
}

void TListHash::DelRecord(TKey k)
{
	if (!IsEmpty())
	{
		if (FindRecord(k) != nullptr)
		{
			Efficiency++;
			DataCount--;
			pList[CurrList]->DelCurrent();
		}
	}
}

int TListHash::Reset()
{
	if (!IsEmpty())
		CurrList = 0;
	return DataOK;
}

int TListHash::IsTabEnded() const
{
	return CurrList >= TabSize;
}

int TListHash::GoNext()
{
	if (!IsTabEnded())
		CurrList++;
	if (pList[CurrList] == nullptr)
		throw -1;
	return DataOK;
}