#include "tscantable.h"

PTDatValue TScanTable::FindRecord(TKey k) {
    int i;
    for(i = 0; i < DataCount; i++)
        if(pRecs[i]->Key == k)
            break;
    Efficiency = i+1;
    if(i < DataCount) {
        CurrPos = i;
        return pRecs[i]->pValue;
    }
    return nullptr;
}

void TScanTable::InsRecord(TKey k, PTDatValue pVal) {
    if(IsFull())
        throw TabFull;
    if(FindRecord(k) != nullptr)
        throw TabRecDbl;
    pRecs[DataCount++] = new TTabRecord(k, pVal);
}

void TScanTable::DelRecord(TKey k) {
    PTDatValue tmp = FindRecord(k);
    if(tmp == nullptr)
        throw TabNoRec;
    pRecs[CurrPos] = pRecs[DataCount-1];
    pRecs[--DataCount] = nullptr;
}
