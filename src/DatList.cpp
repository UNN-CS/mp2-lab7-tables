#include "DatList.h"




PTDatLink TDatList::GetLink(PTDatValue pVal, PTDatLink pLink) {
    PTDatLink tmp = new TDatLink(pVal, pLink);
    if(tmp == NULL)
        throw ListNoMem;
    return tmp;
}

void TDatList::DelLink (PTDatLink pLink) {
    if(pLink != NULL)
    {
        if(pLink->pValue != NULL)
            delete pLink->pValue;
        delete pLink;
    }
}

TDatList::TDatList() {
    pFirst = pLast = pStop = pPrevLink = pCurrLink = NULL;
	ListLen = 0, CurrPos = -1;
}

PTDatValue TDatList::GetDatValue(TLinkPos mode) const {
    PTDatLink tmp;
    switch(mode) {
        case FIRST: tmp = pFirst; break;
        case LAST: tmp = pLast; break;
        default: tmp = pCurrLink; break;
    }
    return (tmp == NULL)?NULL:tmp->pValue;
}

void TDatList::SetCurrentPos(int pos) {
    Reset();
    for(int i = 0; i < pos; i++)
        GoNext();
}

int TDatList::GetCurrentPos() const {
    return CurrPos;
}

void TDatList::Reset() {//???
    pPrevLink = pStop;
    if(IsEmpty()) {
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
    if(pCurrLink == pStop)
        throw ListNoPos;
    pPrevLink = pCurrLink;
    pCurrLink = pCurrLink->GetNextDatLink();
    CurrPos++;
}

void TDatList::InsFirst(PTDatValue pVal) {
    PTDatLink tmp = GetLink(pVal, pFirst);
    if(tmp == NULL)
        throw ListNoMem;
    pFirst = tmp;
    ListLen++;
    //проверка пустоты списка перед вставкой
    if(ListLen == 1) {
        pLast = tmp;
        Reset();
    }
    //корректировка текущей позиции - отличие обработки для начала списка
    else if(CurrPos == 0)
        pCurrLink = tmp;
    else
        CurrPos++;
}

void TDatList::InsLast(PTDatValue pVal) {
    PTDatLink tmp = GetLink(pVal, pStop);
    if(tmp == NULL)
        throw ListNoMem;
    if(pLast != NULL)
        pLast->SetNextLink(tmp);
    pLast = tmp;
    ListLen++;
    //проверка пустоты списка перед вставкой
    if(ListLen == 1) {
        pFirst = tmp;
        Reset();
    }
    //корректировка текущей позиции - отличие pCurrLink за концом списка
    if(IsListEnded())
        pCurrLink = tmp;
}

void TDatList::InsCurrent(PTDatValue pVal) {
    if(IsEmpty() || pCurrLink == pFirst)
        InsFirst(pVal);
    else if (IsListEnded())
        InsLast(pVal);
    else {
        PTDatLink tmp = GetLink(pVal, pCurrLink);
        if(tmp == NULL)
            throw ListNoMem;
        pCurrLink = tmp;
        pPrevLink->SetNextLink(tmp);
        ListLen++;
    }
}

void TDatList::DelFirst() {
    if(IsEmpty())
        throw ListEmpty;
    PTDatLink tmp = pFirst;
    pFirst = pFirst->GetNextDatLink();
    DelLink(tmp);
    --ListLen;
    if(IsEmpty()){
        pLast = pStop;
        Reset();
    }
    //корректировка текущей позиции - отличие обработки для начала списка
    else if(CurrPos == 0)
        pCurrLink = pFirst;
    else if(CurrPos == 1)
        pPrevLink = pStop;
    if(CurrPos > 0)
        --CurrPos;
}

void TDatList::DelCurrent() {
    if(pCurrLink == pStop)
        throw ListNoPos;
    if(pCurrLink == pFirst)
        DelFirst();
    else {
        PTDatLink tmp = pCurrLink;
        //отработка ситуации удаления последнего звена
		pCurrLink = pCurrLink->GetNextDatLink();
		pPrevLink->SetNextLink(pCurrLink);
        DelLink(tmp);
        --ListLen;
    }
}

void TDatList::DelList() {
    while(!IsEmpty())
        DelFirst();
    pFirst = pLast = pPrevLink = pCurrLink = pStop;
    CurrPos = -1;
}
