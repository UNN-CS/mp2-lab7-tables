#include "TScanTable.h"

PTDatValue TScanTable::FindRecord (TKey k)
{
    for (int i = 0; i < DataCount; ++i)
        if (pRecs[i]->GetKey() == k)
        {
            Efficiency += i + 1;
            return pRecs[i];
        }
    Efficiency += DataCount;
    return nullptr;
}

void TScanTable::InsRecord (TKey k, PTDatValue pVal )
{
    if (IsFull())
        throw ("table is full");
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

void TScanTable::DelRecord (TKey k)
{
    for (int i = 0; i < DataCount; ++i)
        if (pRecs[i]->GetKey() == k)
        {
            Efficiency += i + 1;
            delete pRecs[i];
            for (int j = i + 1; j < DataCount; ++j)
                pRecs[j - 1] = pRecs[j];
            --DataCount;
        }
    Efficiency += DataCount;
}
