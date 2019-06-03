#include "TTabRecord.h"
#include "TListHash.h"

TListHash::TListHash(int Size) :THashTable() {
	pList = new PTDatList[Size];
	TabSize = Size;
	CurrList = 0;
	for (int i = 0; i < TabSize; i++)
		pList[i] = new TDatList;
}

TListHash::~TListHash() {
	for (int i = 0; i < TabSize; i++)
		delete pList[i];
	delete[] pList;
}

int TListHash::IsFull() const {
	PTDatLink pLink = new TDatLink();
	int tmp = (pLink == nullptr);
	delete pLink;
	return tmp;
}

PTDatValue TListHash::FindRecord(TKey k) {
	PTDatValue pValue = nullptr;
	CurrList = HashFunc(k) % TabSize;
	PTDatList pL = pList[CurrList];
	for (pL->Reset(); !pL->IsListEnded(); pL->GoNext())
		if (PTTabRecord(pL->GetDatValue())->Key == k) {
			pValue = PTTabRecord(pL->GetDatValue())->pValue;
			break;
		}
	Efficiency += pL->GetCurrentPos() + 1;
	return pValue;
}

void TListHash::InsRecord(TKey k, PTDatValue pVal) {
	if (IsFull())
		throw TabFull;
	PTDatValue tmp = FindRecord(k);
	if (tmp != nullptr)
		throw TabRecDbl;
	CurrList = HashFunc(k) % TabSize;
	PTTabRecord temp = new TTabRecord(k, pVal);
	pList[CurrList]->InsLast(temp);
	DataCount++;
	//Efficiency++; // ???
	// >:-/
}
void TListHash::DelRecord(TKey k) {
	PTDatValue tmp = FindRecord(k);
	if (tmp == nullptr)
		throw TabNoRec;
	CurrList = HashFunc(k) % TabSize;
	PTDatList pL = pList[CurrList];
	pL->DelCurrent(); //установить pCurrent?
	DataCount--;
	// >:-/
}

int TListHash::Reset() {
	CurrList = 0;
	pList[CurrList]->Reset();
	while (CurrList != TabSize) {
		if (!pList[CurrList]->IsEmpty()) {
			pList[CurrList]->Reset();
			break;
		}
		CurrList++;
	}
	return IsTabEnded();
}

int TListHash::IsTabEnded() const {
	return CurrList >= TabSize;
}

int TListHash::GoNext() {
	if (!IsTabEnded()) {
		if (!pList[CurrList]->IsListEnded()) {
			pList[CurrList]->GoNext();
		}
		while (!IsTabEnded() && (pList[CurrList]->IsEmpty() || pList[CurrList]->IsListEnded())) {
			CurrList++;
			if (!IsTabEnded())
				pList[CurrList]->Reset();
		}
	}
	return IsTabEnded();
	// >:-/
}

TKey TListHash::GetKey() const {
	if (CurrList < 0 || CurrList >= TabSize)
		return std::string("");
	PTTabRecord pRec = PTTabRecord(pList[CurrList]->GetDatValue());
	return (pRec == nullptr) ? std::string("") : pRec->Key;
}

PTDatValue TListHash::GetValuePtr() const {
	if (CurrList < 0 || CurrList >= TabSize)
		return nullptr;
	PTTabRecord pRec = PTTabRecord(pList[CurrList]->GetDatValue());
	return(pRec == nullptr) ? nullptr : pRec->pValue;
}
