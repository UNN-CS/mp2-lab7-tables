
#include "DatList.h"

TDatList::TDatList()
{
    pFirst = pLast = pStop = NULL; 
    ListLen = 0;
    Reset();
}

PTDatLink TDatList::GetLink (PTDatValue pVal, PTDatLink pLink)
{
    PTDatLink temp = new TDatLink (pVal, pLink); // выделение звена
    if (temp == NULL)
        SetRetCode(ListNoMem);
    else
        SetRetCode(ListOK);
    return temp;
}

void TDatList::DelLink (PTDatLink pLink)
{
    if (pLink != NULL)
    {
        if (pLink->pValue != NULL)
            delete pLink;
    }
    SetRetCode(ListOK);
}

PTDatValue TDatList::GetDatValue (TLinkPos mode) const 
{
    PTDatLink temp;
    switch (mode)
    {
        case FIRST: temp = pFirst; break;
        case LAST: temp = pLast; break;
        default: temp = pCurrLink; break;
    }
    return (temp == NULL) ? NULL : temp -> pValue;
}

int TDatList::SetCurrentPos (int pos) // установить текущее звено
{
    Reset();
    for (int i = 0; i < pos; i++)
        GoNext();
    SetRetCode(ListOK);
    return RetCode;
}

// методы навигации

int TDatList::GetCurrentPos (void) const // получить номер текущего звена
{
    return CurrPos;
}

int TDatList::Reset (void) // установить на начало списка
{
    pPrevLink = pStop; 
    if (IsEmpty())
    {
        pCurrLink = pStop;
        CurrPos = -1; 
        SetRetCode(ListEmpty);
    }
    else
    {
        pCurrLink = pFirst;
        CurrPos = 0;
        SetRetCode(ListOK);
    }
    return RetCode;
}

int TDatList::GoNext(void) // сдвиг вправо текущего звена   // а вернуть 1 при сдвиге последнего звена?
{
    if (pCurrLink == pStop)
        SetRetCode(ListNoPos);
    else
    {
        SetRetCode(ListOK);
        pPrevLink = pCurrLink;
        pCurrLink = pCurrLink->GetNextDatLink();
        CurrPos++;
    }
    return RetCode;
}

int TDatList::IsListEnded (void) const // =1 после применения GoNext для последнего звена списка
{
    return pCurrLink == pStop;
}

// методы вставки звеньев

void TDatList::InsFirst (PTDatValue pVal) // перед первым
{
    PTDatLink temp = GetLink(pVal, pFirst);
    if (temp == NULL)
        SetRetCode(ListNoMem);
    else   
        {
            pFirst = temp;
            ListLen++;
            // проверка пустоты списка перед вставкой
            if (ListLen == 1)
            {
                pLast = temp;
                Reset();
            }
            // корректировка текущей позиции - отличие обработки для начала списка
            else if (CurrPos == 0)
                pCurrLink = temp; 
            else 
                CurrPos++;
            SetRetCode(ListOK);
        }
}

void TDatList::InsLast (PTDatValue pVal) // вставить последним
{
    PTDatLink temp = GetLink(pVal, pStop);
    if (temp == NULL)
        SetRetCode(ListNoMem);
    else
    {
        if (pLast != NULL)
            pLast->SetNextLink(temp);
        pLast = temp;
        ListLen++;
        // проверка пустоты списка перед вставкой 
        if (ListLen == 1)
        {
            pFirst = temp;
            Reset();
        }
        // корректировка текущей позиции - отличие при pCurrLink за концом списка
        if (IsListEnded())
            pCurrLink = temp;
        SetRetCode(ListOK);
    }
}

void TDatList::InsCurrent (PTDatValue pVal ) // вставить перед текущим
{
    if (IsEmpty() || (pCurrLink == pFirst))
        InsFirst(pVal);
    else if (IsListEnded())
        InsLast(pVal);
    else if (pPrevLink == pStop)
        SetRetCode(ListNoPos);
    else
    {
        PTDatLink temp = GetLink(pVal, pCurrLink);
        if (temp == NULL)
            SetRetCode(ListNoMem);
        else
        {
            pCurrLink = temp;
            pPrevLink->SetNextLink(temp);
            ListLen++;
            SetRetCode(ListOK);
        }
    }
}

// методы удаления звеньев

void TDatList::DelFirst (void)
{
    if (IsEmpty())
        SetRetCode(ListEmpty);
    else
    {
        PTDatLink temp = pFirst;
        pFirst = pFirst->GetNextDatLink();
        DelLink(temp);
        ListLen--;
        if (IsEmpty())
        {
            pLast = pStop;
            Reset();
        }
        // корректировка текущей позиции - отличие обработки для начала списка
        else if (CurrPos == 0)
            pCurrLink == pFirst;
        else if (CurrPos == 1)
            pPrevLink == pStop;
        if (CurrPos > 0)
            CurrPos--;
        SetRetCode(ListOK);
    }
}

void TDatList::DelCurrent (void)
{
    if (pCurrLink == pStop)
        SetRetCode(ListNoPos);
    else if (pCurrLink == pFirst)
        DelFirst();
    else
    {
        PTDatLink temp = pCurrLink;
        pCurrLink = pCurrLink->GetNextDatLink(); // !
        pPrevLink->SetNextLink(pCurrLink);
        DelLink(temp);
        ListLen--;
        // обработка ситуации удаления последнего звена
        if (pCurrLink == pLast)   // ??? 
        {
            pLast = pPrevLink;
            pCurrLink = pStop; // ? почему pStop, а не pPrevLink?
        }
        SetRetCode(ListOK);
    }
}

void TDatList::DelList (void) // удалить весь список 
{
    while (! IsEmpty())
        DelFirst();
    pFirst = pLast = pPrevLink = pCurrLink = pStop;
    CurrPos = -1;
}