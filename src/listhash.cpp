#include "listhash.h"

ListHash::ListHash(int size):HashTable() {
	pList = new PTDatList[size];
	TabSize = size;
	CurrList = 0;
	for (int i = 0; i < TabSize; ++i) pList[i] = new TDatList;
}

ListHash::~ListHash() {
	for (int i = 0; i < TabSize; ++i) delete pList[i];
	delete[] pList;
}

int ListHash::IsFull()const {
	PTDatLink pLink = new TDatLink();
	int temp = (pLink == NULL);
	delete pLink;
	return temp;
}

PTDatValue ListHash::FindRecord(TKey k) {
	PTDatValue pVal = NULL;
	CurrList = HashFunc(k) % TabSize;
	PTDatList pl = pList[CurrList];
	Efficiency = 0;
	for (pl->Reset();!pl->IsListEnded();pl->GoNext())
		if (PTRecord(pl->GetDatValue())->GetKey() == k)
		{
			pVal = PTRecord(pl->GetDatValue())->GetValuePtr();
			break;
		}
	Efficiency = pl->GetCurrentPos() + 1;
	if (pVal == NULL)
		SetRetCode(TabNoRec);
	else SetRetCode(TabOK);
	return pVal;
}

void ListHash::InsRecord(TKey k, PTDatValue pVal) {
	if (FindRecord(k) == NULL)
	{
		SetRetCode(TabOK);
		CurrList = HashFunc(k) % TabSize;
		PTDatList pl = pList[CurrList];
		PTRecord tmp = new TRecord(k, pVal);
		pl->InsLast(tmp);
		DataCount++;
	}
	else
		SetRetCode(TabRecDbl);
}

void ListHash::DelRecord(TKey k) {
	if (FindRecord(k) == NULL)
		SetRetCode(TabNoRec);
	else {
		SetRetCode(TabOK);
		CurrList = HashFunc(k) % TabSize;
		PTDatList pl = pList[CurrList];
		pl->DelCurrent();
		DataCount--;
	}
}

// навигация
int ListHash::Reset() {
	CurrList = 0;
	pList[CurrList]->Reset();
	return IsTabEnded();
}

int ListHash::IsTabEnded() const {
	return CurrList >= TabSize;
}

int ListHash::GoNext() {
	pList[CurrList]->GoNext();
	if (!pList[CurrList]->IsListEnded());
	else {
		CurrList++;
		while (!IsTabEnded())
		{
			if (pList[CurrList]->GetCurrentPos() != -1)
			{
				pList[CurrList]->Reset(); 
				break;
			}
			CurrList++;
		}
	}
	return IsTabEnded();
}

// доступ

TKey ListHash::GetKey() const {
	if ((CurrList < 0) || (CurrList >= TabSize)) return string("");
	PTRecord rec = PTRecord(pList[CurrList]->GetDatValue());
	return (rec == NULL) ? string("") : rec->GetKey();
}

PTDatValue ListHash::GetValuePtr() const {
	if ((CurrList < 0) || (CurrList >= TabSize)) return NULL;
	PTRecord rec = PTRecord(pList[CurrList]->GetDatValue());
	return (rec == NULL) ? NULL : rec->GetValuePtr();
}
