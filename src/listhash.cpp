#include "listhash.h"

TListHash::TListHash(int Size) : THashTable() {
    pList = new PTDatList[Size];
    TabSize = Size;
    CurrList = 0;
    for (int i = 0; i < TabSize; ++i)
        pList[i] = new TDatList;
}

TListHash::~TListHash() {
    for (int i = 0; i < TabSize; ++i)
        delete pList[i];
    delete[] pList;
}

int TListHash::IsFull() const
{
    PTDatLink pLink = new TDatLink();
    int tmp = (pLink == nullptr);
    delete pLink;
    return tmp;
}

PTDatValue TListHash::FindRecord(TKey k) {
    PTDatValue pValue = nullptr;
    CurrList = HashFunc(k) % TabSize;
    PTDatList pL = pList[CurrList];
    for (pL->Reset(); !pL->IsListEnded(); pL->GoNext()) {
        if (PTTabRecord(pL->GetDatValue())->Key == k) {
            pValue = PTTabRecord(pL->GetDatValue())->pValue;
            break;
        }
    }
    if (pValue == nullptr)
        SetRetCode(TabNoRec);
    else
        SetRetCode(TabOK);

    Efficiency += pL->GetCurrentPos() + 1;
    return pValue;
}

void TListHash::InsRecord(TKey k, PTDatValue pVal)
{
    CurrList = HashFunc(k) % TabSize;
    pList[CurrList]->InsLast(new TTabRecord(k, pVal));
    DataCount++;
    Efficiency = pList[CurrList]->GetListLength();
}

void TListHash::DelRecord(TKey k) 
{
    if (FindRecord(k) == nullptr)
        SetRetCode(TabNoRec);
    else
    {
        CurrList = HashFunc(k) % TabSize;
        PTDatList pL = pList[CurrList];
        for (pL->Reset(); !pL->IsListEnded(); pL->GoNext())
        {
            ++Efficiency;
            if (PTTabRecord(pL->GetDatValue())->Key == k)
            {
                pL->DelCurrent();
                DataCount--;
                break;
            }
        }
    }
}

int TListHash::Reset(void)
{
    for (CurrList = 0; CurrList < TabSize; CurrList++)
    {
        if (!pList[CurrList]->IsEmpty())
        {
            pList[CurrList]->Reset();
            break;
        }
    }
    return IsTabEnded();
}

int TListHash::GoNext(void)
{
    if (IsTabEnded())
        return IsTabEnded();

    if (!pList[CurrList]->IsListEnded())
        pList[CurrList]->GoNext();
    else
    {
        for (++CurrList; CurrList < TabSize; CurrList++)
        {
            if (!pList[CurrList]->IsEmpty())
            {
                pList[CurrList]->Reset();
                break;
            }
        }
    }

    return IsTabEnded();
}

int TListHash::IsTabEnded(void) const
{
    return CurrList >= TabSize;
}

TKey TListHash::GetKey() const 
{
    if (CurrList < 0 || CurrList >= TabSize)
        return "";
    PTTabRecord pRec = PTTabRecord(pList[CurrList]->GetDatValue());
    return pRec ? pRec->Key : "";
}

PTDatValue TListHash::GetValuePtr() const 
{
    if (CurrList < 0 || CurrList >= TabSize)
        return nullptr;
    PTTabRecord pRec = PTTabRecord(pList[CurrList]->GetDatValue());
    return pRec ? pRec->pValue : nullptr;
}