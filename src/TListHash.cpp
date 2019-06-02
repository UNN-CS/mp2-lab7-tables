#include "TListHash.h"

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
    delete [] pList; //[]
}

int TListHash::IsFull() const {
    return 0;
}

PTDatValue TListHash::FindRecord(TKey k) {
    PTTabRecord pVal = nullptr;
    int _k = HashFunc(k) % TabSize; //функция расстановки

    for (pList[_k]->Reset(); !pList[_k]->IsListEnded(); pList[_k]->GoNext())
        if (((PTTabRecord)pList[_k]->GetDatValue())->GetKey() == k)
        {
            pVal = (PTTabRecord)pList[_k]->GetDatValue();
            break;
        }
    Efficiency += pList[_k]->GetCurrentPos() + 1; // номер тек позиции = к-ву итераций поиска
    return pVal;
}

void TListHash::InsRecord(TKey k, PTDatValue pVal) {
    int j = HashFunc(k) % TabSize;
    for (pList[j]->Reset(); !pList[j]->IsListEnded(); pList[j]->GoNext())
    {
        if (((PTTabRecord)pList[j]->GetDatValue())->GetKey() == k)
        {
            Efficiency += pList[j]->GetCurrentPos() + 1;
            ((PTTabRecord)pList[j]->GetDatValue())->SetValuePtr(pVal);
            return;
        }
    }
    Efficiency += pList[j]->GetCurrentPos() + 1;
    ++DataCount;
    pList[j]->InsLast(new TTabRecord(k, pVal));
}

void TListHash::DelRecord(TKey k) {
    CurrList = HashFunc(k) % TabSize;
    PTDatList pL = pList[CurrList];
    for (pL->Reset(); !pL->IsListEnded(); pL->GoNext()) {
        ++Efficiency;
        if (PTTabRecord(pL->GetDatValue())->Key == k) {
            pL->DelCurrent();
            DataCount--;
            break;
        }
    }
}

int TListHash::Reset() {
    for (CurrList = 0; CurrList < TabSize; ++CurrList)
    {
        if (!pList[CurrList]->IsEmpty())
        {
            pList[CurrList]->Reset();
            break;
        }
    }
    return IsTabEnded();
}

int TListHash::IsTabEnded() const {
    return CurrList >= TabSize;
}

int TListHash::GoNext() {
    if (IsTabEnded())
        return IsTabEnded();
    pList[CurrList]->GoNext();
    if (!pList[CurrList]->IsListEnded())
        return IsTabEnded();
    for (++CurrList; CurrList < TabSize; ++CurrList)
    {
        if (!pList[CurrList]->IsEmpty())
        {
            pList[CurrList]->Reset();
            break;
        }
    }
    return IsTabEnded();
}

TKey TListHash::GetKey() const {
    if ((CurrList < 0) || (CurrList >= TabSize))
        return std::string("");
    PTTabRecord pRec = PTTabRecord(pList[CurrList]->GetDatValue());
    return (pRec == nullptr) ? std::string("") : pRec->Key;
}

PTDatValue TListHash::GetValuePTR() const {
    if ((CurrList < 0) || (CurrList >= TabSize))
        return nullptr;
    PTTabRecord pRec = PTTabRecord(pList[CurrList]->GetDatValue());
    return (pRec == nullptr) ? nullptr : pRec->pValue;
}