#include "TDatList.h"

int TDatList::Reset() {
	pPrevLink = pStop;
	if (IsEmpty()) {
		pCurrLink = pStop;
		CurrPos = -1;
	}
	else {
		pCurrLink = pFirst;
		CurrPos = 0;
	}
	return 0;
}

TDatList::TDatList() {
	pFirst = pLast = pStop = nullptr;
	ListLen = 0;
	Reset();
}

PTDatValue TDatList::GetDatValue(TLinkPos mode) const {
	PTDatLink temp;
	switch (mode) {
	case FIRST:
		temp = pFirst;
		break;
	case LAST:
		temp = pLast;
		break;
	default:
		temp = pCurrLink;
	}
	return temp ? temp->pValue : nullptr;
}

int TDatList::SetCurrentPos(int pos) {
	Reset();
	for (int i = 0; i < pos; ++i)
		GoNext();
	return 0;
}

int TDatList::GetCurrentPos() const {
	return CurrPos;
}

int TDatList::IsListEnded() const {
	return pCurrLink == pStop;
}

int TDatList::GoNext() {
	if (pCurrLink == pStop)
		throw ListNoPos;
	pPrevLink = pCurrLink;
	pCurrLink = pCurrLink->GetNextDatLink();
	++CurrPos;
	return 0;
}

PTDatLink TDatList::GetLink(PTDatValue pVal, PTDatLink pLink) {
	PTDatLink temp = new TDatLink(pVal, pLink);
	if (!temp)
		throw ListNoMem;
	return temp;
}

void TDatList::DelLink(PTDatLink pLink) {
	if (pLink && pLink->pValue)
		delete pLink->pValue;
	if (pLink)
		delete pLink;
}

void TDatList::InsFirst(PTDatValue pVal) {
	PTDatLink temp = GetLink(pVal, pFirst);
	if (!temp)
		throw ListNoMem;
	pFirst = temp;
	++ListLen;
	if (ListLen == 1) {
		pLast = temp;
		Reset();
	}
	else if (CurrPos == 0)
		pCurrLink = temp;
	else
		++CurrPos;
}

void TDatList::InsLast(PTDatValue pVal) {
	PTDatLink temp = GetLink(pVal, pStop);
	if (!temp)
		throw ListNoMem;
	else {
		if (pLast)
			pLast->SetNextLink(temp);
		pLast = temp;
		++ListLen;
		if (ListLen == 1) {
			pFirst = temp;
			Reset();
		}
		if (IsListEnded())
			pCurrLink = temp;
	}
}

void TDatList::InsCurrent(PTDatValue pVal) {
	if (IsEmpty() || (pCurrLink == pFirst))
		InsFirst(pVal);
	else if (IsListEnded())
		InsLast(pVal);
	else if (pPrevLink == pStop)
		throw ListNoPos;
	else {
		PTDatLink temp = GetLink(pVal, pCurrLink);
		if (!temp)
			throw ListNoMem;
		else {
			pCurrLink = temp;
			pPrevLink->SetNextLink(temp);
			++ListLen;
		}
	}
}

void TDatList::DelFirst() {
	if (IsEmpty())
		throw ListEmpty;
	else {
		PTDatLink temp = pFirst;
		pFirst = pFirst->GetNextDatLink();
		DelLink(temp);
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
}

void TDatList::DelCurrent() {
	if (pCurrLink == pStop)
		throw ListNoPos;
	else if (pCurrLink == pFirst)
		DelFirst();
	else {
		PTDatLink temp = pCurrLink;
		if (pCurrLink == pLast)
			pLast = pPrevLink;
		pCurrLink = pCurrLink->GetNextDatLink();
		pPrevLink->SetNextLink(pCurrLink);
		DelLink(temp);
		--ListLen;
	}
}

void TDatList::DelList() {
	while (!IsEmpty())
		DelFirst();
	pFirst = pLast = pPrevLink = pCurrLink = pStop;
	CurrPos = -1;
}