#include "listhash.h"

#include "datlist.h"
#include "tabrecord.h"

TListHash::TListHash(int size)
        : THashTable() {
    tabSize = size;
    pList = new PTDatList[size];
    for (int i = 0; i < tabSize; ++i) {
        pList[i] = new TDatList();
    }
    currList = 0;
}

TListHash::~TListHash() {
    for (int i = 0; i < tabSize; ++i) {
        delete pList[i];
    }
    delete[] pList; 
}

bool TListHash::IsFull() const {
    return false;
}

TKey TListHash::GetKey() const {
    if (IsTabEnded()) {
        return "";
    }
    return ((PTTabRecord)pList[currList]->GetDatValue())->GetKey();
}

PTDatValue TListHash::GetValuePtr() const {
    if (IsTabEnded()) {
        return nullptr;
    }
    return ((PTTabRecord)pList[currList]->GetDatValue())->GetValuePtr();
}

PTDatValue TListHash::FindRecord(TKey k) {
    PTTabRecord p = nullptr;
    int j = HashFunc(k) % tabSize;
    for (pList[j]->Reset(); !pList[j]->IsListEnded(); pList[j]->GoNext()) {
        if (((PTTabRecord)pList[j]->GetDatValue())->GetKey() == k) {
            p = (PTTabRecord)pList[j]->GetDatValue();
            break;
        }
    }
    efficiency += pList[j]->GetCurrentPos() + 1;
    return p;
}

void TListHash::InsRecord(TKey k, PTDatValue pVal) {
    int j = HashFunc(k) % tabSize;
    for (pList[j]->Reset(); !pList[j]->IsListEnded(); pList[j]->GoNext()) {
        if (((PTTabRecord)pList[j]->GetDatValue())->GetKey() == k) {
            efficiency += pList[j]->GetCurrentPos() + 1;
            ((PTTabRecord)pList[j]->GetDatValue())->SetValuePtr(pVal);
            return;
        }
    }
    efficiency += pList[j]->GetCurrentPos() + 1;
    ++dataCount;
    pList[j]->InsLast(new TTabRecord(k, pVal));
}

void TListHash::DelRecord(TKey k) {
    int j = HashFunc(k) % tabSize;
    for (pList[j]->Reset(); !pList[j]->IsListEnded(); pList[j]->GoNext()) {
        if (((PTTabRecord)pList[j]->GetDatValue())->GetKey() == k) {
            efficiency += pList[j]->GetCurrentPos() + 1;
            pList[j]->DelCurrent();
            --dataCount;
            return;
        }
    }
    efficiency += pList[j]->GetCurrentPos() + 1;
}

bool TListHash::Reset() {
    for (currList = 0; currList < tabSize; ++currList) {
        if (!pList[currList]->IsEmpty()) {
            pList[currList]->Reset();
            break;
        }
    }
    return IsTabEnded();
}

bool TListHash::IsTabEnded() const {
    return currList >= tabSize;
}

bool TListHash::GoNext() {
    if (IsTabEnded()) {
        return IsTabEnded();
    }
    pList[currList]->GoNext();
    if (!pList[currList]->IsListEnded()) {
        return IsTabEnded();
    }
    for (++currList; currList < tabSize; ++currList) {
        if (!pList[currList]->IsEmpty()) {
            pList[currList]->Reset();
            break;
        }
    }
    return IsTabEnded();
}

