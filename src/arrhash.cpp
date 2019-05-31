#include "arrhash.h"

ArrayHash::ArrayHash(int Size, int Step) : HashTable() {
	pRecs = new PTRecord[Size];
	TabSize = Size;
	HashStep = Step;
	for (int i = 0; i < TabSize; ++i) pRecs[i] = NULL;
	pMark = new TRecord(string(""), NULL);
}

ArrayHash::~ArrayHash() {
	for (int i = 0; i < TabSize; ++i)
		if ((pRecs[i] != NULL) && (pRecs[i] != pMark)) delete pRecs[i];
	delete[]pRecs;
	delete pMark;
}

// основные методы
PTDatValue ArrayHash::FindRecord(TKey k) {
	PTDatValue pVal = NULL;
	FreePos = -1;
	Efficiency = 0;
	CurrPos = HashFunc(k) % TabSize;
	for (int i = 0; i < TabSize; ++i) {
		Efficiency++;
		if (pRecs[CurrPos] == NULL) break;
		else if (pRecs[CurrPos] == pMark)
		{
			if (FreePos == -1)
				FreePos = CurrPos;
		}
		else if (pRecs[CurrPos]->GetKey() == k)
		{
			pVal = pRecs[CurrPos]->GetValuePtr();
			break;
		}
		CurrPos = GetNextPos(CurrPos); // открытое перемешивание
	}
	if (pVal == NULL) SetRetCode(TabNoRec);
	else SetRetCode(TabOK);
	return pVal;
}

void ArrayHash::DelRecord(TKey k)
{
	PTDatValue tmp = FindRecord(k);
	if (tmp == NULL) SetRetCode(TabNoRec);
	else {
		SetRetCode(TabOK);
		delete pRecs[CurrPos];
		pRecs[CurrPos] = pMark;
		//cout << DataCount << endl;
		DataCount--;
	}
}

void ArrayHash::InsRecord(TKey k, PTDatValue pVal) {
	if (IsFull()) SetRetCode(TabNoMem);
	else {
		PTDatValue tmp = FindRecord(k);
		if (tmp != NULL) SetRetCode(TabRecDbl);
		else
		{
			SetRetCode(TabOK);
			if (FreePos != -1) CurrPos = FreePos;
			if (pRecs[CurrPos] != NULL && pRecs[CurrPos] != pMark)
			{
				delete pRecs[CurrPos];
				DataCount--;
			}
			pRecs[CurrPos] = new TRecord(k, pVal);
			DataCount++;
		}
	}
}

// навигация
int ArrayHash::IsTabEnded() const {
	return CurrPos >= TabSize;
}

int ArrayHash::GoNext() {
	if (!IsTabEnded()) {
		while (++CurrPos < TabSize)
			if ((pRecs[CurrPos] != NULL) && (pRecs[CurrPos] != pMark)) break;
	}
	return IsTabEnded();
}

int ArrayHash::Reset() {
	CurrPos = 0;
	for (;CurrPos<TabSize;++CurrPos)
		if ((pRecs[CurrPos] != NULL) && (pRecs[CurrPos] != pMark)) break;
	return IsTabEnded();
}
// доступ
TKey ArrayHash::GetKey() const {
	return ((CurrPos < 0) || (CurrPos >= TabSize)) ? string("") : pRecs[CurrPos]->GetKey();
}

PTDatValue ArrayHash::GetValuePtr() const {
	return ((CurrPos < 0) || (CurrPos >= TabSize)) ? NULL : pRecs[CurrPos]->GetValuePtr();
}
