#include "arrayhash.h"

#include "tabrecord.h"

TArrayHash::TArrayHash(int size, int step)
        : THashTable() {
    pRecs = new PTTabRecord[size];
    tabSize = size;
    hashStep = step;
    freePos = 0;
    currPos = 0;
    pMark = nullptr;
    for (int i = 0; i < size; ++i) {
        pRecs[i] = pMark;
    }
}

TArrayHash::~TArrayHash() {
    for (int i = 0; i < tabSize; ++i) {
        if (pRecs[i] != pMark) {
            delete pRecs[i];
        }
    }
    delete pRecs;
    delete pMark;
}

bool TArrayHash::IsFull() const {
    return dataCount >= tabSize;
}

TKey TArrayHash::GetKey() const {
    return pRecs[currPos]->GetKey();
}

PTDatValue TArrayHash::GetValuePtr() const {
    return pRecs[currPos]->GetValuePtr();
}

PTDatValue TArrayHash::FindRecord(TKey k) {
    uint64_t pos = HashFunc(k) % tabSize;
    for (int i = 0; i < tabSize; ++i) {
        ++efficiency;
        if (pRecs[pos] == pMark) {
            return nullptr;
        }
        if (pRecs[pos]->GetKey() == k) {
            return pRecs[pos]->GetValuePtr();
        }
        pos = GetNextPos(pos);
    }
    return nullptr;
}

void TArrayHash::InsRecord(TKey k, PTDatValue pVal) {
    uint64_t pos = HashFunc(k) % tabSize;
    for (int i = 0; i < tabSize; ++i) {
        ++efficiency;
        if (pRecs[pos] == pMark) {
            pRecs[pos] = new TTabRecord(k, pVal);
            ++dataCount;
            return;
        }
        pos = GetNextPos(pos);
    }
    return;
}

void TArrayHash::DelRecord(TKey k) {
    uint64_t pos = HashFunc(k) % tabSize;
    for (int i = 0; i < tabSize; ++i) {
        ++efficiency;
        if (pRecs[pos]->GetKey() == k) {
            delete pRecs[pos];
            pRecs[pos] = pMark;
            --dataCount;
            return;
        }
        pos = GetNextPos(pos);
    }
}

bool TArrayHash::Reset() {
    for (currPos = 0; currPos < tabSize; ++currPos) {
        if (pRecs[currPos] != pMark) {
            return true;
        }
    }
    return false;
}

bool TArrayHash::IsTabEnded() const {
    return currPos >= tabSize;
}

bool TArrayHash::GoNext() {
    if (IsTabEnded()) {
        return false;
    }
    for (++currPos; currPos < tabSize; ++currPos) {
        if (pRecs[currPos] != pMark) {
            return true;
        }
    }
    return false;
}

int TArrayHash::GetNextPos(int pos) {
    return (pos + hashStep) % tabSize;
}
