#include "TDatList.h"

PTDatLink TDatList::GetLink(PTDatValue pVal, PTDatLink pLink) {
	PTDatLink t = new TDatLink(pVal, pLink);
	return t;
}

void TDatList::DelLink(PTDatLink pLink) {
	if (pLink != nullptr)
	{
		if (pLink->pValue != nullptr)
			delete pLink->pValue;
		delete pLink;
	}
}

TDatList::TDatList() {
	pFirst = pLast = pStop = pPrevLink = pCurrLink = nullptr;
	ListLen = 0, CurrPos = -1;
}

PTDatValue TDatList::GetDatValue(TLinkPos mode) const {
	PTDatLink t;
	switch (mode) {
	case FIRST: t = pFirst; break;
	case LAST: t = pLast; break;
	default: t = pCurrLink; break;
	}
	return (t == nullptr) ? nullptr : t->pValue;
}

void TDatList::SetCurrentPos(int pos) {
	Reset();
	for (int i = 0; i < pos; i++)
		GoNext();
}

int TDatList::GetCurrentPos() const {
	return CurrPos;
}

void TDatList::Reset() {
	pPrevLink = pStop;
	if (IsEmpty()) {
		pCurrLink = pStop; CurrPos = -1;
	}
	else {
		pCurrLink = pFirst; CurrPos = 0;
	}
}

int TDatList::IsListEnded() const {
	return pCurrLink == pStop;
}

void TDatList::GoNext() {
	pPrevLink = pCurrLink;
	pCurrLink = pCurrLink->GetNextDatLink();
	CurrPos++;
}

void TDatList::InsFirst(PTDatValue pVal) {
	PTDatLink tmp = GetLink(pVal, pFirst);
	pFirst = tmp;
	ListLen++;
	
	if (ListLen == 1) {
		pLast = tmp;
		Reset();
	}
	else if (CurrPos == 0)
		pCurrLink = tmp;
	else
		CurrPos++;
}

void TDatList::InsLast(PTDatValue pVal) {
	PTDatLink tmp = GetLink(pVal, pStop);
	if (pLast != nullptr)
		pLast->SetNextLink(tmp);
	pLast = tmp;
	ListLen++;
	if (ListLen == 1) {
		pFirst = tmp;
		Reset();
	}
	if (IsListEnded())
		pCurrLink = tmp;
}

void TDatList::InsCurrent(PTDatValue pVal) {
	if (IsEmpty() || pCurrLink == pFirst)
		InsFirst(pVal);
	else if (IsListEnded())
		InsLast(pVal);
	else {
		PTDatLink tmp = GetLink(pVal, pCurrLink);
		pCurrLink = tmp;
		pPrevLink->SetNextLink(tmp);
		ListLen++;
	}
}

void TDatList::DelFirst() {
	PTDatLink tmp = pFirst;
	pFirst = pFirst->GetNextDatLink();
	DelLink(tmp);
	--ListLen;
	if (IsEmpty()) {
		pLast = pStop;
		Reset();
	}
	else if (CurrPos == 0)
		pCurrLink = pFirst;
	else if (CurrPos == 1)
		pPrevLink = pStop;
	if (CurrPos > 0)
		--CurrPos;
}

void TDatList::DelCurrent() {
	if (pCurrLink == pFirst)
		DelFirst();
	else {
		PTDatLink tmp = pCurrLink;
		pCurrLink = pCurrLink->GetNextDatLink();
		pPrevLink->SetNextLink(pCurrLink);
		DelLink(tmp);
		--ListLen;
	}
}

void TDatList::DelList() {
	while (!IsEmpty())
		DelFirst();
	pFirst = pLast = pPrevLink = pCurrLink = pStop;
	CurrPos = -1;
}
