#include "tscantable.h"

PTDatValue TScanTable::FindRecord(TKey k) {
    SetRetCode(TabOK);
    
    int i;
    for (i = 0; i < DataCount; i++)
        if (pRecs[i]->key == k) break;
    
    Efficiency = i + 1;

    if (DataCount > i) {
        currPos = i;
        return pRecs[i]->pValue;
    }

    SetRetCode(TabNoRec);
    return NULL;
}       /*================================================*/

void TScanTable::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull())
        SetRetCode(TabFull);
    else {
        for (int i = 0; i < DataCount; i++) {
            if (pRecs[i]->GetKey() == k) {
                Efficiency = i + 1;
                pRecs[i]->SetValuePtr(pVal);
                return;
            }
        }

        Efficiency = DataCount;
        pRecs[DataCount++] = new TTabRecord(k, pVal);
    }
}       /*================================================*/

void TScanTable::DelRecord(TKey k) {
    if (IsEmpty())
        SetRetCode(TabEmpty);
    else
    {
        for (int i = 0; i < DataCount; i++) {
            if (pRecs[i]->GetKey() == k) {
                delete pRecs[i];

                for (int j = i + 1; j < DataCount; j++)
                    pRecs[j - 1] = pRecs[j];
                
                DataCount--;
            }
        }

        Efficiency += DataCount;
    }
}       /*================================================*/
