#include "TListHash.h"

TListHash::TListHash(int size) :THashTable() {
    pList = new PTDatList[size];
    TabSize = size;
    CurrList = 0;
    for (int i = 0; i < TabSize; ++i) pList[i] = new TDatList;
}

TListHash::~TListHash() {
    for (int i = 0; i < TabSize; ++i) delete pList[i];
    delete[] pList;
}

int TListHash::IsFull()const {
    PTDatLink pLink = new TDatLink();
    int temp = (pLink == NULL);
    delete pLink;
    return temp;
}

PTDatValue TListHash::FindRecord(TKey k) {
    PTDatValue pVal = NULL;
    CurrList = HashFunc(k) % TabSize;
    PTDatList pl = pList[CurrList];
    Efficiency = 0;
    for (pl->Reset(); !pl->IsListEnded(); pl->GoNext())
        if (PTTabRecord(pl->GetDatValue())->GetKey() == k)
        {
            pVal = PTTabRecord(pl->GetDatValue())->GetValuePTR();
            break;
        }
    Efficiency = pl->GetCurrentPos() + 1;
    if (pVal == NULL)
        SetRetCode(TabNoRec);
    else SetRetCode(TabOK);
    return pVal;
}

void TListHash::InsRecord(TKey k, PTDatValue pVal) {
    if (FindRecord(k) == NULL)
    {
        SetRetCode(TabOK);
        CurrList = HashFunc(k) % TabSize;
        PTDatList pl = pList[CurrList];
        PTTabRecord tmp = new TTabRecord(k, pVal);
        pl->InsLast(tmp);
        DataCount++;
    }
    else
        SetRetCode(TabRecDbl);
}

void TListHash::DelRecord(TKey k) {
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

int TListHash::Reset() {
    CurrList = 0;
    pList[CurrList]->Reset();
    return IsTabEnded();
}

int TListHash::IsTabEnded() const {
    return CurrList >= TabSize;
}

int TListHash::GoNext() {
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

TKey TListHash::GetKey() const {
    if ((CurrList < 0) || (CurrList >= TabSize)) return string("");
    PTTabRecord rec = PTTabRecord(pList[CurrList]->GetDatValue());
    return (rec == NULL) ? string("") : rec->GetKey();
}

PTDatValue TListHash::GetValuePTR() const {
    if ((CurrList < 0) || (CurrList >= TabSize)) return NULL;
    PTTabRecord rec = PTTabRecord(pList[CurrList]->GetDatValue());
    return (rec == NULL) ? NULL : rec->GetValuePTR();
}
