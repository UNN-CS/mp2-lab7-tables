#include "TArrayHash.h"

TArrayHash::TArrayHash(int Size, int Step) 
{
	pRecs = new PTTabRecord[Size];
	TabSize = Size;
	HashStep = Step;
	pMark = new TTabRecord("", nullptr);
	for (int i = 0; i < TabSize; ++i)
		pRecs[i] = pMark;
}

TArrayHash::~TArrayHash() {
	for (int i = 0; i < TabSize; ++i) 
	{
		if (pRecs[i] && pRecs[i] != pMark)
			delete pRecs[i];
	}
	delete[] pRecs;
	delete pMark;
}

int TArrayHash::IsFull() const 
{
	return (DataCount == TabSize);
}

TKey TArrayHash::GetKey() const 
{
	if (CurrPos < 0 || CurrPos >= TabSize)
		return("");
	else
		return (pRecs[CurrPos]->Key);
}

PTDatValue TArrayHash::GetValuePTR() const {
	if (CurrPos < 0 || CurrPos >= TabSize)
		return nullptr;
	else
		return (pRecs[CurrPos]->pValue);
}

PTDatValue TArrayHash::FindRecord(TKey k) {
	PTTabRecord p = nullptr;
	int eff = DataCount;
	int _k = HashFunc(k) % TabSize;
	for (int i = 0; i < TabSize; ++i)
	{
		if (pRecs[_k] == nullptr)
		{
			eff = i + 1;
			break;
		}
		if (pRecs[_k]->GetKey() == k)
		{
			eff = i + 1;
			p = pRecs[_k];
			break;
		}
		_k = GetNextPos(_k);
	}
	Efficiency += eff;
	return p;
}

void TArrayHash::InsRecord(TKey k, PTDatValue pVal) {
	if (DataCount == TabSize)
		throw - 1;
	int CurrPos = HashFunc(k) % TabSize;
	while (pRecs[CurrPos] != pMark) {
		++Efficiency;
		CurrPos = GetNextPos(CurrPos);
	}
	pRecs[CurrPos] = new TTabRecord(k, pVal);
	++DataCount;
}

void TArrayHash::DelRecord(TKey k) {
	int _k = HashFunc(k) % TabSize;
	for (int i = 0; i < TabSize; ++i)
	{
		if (pRecs[_k] == nullptr)
		{
			Efficiency += i + 1;
			return;
		}
		if (pRecs[_k]->GetKey() == k)
		{
			Efficiency += i + 1;
			pRecs[_k]->SetKey("");
			pRecs[_k]->SetValuePtr(nullptr);
			--DataCount;
			return;
		}
		_k = GetNextPos(_k);
	}
	Efficiency += TabSize;
}

int TArrayHash::Reset() {
	CurrPos = 0;
	return 0;
}

int TArrayHash::IsTabEnded() const {
	return (CurrPos >= TabSize);
}

int TArrayHash::GoNext() {
	if (!IsTabEnded()) {
		while (++CurrPos < TabSize)
			if (pRecs[CurrPos] && pRecs[CurrPos] != pMark)
				break;
	}
	return 0;
}
