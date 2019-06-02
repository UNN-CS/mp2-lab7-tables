#include "scantab.h"

PTDatValue TScanTable::FindRecord(TKey k)
{
    int i;
    SetRetCode(TabOK);
    for (i = 0; i < DataCount; i++)
        if (pRecs[i]->Key == k) break;
    Efficiency = i + 1;
    if (i < DataCount)
    {
        CurrPos = i;
        return pRecs[i]->pValue;
    }
    SetRetCode(TabNoRec);
    return nullptr;
}

void TScanTable::InsRecord(TKey k, PTDatValue pVal)
{
    SetRetCode(TabOK);
    if (IsFull())
        SetRetCode(TabFull);
    else if (!FindRecord(k))
    {
        PTTabRecord tmp = new TTabRecord(k, pVal);
        pRecs[DataCount] = tmp;
        DataCount++;
        Efficiency++;
    }
    else SetRetCode(TabRecDbl);
}

void TScanTable::DelRecord(TKey k)
{
    SetRetCode(TabNoRec);
    if (IsEmpty())
        SetRetCode(TabEmpty);
    else
    {
        int i = 0, j = 0;
        for (i = 0; i < DataCount; i++)
        {
            if (pRecs[i]->Key == k)
            {
                delete pRecs[i];
                for (j = i + 1; j < DataCount; j++)
                    pRecs[j - 1] = pRecs[j];
                DataCount--;
                SetRetCode(TabOK);
                break;
            }
        }
        Efficiency = i + j + 1;        
    }
}
