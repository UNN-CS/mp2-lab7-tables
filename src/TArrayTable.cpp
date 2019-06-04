#include "TArrayTable.h"

TArrayTable::TArrayTable(int Size) : TTable(), TabSize(Size)
{
	CurrPos = 0;
	pRecs = new PTTabRecord[Size];
	for (int i = 0; i < Size; ++i)
		pRecs[i] = nullptr;
}

TArrayTable::~TArrayTable()
{
	for (int i = 0; i < DataCount; ++i)
		delete pRecs[i];
	delete[] pRecs;
}

int TArrayTable::IsFull() const
{
	return DataCount == TabSize;
}

int TArrayTable::GetTabSize() const
{
	return TabSize;
}

TKey TArrayTable::GetKey(void) const
{
	if (IsEmpty())
		throw ("Empty table");
	return pRecs[CurrPos]->GetKey();
}

PTDatValue TArrayTable::GetValuePTR(void) const
{
	if (IsEmpty())
		throw ("Empty table");
	return pRecs[CurrPos]->GetValuePTR();
}

TKey TArrayTable::GetKey(TDataPos mode) const
{
	if (IsEmpty())
		throw ("Empty table");
	switch (mode)
	{
	case TDataPos::FIRST_POS:
		return pRecs[0]->GetKey();
		break;
	case TDataPos::CURRENT_POS:
		return pRecs[CurrPos]->GetKey();
		break;
	case TDataPos::LAST_POS:
		return pRecs[DataCount - 1]->GetKey();
		break;
	default:
		throw ("Wrong mode");
	}
}

PTDatValue TArrayTable::GetValuePTR(TDataPos mode) const
{
	if (IsEmpty())
		throw ("Empty table");
	switch (mode)
	{
	case TDataPos::FIRST_POS:
		return pRecs[0]->GetValuePTR();
		break;
	case TDataPos::CURRENT_POS:
		return pRecs[CurrPos]->GetValuePTR();
		break;
	case TDataPos::LAST_POS:
		return pRecs[DataCount - 1]->GetValuePTR();
		break;
	default:
		throw ("Wrong mode");
	}
}

int TArrayTable::Reset(void)
{
	CurrPos = 0;
	return 0;
}

int TArrayTable::IsTabEnded(void) const
{
	return CurrPos == DataCount;
}

int TArrayTable::GoNext(void)
{
	CurrPos++;
	return IsTabEnded();
}

int TArrayTable::SetCurrentPos(int pos)
{
	if ((pos < 0) || (pos >= DataCount))
		throw ("Position error");
	CurrPos = pos;
	return 0;
}

int TArrayTable::GetCurrentPos(void) const
{
	return CurrPos;
}