#include "TScanTable.h"

PTDatValue TScanTable::FindRecord(TKey k)
{
	int i;
	for (i = 0;i < DataCount;i++)
		if (pRecs[i]->GetKey() == k)
			break;
	Efficiency += i + 1;
	if (i < DataCount) {
		CurrPos = i;
		return pRecs[i]->pValue;
	}
	return nullptr;
}

void TScanTable::InsRecord(TKey k, PTDatValue pVal)
{
	if (!IsFull())
	{
		int i;
		for (i = 0;i < DataCount;i++)
			if (pRecs[i]->GetKey() == k)
			{
				Efficiency += i + 1;
				pRecs[i]->SetValuePtr(pVal);
				return;
			}
		pRecs[DataCount++] = new TTabRecord(k, pVal);
		Efficiency ++;
	}
}

void TScanTable::DelRecord(TKey k)
{
	if (!IsEmpty())
	{
		int i;
		for (i = 0;i < DataCount;i++)
		{
			if (pRecs[i]->GetKey() == k)
			{
				pRecs[i]->SetKey(pRecs[DataCount - 1]->GetKey());
				pRecs[i]->SetValuePtr(pRecs[DataCount - 1]->GetValuePTR());
				delete pRecs[DataCount - 1];
				pRecs[DataCount - 1] = nullptr;
				DataCount--;
				Efficiency += i + 1;
				return;
			}
		}
		Efficiency += i + 1;
	}
}