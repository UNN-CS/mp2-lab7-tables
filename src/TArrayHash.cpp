#include "TArrayHash.h"

TArrayHash::TArrayHash(int Size, int Step):THashTable(), TabSize(Size), HashStep(Step)
{
	pRecs = new PTTabRecord[TabSize];
	for (int i = 0;i < TabSize;i++)
		pRecs[i] = nullptr;
	pMark = new TTabRecord;
	FreePos = -1;
	CurrPos = 0;
}

TArrayHash::~TArrayHash()
{
	for (int i = 0;i < TabSize;i++)
		if (pRecs[i] != nullptr && pRecs[i] != pMark)
			delete pRecs[i];
	delete[] pRecs;
	delete pMark;
	pRecs = nullptr;
	pMark = nullptr;
}

int TArrayHash::IsFull() const
{
	return DataCount >= TabSize;
}

TKey TArrayHash::GetKey()const
{
	if (pRecs[CurrPos] != nullptr)
		return pRecs[CurrPos]->GetKey();
	else
		return "";
}

PTDatValue TArrayHash::GetValuePTR() const
{
	if (pRecs[CurrPos] != nullptr)
		return pRecs[CurrPos]->GetValuePTR();
	else
		return nullptr;
}

PTDatValue TArrayHash::FindRecord(TKey k)
{
	FreePos = -1;
	CurrPos = HashFunc(k) % TabSize;
	for (int i = 0;i < TabSize;i++)
	{
		Efficiency++;
		if (pRecs[CurrPos] != nullptr)
		{
			if (pRecs[CurrPos]->GetKey() == k)
				return pRecs[CurrPos]->GetValuePTR();
			else if (pRecs[CurrPos] == pMark && FreePos < 0)
				FreePos = CurrPos;
		}
		else if (pRecs[CurrPos] == nullptr)
			return nullptr;
		CurrPos = GetNextPos(CurrPos);
	}
	return nullptr;
}

void TArrayHash::InsRecord(TKey k, PTDatValue pVal)
{
	if (!IsFull())
	{
		FreePos = -1;
		CurrPos = HashFunc(k) % TabSize;
		for (int i = 0;i < TabSize;i++)
		{
			Efficiency++;
			if (pRecs[CurrPos] != nullptr)
			{
				if (pRecs[CurrPos]->GetKey() == k)
					return;
				else if (pRecs[CurrPos] == pMark && FreePos < 0)
					FreePos = CurrPos;
			}
			if (FreePos < 0)
			{
				DataCount++;
				pRecs[CurrPos] = new TTabRecord(k, pVal);
				return;
			}
			else
			{
				DataCount++;
				pRecs[FreePos] = new TTabRecord(k, pVal);
				return;
			}
			CurrPos = GetNextPos(CurrPos);
		}
	}
}

void TArrayHash::DelRecord(TKey k)
{
	if (!IsEmpty())
	{
		if (FindRecord(k) != nullptr)
		{
			DataCount--;
			pRecs[CurrPos] = pMark;
			return;
		}
	}
}

int TArrayHash::Reset()
{
	CurrPos = 0;
	return DataOK;
}

int TArrayHash::IsTabEnded() const
{
	return CurrPos >= TabSize;
}

int TArrayHash::GoNext()
{
	if (!IsTabEnded())
		CurrPos++;
	return DataOK;
}