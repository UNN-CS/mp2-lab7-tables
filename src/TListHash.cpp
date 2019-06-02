#include "TListHash.h"

TListHash::TListHash(int Size) : THashTable(), TabSize(Size)
{
	pList = new PTDatList[Size];
	for (int i = 0; i < TabSize; ++i)
		pList[i] = new TDatList();
	CurrList = 0;
}

TListHash::~TListHash()
{
	for (int i = 0; i < TabSize; ++i)
		delete pList[i];
	delete[] pList;
}

int TListHash::IsFull() const
{
	return 0;
}

TKey TListHash::GetKey(void) const
{
	if (CurrList >= TabSize)
		throw -1;
	return ((PTTabRecord)pList[CurrList]->GetDatValue())->GetKey();
}

PTDatValue TListHash::GetValuePTR(void) const
{
	if (CurrList >= TabSize)
		throw -1;
	return ((PTTabRecord)pList[CurrList]->GetDatValue())->GetValuePTR();
}

PTDatValue TListHash::FindRecord(TKey k)
{
	PTTabRecord rec = nullptr;
	int current = HashFunc(k) % TabSize;
	for (pList[current]->Reset(); !pList[current]->IsListEnded(); pList[current]->GoNext())
		if (((PTTabRecord)pList[current]->GetDatValue())->GetKey() == k)
		{
			rec = (PTTabRecord)pList[current]->GetDatValue();
			break;
		}
	Efficiency += pList[current]->GetCurrentPos() + 1;
	return rec;
}

void TListHash::InsRecord(TKey k, PTDatValue pVal)
{
	int current = HashFunc(k) % TabSize;
	for (pList[current]->Reset(); !pList[current]->IsListEnded(); pList[current]->GoNext())
	{
		if (((PTTabRecord)pList[current]->GetDatValue())->GetKey() == k)
		{
			Efficiency += pList[current]->GetCurrentPos() + 1;
			((PTTabRecord)pList[current]->GetDatValue())->SetValuePtr(pVal);
			return;
		}
	}
	Efficiency += pList[current]->GetCurrentPos() + 1;
	++DataCount;
	pList[current]->InsLast(new TTabRecord(k, pVal));
}

void TListHash::DelRecord(TKey k)
{
	int current = HashFunc(k) % TabSize;
	for (pList[current]->Reset(); !pList[current]->IsListEnded(); pList[current]->GoNext())
	{
		if (((PTTabRecord)pList[current]->GetDatValue())->GetKey() == k)
		{
			Efficiency += pList[current]->GetCurrentPos() + 1;
			pList[current]->DelCurrent();
			--DataCount;
			return;
		}
	}
	Efficiency += pList[current]->GetCurrentPos() + 1;
}

int TListHash::Reset(void)
{
	for (CurrList = 0; CurrList < TabSize; ++CurrList)
	{
		if (!pList[CurrList]->IsEmpty())
		{
			pList[CurrList]->Reset();
			break;
		}
	}
	return IsTabEnded();
}

int TListHash::IsTabEnded(void) const
{
	return CurrList == TabSize;
}

int TListHash::GoNext(void)
{
	if (IsTabEnded())
		return IsTabEnded();
	pList[CurrList]->GoNext();
	if (!pList[CurrList]->IsListEnded())
		return IsTabEnded();
	for (++CurrList; CurrList < TabSize; ++CurrList)
	{
		if (!pList[CurrList]->IsEmpty())
		{
			pList[CurrList]->Reset();
			break;
		}
	}
	return IsTabEnded();
}