#include "tarrayhash.h"

TArrayHash::TArrayHash(int Size, int Step):THashTable() {
    pRecs = new PTTabRecord[Size];
    TabSize = Size;
    HashStep = Step;
    for(int i = 0; i < TabSize; i++)
        pRecs[i] = nullptr;
    pMark = new TTabRecord(std::string(""), nullptr);
}

TArrayHash::~TArrayHash() {
    for(int i = 0; i < TabSize; i++)
    {
        if(pRecs[i] != nullptr && pRecs[i] != pMark)
            delete pRecs[i];
    }
    delete[] pRecs;
    delete pMark;
}

PTDatValue:: TArrayHash::FindRecord(TKey k) {
    PTDatValue pValue = nullptr;
    FreePos = -1;
    CurrPos = HashFunc(k)%TabSize;
    for(int i = 0; i <  TabSize; i++) {
        Efficiency++;
        if(pRecs[CurrPos] == nullptr)
            break;
        else if(pRecs[CurrPos] == pMark) {
            if(FreePos == -1)
                FreePos = CurrPos;
        }
        else if (pRecs[CurrPos]->Key == k) {
            pValue = pRecs[CurrPos]->pValue;
            break;
        }
        CurrPos = GetNextPos(CurrPos);
    }
    return pValue;
}

void TArrayHash::InsRecord(TKey k, PTDatValue pVal) {
    if(IsFull())
        throw TabFull;
    PTDatValue tmp = FindRecord(k);
    if(tmp != nullptr)
        throw(TabRecDbl);
    if(FreePos != -1) {
        CurrPos = FreePos;
    }
    pRecs[CurrPos] = new TTabRecord(k, pVal);
    DataCount++;
    // >:-/
}

void TArrayHash::DelRecord(TKey k) {
    PTDatValue tmp = FindRecord(k);
    if(tmp == nullptr) {
        throw TabNoRec;
    }
    delete pRecs[CurrPos];
    pRecs[CurrPos] = pMark;
    DataCount--;
    // >:-/
}

int TArrayHash::Reset() {
    CurrPos = 0;
    while(CurrPos != TabSize) {
        if(pRecs[CurrPos] != nullptr && pRecs[CurrPos] != pMark)
            break;
        CurrPos++;
    }
    return IsTabEnded();
    // >:-/
}

int TArrayHash::IsTabEnded() const {
    return CurrPos >= TabSize;
}

int TArrayHash::GoNext() {
    if(!IsTabEnded())
        while(++CurrPos < TabSize)
            if(pRecs[CurrPos] != nullptr && pRecs[CurrPos] != pMark)
                break;
    return IsTabEnded();
}

TKey TArrayHash::GetKey() const {
    return (CurrPos < 0 || CurrPos >= TabSize)?std::string(""):pRecs[CurrPos]->Key;
}

PTDatValue::TArrayHash::GetValuePtr() const {
    return (CurrPos < 0 || CurrPos >= TabSize)?nullptr:pRecs[CurrPos]->pValue;
}
