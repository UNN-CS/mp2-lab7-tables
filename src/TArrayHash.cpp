// TArrayHash.cpp
#include "TArrayHash.h"

TArrayHash::TArrayHash(int Size, int Step) : THashTable() {
    pRecs = new PTTabRecord[Size];
    TabSize = Size;
    HashStep = Step;
    for (int i = 0; i < TabSize; ++i)
        pRecs[i] = nullptr;
    CurrPos = FreePos = 0;
    pMark = new TTabRecord(std::string(""), nullptr);
}

TArrayHash::~TArrayHash() {
    for (int i = 0; i < TabSize; ++i)
        if ((pRecs[i] != nullptr) && (pRecs[i] != pMark)) delete pRecs[i];
    delete[] pRecs;
    delete pMark;
}

PTDatValue TArrayHash::FindRecord(TKey k) {
    PTTabRecord p = nullptr;
    int eff = DataCount;
    int _k = HashFunc(k) % TabSize;
    for (int i = 0; i < TabSize; ++i)
    {
        if (pRecs[_k] == nullptr)
        {
            eff = i + 1;
            break;
        }
        if (pRecs[_k]->GetKey() == k)
        {
            eff = i + 1;
            p = pRecs[_k];
            break;
        }
        _k = GetNextPos(_k);
    }
    Efficiency += eff;
    return p;
}

void TArrayHash::InsRecord(TKey k, PTDatValue pVal) {
    int pre = -1;
    int _k = HashFunc(k) % TabSize;
    for (int i = 0; i < TabSize; ++i)
    {
        if (pRecs[_k] == nullptr)
        {
            Efficiency += i + 1;
            ++DataCount;
            if (pre > -1)
            {
                pRecs[pre]->SetKey(k);
                pRecs[pre]->SetValuePtr(pVal);
                return;
            }
            pRecs[_k] = new TTabRecord(k, pVal);
            return;
        }
        if ((pre < 0) && (pRecs[_k]->GetKey() == "") && (pRecs[_k]->GetValuePTR() == nullptr))
            pre = _k;
        else if (pRecs[_k]->GetKey() == k)
        {
            Efficiency += i + 1;
            pRecs[_k]->SetValuePtr(pVal);
            return;
        }
        _k = GetNextPos(_k);
    }
    if (pre > -1)
    {
        Efficiency += TabSize;
        ++DataCount;
        pRecs[pre]->SetKey(k);
        pRecs[pre]->SetValuePtr(pVal);
        return;
    }
    throw "insert in full table";
}

void TArrayHash::DelRecord(TKey k) {
    int _k = HashFunc(k) % TabSize;
    for (int i = 0; i < TabSize; ++i)
    {
        if (pRecs[_k] == nullptr)
        {
            Efficiency += i + 1;
            return;
        }
        if (pRecs[_k]->GetKey() == k)
        {
            Efficiency += i + 1;
            pRecs[_k]->SetKey("");
            pRecs[_k]->SetValuePtr(nullptr);
            --DataCount;
            return;
        }
        _k = GetNextPos(_k);
    }
    Efficiency += TabSize;
}

int TArrayHash::Reset() {
    CurrPos = 0;
    return IsTabEnded();
}

int TArrayHash::IsTabEnded() const {
    return CurrPos >= TabSize;
}

int TArrayHash::GoNext() {
    if (!IsTabEnded()) {
        while (++CurrPos < TabSize)
            if ((pRecs[CurrPos] != nullptr) && (pRecs[CurrPos] != pMark)) break;
    }
    return IsTabEnded();
}

TKey TArrayHash::GetKey() const {
    return ((CurrPos < 0) || (CurrPos >= TabSize)) ? std::string("") : pRecs[CurrPos]->Key;
}

PTDatValue TArrayHash::GetValuePTR() const {
    return ((CurrPos < 0) || (CurrPos >= TabSize)) ? nullptr : pRecs[CurrPos]->pValue;
}
