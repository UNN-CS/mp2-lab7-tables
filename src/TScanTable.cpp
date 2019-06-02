#include "TScanTable.h"

PTDatValue TScanTable::FindRecord(TKey k)
{
	int i;
	SetRetCode(TabOK);
	for (i = 0; i<DataCount; i++)
		if (pRecs[i]->Key == k)
			break;
	Efficiency = i + 1;
	if (i<DataCount)
	{
		CurrPos = i;
		return pRecs[i]->pValue;
	}
	SetRetCode(TabNoRec);
	return nullptr;
}

void TScanTable::DelRecord(TKey k)
{
	if (!IsEmpty())
	{
		if (FindRecord(k) == nullptr)
			SetRetCode(TabNoRec);
		else
		{
			pRecs[CurrPos] = pRecs[DataCount - 1];
			pRecs[DataCount - 1] = nullptr;
			DataCount--;
			SetRetCode(TabOK);
		}
	}
	else
		SetRetCode(TabEmpty);
}

void TScanTable::InsRecord(TKey k, PTDatValue pVal)
{
	if (!IsFull())
	{
		PTDatValue tmp = FindRecord(k);
		if (tmp == nullptr)
		{
			pRecs[DataCount] = new TTabRecord(k, pVal);
			DataCount++;
			SetRetCode(TabOK);
		}
		else
			SetRetCode(TabRecDbl);
	}
	else SetRetCode(TabFull);
} 
