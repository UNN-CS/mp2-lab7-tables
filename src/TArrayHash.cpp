#include "TArrayHash.h"

TArrayHash::TArrayHash(int Size, int Step) : THashTable(), TabSize(Size), HashStep(Step)
{
	pRecs = new PTTabRecord[Size];
	for (int i = 0; i < TabSize; ++i)
		pRecs[i] = nullptr;
	FreePos = CurrPos = 0;
}

TArrayHash::~TArrayHash()
{
	delete[] pRecs;
}

int TArrayHash::IsFull() const
{
	return DataCount == TabSize;
}

TKey TArrayHash::GetKey(void) const
{
	if (CurrPos >= TabSize)
		throw std::runtime_error("Current position out of range");
	return pRecs[CurrPos]->GetKey();
}

PTDatValue TArrayHash::GetValuePTR(void) const
{
	if (CurrPos >= TabSize)
		throw std::runtime_error("Current position out of range");
	return pRecs[CurrPos]->GetValuePTR();
}

PTDatValue TArrayHash::FindRecord(TKey k)
{
	PTTabRecord rec = nullptr;
	int eff = DataCount;
	int current = HashFunc(k) % TabSize;
	for (int i = 0; i < TabSize; ++i)
	{
		if (pRecs[current] == nullptr)
		{
			eff = i + 1;
			break;
		}
		if (pRecs[current]->GetKey() == k)
		{
			eff = i + 1;
			rec = pRecs[current];
			break;
		}
		current = GetNextPos(current);
	}
	Efficiency += eff;
	return rec;
}

void TArrayHash::InsRecord(TKey k, PTDatValue pVal)
{
	int pre = -1;
	int current = HashFunc(k) % TabSize;
	for (int i = 0; i < TabSize; ++i)
	{
		if (pRecs[current] == nullptr)
		{
			Efficiency += i + 1;
			DataCount++;
			if (pre > -1)
			{
				pRecs[pre]->SetKey(k);
				pRecs[pre]->SetValuePtr(pVal);
				return;
			}
			pRecs[current] = new TTabRecord(k, pVal);
			return;
		}
		if ((pre < 0) && (pRecs[current]->GetKey() == "") && (pRecs[current]->GetValuePTR() == nullptr))
			pre = current;
		else if (pRecs[current]->GetKey() == k)
		{
			Efficiency += i + 1;
			pRecs[current]->SetValuePtr(pVal);
			return;
		}
		current = GetNextPos(current);
	}
	if (pre > -1)
	{
		Efficiency += TabSize;
		DataCount++;
		pRecs[pre]->SetKey(k);
		pRecs[pre]->SetValuePtr(pVal);
		return;
	}
	throw -1;
}

void TArrayHash::DelRecord(TKey k)
{
	int current = HashFunc(k) % TabSize;
	for (int i = 0; i < TabSize; ++i)
	{
		if (pRecs[current] == nullptr)
		{
			Efficiency += i + 1;
			return;
		}
		if (pRecs[current]->GetKey() == k)
		{
			Efficiency += i + 1;
			pRecs[current]->SetKey("");
			pRecs[current]->SetValuePtr(nullptr);
			DataCount--;
			return;
		}
		current = GetNextPos(current);
	}
	Efficiency += TabSize;
}

int TArrayHash::Reset(void)
{
	for (CurrPos = 0; CurrPos < TabSize; ++CurrPos)
	{
		if ((pRecs[CurrPos] != nullptr) && ((pRecs[CurrPos]->GetKey() != "") || (pRecs[CurrPos]->GetValuePTR() != nullptr)))
			break;
	}
	return IsTabEnded();
}

int TArrayHash::IsTabEnded(void) const
{
	return CurrPos == TabSize;
}

int TArrayHash::GoNext(void)
{
	if (!IsTabEnded())
		while (++CurrPos < TabSize)
		{
			if ((pRecs[CurrPos] != nullptr) && ((pRecs[CurrPos]->GetKey() != "") || (pRecs[CurrPos]->GetValuePTR() != nullptr)))
				break;
		}
	return IsTabEnded();
}