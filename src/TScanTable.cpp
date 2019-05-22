#include "TScanTable.h"

PTDatValue TScanTable::FindRecord(TKey k) {
	int i;

	for (i = 0; i < DataCount; i++)
		if (pRecs[i]->key == k)
			break;
	Efficiency = i + 1;
	if (i < DataCount) {
		CurrPos = i;
		return pRecs[i]->pValue;
	}
	throw -1;
}

void TScanTable::InsRecord(TKey k, PTDatValue pVal) {
	if (IsFull())
		throw -1;
	pRecs[DataCount++] = new TTabRecord(k, pVal);
}

void TScanTable::DelRecord(TKey k) {
	FindRecord(k);
	pRecs[CurrPos] = pRecs[DataCount - 1];
	pRecs[--DataCount] = nullptr;
}