// TScanTable.cpp
#include "TScanTable.h"

PTDatValue TScanTable::FindRecord(TKey k) {
    for (int i = 0; i < DataCount; ++i)
        if (pRecs[i]->GetKey() == k)
        {
            Efficiency += i + 1;
            return pRecs[i];
        }
    Efficiency += DataCount;
    return nullptr;
}

void TScanTable::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull())
        throw "insert in full table";
    for (int i = 0; i < DataCount; ++i)
        if (pRecs[i]->GetKey() == k)
        {
            Efficiency += i + 1;
            pRecs[i]->SetValuePtr(pVal);
            return;
        }
    Efficiency += DataCount;
    pRecs[DataCount++] = new TTabRecord(k, pVal);
}

void TScanTable::DelRecord(TKey k) {
    int i;
    for (i = 0; i < DataCount; ++i) 
        if (pRecs[i]->GetKey() == k) {
            delete pRecs[i];
            for (int j = i + 1; j < DataCount; ++j)
                pRecs[j - 1] = pRecs[j];
            DataCount--;
            Efficiency += i + 1;
        }
    Efficiency += DataCount;
}
