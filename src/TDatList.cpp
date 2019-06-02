#include "TDatList.h"

TDatList::TDatList()
{
	pFirst = pPrevLink = pCurrLink = pLast = pStop = NULL;
	ListLen = 0;
	CurrPos = -1;
}

TDatList::~TDatList()
{
	DelList();
}

PTDatLink TDatList::GetLink(PTDatValue pVal, PTDatLink pLink)
{
	PTDatLink t = new TDatLink(pVal, pLink);
	return t;
}

void TDatList::DelLink(PTDatLink pLink)
{
	if (!pLink)
	{
		if (pLink->pValue != NULL)
			delete pLink->pValue;
		delete pLink;
	}
}

bool TDatList::IsEmpty() const
{
	return pFirst == pStop;
}

int TDatList::GetListLeght() const
{
	return ListLen;
}

PTDatValue TDatList::GetDatValue(TLinkPos mode) const
{
	PTDatLink tmp;
	switch(mode)
	{
		case FIRST:
			tmp = pFirst;
			break;
		
		case CURRENT:
			tmp = pCurrLink;
			break;
		
		case LAST:
			tmp = pLast;
			break;
		
		default:
		throw -1;
	}
	return (tmp == NULL) ? NULL : tmp->pValue;
}

void TDatList::Reset()
{
	pCurrLink = pFirst;
	CurrPos = 0;
}

void TDatList::GoNext()
{
	if(pCurrLink == pStop) throw -1;
	pPrevLink = pCurrLink;
	pCurrLink = pCurrLink->GetNextDatLink();
	CurrPos++;
}

bool TDatList::IsListEnded() const
{
	return (pPrevLink == pLast)&&(pCurrLink == pStop);
}

int TDatList::GetCurrentPos() const
{
	return CurrPos;
}

void TDatList::SetCurrentPos(int pos)
{
	Reset();
	for(int i = 0;i<pos;i++)
		GoNext();
}

void TDatList::InsFirst(PTDatValue pVal)
{
	PTDatLink t = new TDatLink(pVal);
	if (IsEmpty())
	{
		t->pNext = pStop;
		pLast = t;
	}	
	else
		t->pNext = pFirst;
	pFirst = t;
	ListLen++;
	Reset();
}

void TDatList::InsLast(PTDatValue pVal)
{
	PTDatLink t = new TDatLink(pVal);
	if (IsEmpty())
		pFirst = t;
	else
		pLast->pNext = t;
	pLast = t;
	t->pNext = pStop;	
	ListLen++;
	Reset();
}

void TDatList::InsCurrent(PTDatValue pVal)
{
	if(pCurrLink == pFirst)
		InsFirst(pVal);
	else
	{
		PTDatLink t = new TDatLink(pVal);
		t->pNext = pCurrLink;
		pPrevLink->pNext = t;
		ListLen++;
		Reset();
	}
}

void TDatList::DelFirst()
{
	if (IsEmpty()) throw - 1;
	PTDatLink q = pFirst;
	pFirst = pFirst->GetNextDatLink();
	DelLink(q);
	ListLen--;
	Reset();
}

void TDatList::DelCurrent()
{
	if(IsEmpty()) throw -1;
	if (pCurrLink == pFirst) DelFirst();
	else
	{
		if (pCurrLink == pLast)
		{
			pLast = pPrevLink;
			delete pCurrLink;
			pLast->pNext = pStop;
		}
		else
		{
			PTDatLink q = pCurrLink;
			pPrevLink->SetNextLink(q->GetNextLink());
			delete q;
		}
		ListLen--;
		Reset();
	}
}


void TDatList::DelList()
{
	while (!IsEmpty())
		DelFirst();
	pFirst = pPrevLink = pCurrLink = pLast = pStop = NULL;
	CurrPos = -1;
}
