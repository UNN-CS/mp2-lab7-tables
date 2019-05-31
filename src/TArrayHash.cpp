#include "TArrayHash.h"

TArrayHash::TArrayHash(int Size, int Step) {
	pRecs = new PTTabRecord[Size];
	TabSize = Size;
	HashStep = Step;
	pMark = new TTabRecord("", nullptr);
	for (int i = 0; i < TabSize; ++i)
		pRecs[i] = pMark;
}

TArrayHash::~TArrayHash() {
	for (int i = 0; i < TabSize; ++i) {
		if (pRecs[i] && pRecs[i] != pMark)
			delete pRecs[i];
	}
	delete[] pRecs;
	delete pMark;
}

PTDatValue TArrayHash::FindRecord(TKey k) {
	PTDatValue pValue = nullptr;
	FreePos = -1;
	CurrPos = HashFunc(k) % TabSize;
	for (int i = 0; i < TabSize; ++i) {
		++Efficiency;
		if (!pRecs[CurrPos])
			break;
		if (pRecs[CurrPos] == pMark) {
			if (FreePos == -1)
				FreePos = CurrPos;
		}
		else if (pRecs[CurrPos]->key == k) {
			pValue = pRecs[CurrPos]->pValue;
			break;
		}
		CurrPos = GetNextPos(CurrPos);
	}
	if (!pValue)
		return nullptr;
	return pValue;
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
	PTDatValue temp = FindRecord(k);
	if (!temp)
		return;
	pRecs[CurrPos] = pMark;
	--DataCount;
}

int TArrayHash::Reset() {
	CurrPos = 0;
	return IsTabEnded();
}

int TArrayHash::IsFull() const {
	return DataCount == TabSize;
}

int TArrayHash::IsTabEnded() const {
	return CurrPos >= TabSize;
}

int TArrayHash::GoNext() {
	if (!IsTabEnded()) {
		while (++CurrPos < TabSize)
			if (pRecs[CurrPos] && pRecs[CurrPos] != pMark)
				break;
	}
	return IsTabEnded();
}

TKey TArrayHash::GetKey() const {
	return (CurrPos < 0 || CurrPos >= TabSize) ? "" : pRecs[CurrPos]->key;
}

PTDatValue TArrayHash::GetValuePTR() const {
	return (CurrPos < 0 || CurrPos >= TabSize) ? nullptr : pRecs[CurrPos]->pValue;
}