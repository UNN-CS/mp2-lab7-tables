#include "TListHash.h"

TListHash::TListHash(int Size) : THashTable()
{
    pList = new PTDatList[Size];
    TabSize = Size;
    CurrList = 0;
    for (int i = 0; i < TabSize; i++)
        pList[i] = new TDatList;
}

TListHash::~TListHash()
{
    for (int i = 0; i < TabSize; ++i)
        delete pList[i];
    delete[] pList;
}

int TListHash::IsFull ( ) const
{
    return 0;
}

TKey TListHash::GetKey() const
{
    if ((CurrList < 0) || IsTabEnded())
        return string("");
    PTTabRecord pRec = PTTabRecord(pList[CurrList]->GetDatValue());
    if (pRec == nullptr)
        return string("");
    else
        pRec->GetKey();
}

PTDatValue TListHash::GetValuePTR() const
{
    if (CurrList < 0 || IsTabEnded())
        return nullptr;
    PTTabRecord pRec = PTTabRecord(pList[CurrList]->GetDatValue());
    return pRec ? pRec->pValue : nullptr;
}

PTDatValue TListHash::FindRecord(TKey k)
{
    PTDatValue pValue = nullptr;
    CurrList = HashFunc(k) % TabSize;
    PTDatList pL = pList[CurrList];
    Efficiency++;
    for (pL->Reset(); !pL->IsListEnded(); pL->GoNext())
    {
        if (PTTabRecord(pL->GetDatValue())->GetKey() == k)
        {
            pValue = PTTabRecord(pL->GetDatValue())->pValue;
            break;
        }
    }
    Efficiency += pL->GetCurrentPos() + 1;
    if (pValue == nullptr)
        SetRetCode(TabNoRec);
    else
        SetRetCode(TabOK);
    return pValue;
}

void TListHash::InsRecord(TKey k, PTDatValue pVal)
{
    PTDatValue tmp = FindRecord(k);
    if (tmp != nullptr)
    {
        PTTabRecord(pList[CurrList]->GetDatValue())->SetValuePtr(pVal);
        Efficiency += pList[CurrList]->GetCurrentPos() + 1;
        return;
    }
    Efficiency += pList[CurrList]->GetCurrentPos() + 1;
    DataCount++;
    pList[CurrList]->InsLast(new TTabRecord(k, pVal));
}

void TListHash::DelRecord(TKey k)
{
    PTDatValue tmp = FindRecord(k);
    if (tmp != nullptr)
    {
        pList[CurrList]->DelCurrent();
        DataCount--;
        Efficiency += pList[CurrList]->GetCurrentPos() + 1;
    }
}

int TListHash::Reset()
{
    CurrList = 0;
    pList[CurrList]->Reset();
    return IsTabEnded();
}

int TListHash::IsTabEnded (void) const
{
    return CurrList >= TabSize;
}

int TListHash::GoNext()
{
    if (!pList[CurrList]->IsListEnded())
        pList[CurrList]->GoNext();
    while (pList[CurrList]->IsListEnded())
    {
        CurrList = (CurrList + 1) % TabSize;
        pList[CurrList]->Reset();
    }
}
