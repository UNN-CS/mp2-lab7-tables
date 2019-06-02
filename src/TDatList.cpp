#include "TDatList.h"

PTDatLink TDatList::GetLink(PTDatValue pVal, PTDatLink pLink)
{
    return new TDatLink(pVal, pLink);
}

void TDatList::DelLink(PTDatLink pLink)
{
    if (pLink->GetDatValue() != nullptr)
        delete pLink->GetDatValue();
    delete pLink;
}

TDatList::TDatList()
{
    pFirst = pLast = pCurrLink = pPrevLink = pStop = nullptr;
    CurrPos = 0;
    ListLen = 0;
}

PTDatValue TDatList::GetDatValue(TLinkPos mode) const
{
    switch (mode)
    {
    case TLinkPos::CURRENT:
        if (pCurrLink == nullptr)
            throw "reference to nonexistent link";
        return pCurrLink->GetDatValue();
    case TLinkPos::FIRST:
        if (pFirst == nullptr)
            throw "reference to nonexistent link";
        return pFirst->GetDatValue();
    case TLinkPos::LAST:
        if (pLast == nullptr)
            throw "reference to nonexistent link";
        return pLast->GetDatValue();
    default:
        throw "invalid mode";
    }
}

void TDatList::SetCurrentPos(int pos)
{
    if (pos > ListLen || pos < 0)
        throw "invalid position";
    if (pos < CurrPos)
    {
        pCurrLink = pPrevLink = pFirst;
        CurrPos = 0;
    }
    for (; CurrPos < pos; ++CurrPos)
    {
        pPrevLink = pCurrLink;
        pCurrLink = (PTDatLink)pCurrLink->pNext;
    }
}

int TDatList::GetCurrentPos(void) const
{
    return CurrPos;
}

void TDatList::Reset(void)
{
    pPrevLink = pCurrLink = pFirst;
    CurrPos = 0;
}

int TDatList::IsListEnded(void) const
{
    return pCurrLink == pStop;
}

int TDatList::GoNext(void)
{
    if (IsListEnded())
        return 1;
    pPrevLink = pCurrLink;
    pCurrLink = (PTDatLink)pCurrLink->pNext;
    ++CurrPos;
    return pCurrLink == pStop;
}

void TDatList::InsFirst(PTDatValue pVal)
{
    if (IsEmpty())
    {
        pFirst = new TDatLink(pVal, pStop);
        pLast = pCurrLink = pPrevLink = pFirst;
        CurrPos = 0;
        ++ListLen;
    }
    else
    {
        pFirst = new TDatLink(pVal, pFirst);
        ++ListLen;
        ++CurrPos;
        if (CurrPos == 1)
        {
            pPrevLink = pFirst;
        }
    }
}

void TDatList::InsLast(PTDatValue pVal)
{
    if (IsEmpty())
    {
        InsFirst(pVal);
    }
    else
    {
        pLast->pNext = new TDatLink(pVal, pStop);
        pLast = (PTDatLink)pLast->pNext;
        ++ListLen;
    }
}

void TDatList::InsCurrent(PTDatValue pVal)
{
    if ((IsEmpty()) || (CurrPos == 0))
    {
        InsFirst(pVal);
    }
    else
    {
        pPrevLink->pNext = new TDatLink(pVal, pCurrLink);
        ++CurrPos;
        pPrevLink = (PTDatLink)pPrevLink->pNext;
        ++ListLen;
    }
}

void TDatList::DelFirst(void)
{
    if (IsEmpty())
        return;
    else
    {
        PTDatLink p = (PTDatLink)pFirst->pNext;
        DelLink(pFirst);
        pFirst = p;
        --ListLen;
        --CurrPos;
        if (CurrPos == 0)
        {
            pPrevLink = p;
        }
        else if (CurrPos == -1)
        {
            pPrevLink = p;
            pCurrLink = p;
            CurrPos = 0;
        }
    }
}

void TDatList::DelCurrent(void)
{
    if (IsEmpty() || IsListEnded())
        return;
    else if (CurrPos == 0)
        DelFirst();
    else
    {
        --ListLen;
        PTDatLink p = (PTDatLink)pCurrLink->pNext;
        pPrevLink->pNext = p;
        DelLink(pCurrLink);
        pCurrLink = p;
    }
}

void TDatList::DelList(void)
{
    PTDatLink p;
    while (pFirst != pStop)
    {
        p = pFirst;
        pFirst = (PTDatLink)pFirst->pNext;
        DelLink(p);
    }
    pCurrLink = pPrevLink = pLast = pStop;
    ListLen = CurrPos = 0;
}
