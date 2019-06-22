#include "TScanTable.h"

PTDatValue TScanTable::FindRecord(TKey k) {
    int i;
    SetRetCode(TabOK);
    for (i = 0; i < DataCount; i++)
        if (pRecs[i]->Key == k) break;
    Efficiency = i + 1;
    if (i < DataCount) {
        CurrPos = i;
        return pRecs[i]->pValue;
    }
    SetRetCode(TabNoRec); // if did not find
    return nullptr;
}

void TScanTable::InsRecord(TKey k, PTDatValue pVal) {
    // We mustn't check double records, because when we are going to use scan tables,
    // it is supposed that we use small quantity of records and want to get rid of
    // searching for double records (for max efficiency).
    if (!IsFull()) {
        pRecs[DataCount] = new TTabRecord(k, pVal);
        //pRecs[DataCount]->Key = k;
        //pRecs[DataCount]->pValue = pVal;
        DataCount++;
        Efficiency++; // not sure
        SetRetCode(TabOK);
    }
    else {
        SetRetCode(TabFull);
    }
}

void TScanTable::DelRecord(TKey k) {
    if (!IsEmpty()) {
        PTDatValue search = FindRecord(k);
        if (search != nullptr) {
            PTTabRecord tmp = pRecs[CurrPos];
            pRecs[CurrPos] = pRecs[DataCount - 1]; // move the last record on the free place
            delete tmp;
            DataCount--;
            SetRetCode(TabOK);
        }
        else
            SetRetCode(TabNoRec);
    }
    else
        SetRetCode(TabEmpty);
}