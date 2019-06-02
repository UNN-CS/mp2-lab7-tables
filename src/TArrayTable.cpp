#include "TArrayTable.h"

TArrayTable::TArrayTable(int Size)
{
	if (Size <= 0 || Size > TabMaxSize)
		throw -1;
	TabSize = Size;
	pRecs = new PTTabRecord[TabSize];
	for (int i = 0;i < TabSize;i++)
		pRecs[i] = nullptr;
	DataCount = CurrPos = 0;
}

TArrayTable::~TArrayTable()
{
	for (int i = 0;i < TabSize;i++)
		delete pRecs[i];
	delete [] pRecs;
}

int TArrayTable::IsFull() const
{
	return DataCount >= TabSize;
}

int TArrayTable::GetTabSize() const
{
	return DataCount;
}

TKey TArrayTable::GetKey() const
{
	return pRecs[CurrPos]->Key;
}

PTDatValue TArrayTable::GetValuePTR() const
{
	return pRecs[CurrPos]->pValue;
}

TKey TArrayTable::GetKey(TDataPos mode) const
{
	if (!IsEmpty())
	{
		int t;
		switch (mode)
		{
		case FIRST_POS:
			t = 0;
			break;
		case CURRENT_POS:
			t = CurrPos;
			break;
		case LAST_POS:
			t = DataCount - 1;
			break;
		default:
			throw -1;
			break;
		}
		return pRecs[t]->Key;
	}
}

PTDatValue TArrayTable::GetValuePTR(TDataPos mode) const
{
	if (!IsEmpty())
	{
		int t;
		switch (mode)
		{
		case FIRST_POS:
			t = 0;
			break;
		case CURRENT_POS:
			t = CurrPos;
			break;
		case LAST_POS:
			t = DataCount - 1;
			break;
		default:
			throw -1;
			break;
		}
		return pRecs[t]->pValue;
	}
}

int TArrayTable::Reset()
{
	CurrPos = 0;
	return DataOK;
}

int TArrayTable::IsTabEnded() const
{
	return CurrPos >= DataCount;
}

int TArrayTable::GoNext()
{
	if (!IsTabEnded())
		CurrPos++;
	return DataOK;
}

int TArrayTable::SetCurrentPos(int pos)
{
	if (pos < 0 || pos >= TabMaxSize)
		throw -1;
	CurrPos = pos;
}

int TArrayTable::GetCurrentPos() const
{
	if(!IsEmpty())
		return CurrPos;
}