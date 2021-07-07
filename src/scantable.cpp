#include "scantable.h"

#include "tabrecord.h"

TScanTable::TScanTable(int size) : TArrayTable(size) {}

PTDatValue TScanTable::FindRecord(TKey k) {
    for (Reset(); !IsTabEnded(); GoNext()) {
        ++efficiency;
        if (GetKey() == k) {
            return GetValuePtr();
        }
    }

    return nullptr;
}

void TScanTable::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull()) {
        return;
    }

    if (FindRecord(k) != nullptr) {
        return;
    }

    currPos = dataCount++;

    pRecs[currPos] = new TTabRecord(k, pVal);
}

void TScanTable::DelRecord(TKey k) {
    if (FindRecord(k) != nullptr) {
        delete pRecs[currPos];

        for (int i = currPos + 1; i < dataCount; ++i) {
            pRecs[i - 1] = pRecs[i];
            ++efficiency;
        }

        --dataCount;
    }

    Reset();
}
