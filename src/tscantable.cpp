#include "tscantable.h"

PTDatValue TScanTable::FindRecord(TKey k) {
    int i;
    for (i = 0; i < DataCount; ++i) {
        if (pRecs[i]->Key == k)
            break;
    }
    Efficiency += i + 1;
    if (i < DataCount) {
        CurrPos = i;
        return pRecs[i]->pValue;
    }
    return nullptr;
}

void TScanTable::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull())
        throw -1;
    for (int i = 0; i < TabSize; ++i) {
        if (!pRecs[i]) {
            pRecs[i] = new TTabRecord(k, pVal);
            ++DataCount;
            Efficiency += i + 1;
            break;
        }
        if (pRecs[i]->Key == k) {
            pRecs[i]->pValue = pVal;
            break;
        }
    }
}

void TScanTable::DelRecord(TKey k) {
    if (IsEmpty())
        return;
    for (int i = 0; i < DataCount; ++i) {
        ++Efficiency;
        if (!pRecs[i])
            continue;
        if (pRecs[i]->Key == k) {
            delete pRecs[i];
            for (int j = i + 1; j < DataCount; ++j)
                pRecs[j - 1] = pRecs[j];
            --DataCount;
            break;
        }
    }
}
