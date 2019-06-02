#include "TDatList.h"

	PTDatLink TDatList :: GetLink (PTDatValue pVal, PTDatLink pLink)  
{
	PTDatLink link = new TDatLink(pVal, pLink);
	return link;
}

    void TDatList :: DelLink (PTDatLink pLink) 
	{
		if (pLink != nullptr) {
			if(GetDatValue() != nullptr)
				delete (pLink -> pValue);
			delete pLink;
		}
	}
	TDatList :: TDatList()
	{
		pFirst = nullptr; 
		pLast = nullptr; 
		pCurrLink = nullptr; 
		pPrevLink = nullptr;
		pStop = nullptr; 
		CurrPos = -1; 
		ListLen = 0;  
	}

    PTDatValue TDatList :: GetDatValue (TLinkPos mode) const 
	{
		PTDatLink link;
		switch (mode) {
		case BEGIN: 
			link = pFirst; break;
		case CURRENT: 
			link = pCurrLink; break;
		case END: 
			link = pLast; break;
		default: 
			throw -1;
		}
		return (link==nullptr)?0:link->pValue;
	}

    int TDatList :: SetCurrentPos (int pos)
	{
		if ((pos<0)||(pos>GetListLength()))
			throw -1;
		Reset();
		for (int i=0; i<pos; i++)
			GoNext();
		CurrPos = pos;
		return 0;
	}
    int TDatList :: GetCurrentPos (void) const 
	{
		return CurrPos;
	}
    int TDatList :: Reset (void) {
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
	int TDatList :: IsListEnded (void) const {
		return (pCurrLink == pStop);
	}
    int TDatList :: GoNext (void) {
		if (pCurrLink == pStop)
			return -1;
		else {
			pPrevLink = pCurrLink;
			pCurrLink = pCurrLink -> GetNextDatLink();
			CurrPos++;
			return 0;
		}
	}

    void TDatList :: InsFirst (PTDatValue pVal) {
		PTDatLink link = GetLink(pVal, pFirst);
		if (link == nullptr)
			throw -1;
		pFirst = link;
		if (pLast == nullptr)
			pLast = pFirst;
		Reset();
		ListLen++;

	}
    void TDatList :: InsLast (PTDatValue pVal) { 
		PTDatLink link = GetLink(pVal, pStop);
		if (pLast != nullptr) {
			pPrevLink = pLast;
			pLast -> SetNextLink (link);
		}
		pLast = link;
		pCurrLink = pLast;
		if (ListLen==0) 
			pFirst = pLast;
		Reset();
		ListLen++;
	}
    void TDatList :: InsCurrent (PTDatValue pVal) {
		if ((pCurrLink == nullptr)||(pPrevLink == nullptr))
			InsFirst (pVal);
		else  {
			PTDatLink link = GetLink(pVal, pCurrLink);
			pPrevLink -> SetNextLink (link);
			pCurrLink = link;
			ListLen++;
		}
		
	}
   
    void TDatList :: DelFirst (void) {
		if (IsEmpty()) 
			throw -1;
		if (pFirst == pLast) 
			pLast = nullptr;
		PTDatLink link = pFirst;
		pFirst = pFirst -> GetNextDatLink();
		DelLink(link);
		Reset();
		ListLen--;
	}
    void TDatList :: DelCurrent (void) {
		if (pCurrLink == nullptr) throw -1;
		if (pCurrLink == pFirst) DelFirst();
		else {
			PTDatLink link = pCurrLink;
			pCurrLink = pCurrLink -> GetNextDatLink();
			pPrevLink -> SetNextLink(pCurrLink);
			DelLink(link);
			if (pCurrLink == nullptr) 
				pPrevLink = nullptr;
			ListLen--;
		}
	} 
    void TDatList :: DelList (void) {
		while(!IsEmpty())
			DelFirst();
		CurrPos = -1;
		pFirst = pLast = pCurrLink = pPrevLink = pStop;
	}