#include "TArrayTable.h"

TArrayTable::TArrayTable(int size)
{
	TabSize = size;
	DataCount = CurrPos = 0;
	pRecs = new PTRecord[size];
	for (int i = 0; i < size; ++i)
	{
		pRecs[i] = NULL;
	}
}

TArrayTable::~TArrayTable()
{
	for (int i = 0; i < DataCount; ++i) delete pRecs[i];
	delete[] pRecs;
}

// информационные методы
int TArrayTable::IsFull() const
{
	return DataCount >= TabSize;
}

int TArrayTable::GetTabSize() const
{
	return TabSize;
}

// доступ
TKey TArrayTable::GetKey(TDataPos mode) const
{
	int pos = -1;
	if (!IsEmpty())
	{
		switch (mode)
		{
			case FIRST_POS: pos = 0;  break;
			case LAST_POS: pos = DataCount - 1; break;
			case CURRENT_POS: pos = CurrPos;
		}
	}
	return (pos == -1) ? string("") : pRecs[pos]->Key;
}

PTDatValue TArrayTable::GetValuePTR(TDataPos mode) const
{
	int pos = -1;
	if (!IsEmpty())
	{
		switch (mode)
		{
		case FIRST_POS: pos = 0;  break;
		case LAST_POS: pos = DataCount - 1; break;
		case CURRENT_POS: pos = CurrPos;
		}
	}
	return (pos == -1) ? NULL : (pRecs[pos]->pValue);
}