#include "TScanTable.h"

PTDatValue TScanTable::FindRecord(TKey tmp)
{
	SetRetCode(TabOK);
	int  i = 0;
	for (i = 0; i < DataCount; ++i)
	{
		if (pRecs[i]->Key == tmp) break;
	}

	Efficiency = i + 1;
	if (i < DataCount)
	{
		CurrPos = i;
		return pRecs[i]->pValue;
	}
	SetRetCode(TabNoRec);
	return NULL;
}

void TScanTable::InsRecord(TKey k, PTDatValue val)
{
	SetRetCode(TabOK);
	PTDatValue tmp = FindRecord(k);
	if (tmp != NULL)
	{
		SetRetCode(TabRecDbl);
		return;
	}
	if (IsFull())
		SetRetCode(TabFull);
	else {
		int i = DataCount;
		pRecs[i] = new TRecord(k, val);
		DataCount++;
	}
}

void TScanTable::DelRecord(TKey k)
{
	PTDatValue tmp = FindRecord(k);
	if (tmp == NULL)
		SetRetCode(TabNoRec);
	else
	{
		SetRetCode(TabOK);
		PTRecord tmp = pRecs[CurrPos];
		pRecs[CurrPos] = pRecs[DataCount - 1];
		delete tmp;
		DataCount--;
	}
}
