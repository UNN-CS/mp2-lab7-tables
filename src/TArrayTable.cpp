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
		throw std::runtime_error("get when table is empty");
	return pRecs[CurrPos]->GetKey();
}

PTDatValue TArrayTable::GetValuePTR(void) const
{
	if (IsEmpty())
		throw std::runtime_error("get when table is empty");
	return pRecs[CurrPos]->GetValuePTR();
}

TKey TArrayTable::GetKey(TDataPos mode) const
{
	if (IsEmpty())
		throw std::runtime_error("get when table is empty");
	switch (mode)
	{
	case TDataPos::FIRST_POS:
		return pRecs[0]->GetKey();
	case TDataPos::CURRENT_POS:
		return pRecs[CurrPos]->GetKey();
	case TDataPos::LAST_POS:
		return pRecs[DataCount - 1]->GetKey();
	default:
		throw std::runtime_error("invalid mode");
	}
}

PTDatValue TArrayTable::GetValuePTR(TDataPos mode) const
{
	if (IsEmpty())
		throw std::runtime_error("get when table is empty");
	switch (mode)
	{
	case TDataPos::FIRST_POS:
		return pRecs[0]->GetValuePTR();
	case TDataPos::CURRENT_POS:
		return pRecs[CurrPos]->GetValuePTR();
	case TDataPos::LAST_POS:
		return pRecs[DataCount - 1]->GetValuePTR();
	default:
		throw std::runtime_error("invalid mode");
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
	++CurrPos;
	return IsTabEnded();
}

int TArrayTable::SetCurrentPos(int pos)
{
	if ((pos < 0) || (pos >= DataCount))
		throw std::runtime_error("invalid position");
	CurrPos = pos;
	return 0;
}

int TArrayTable::GetCurrentPos(void) const
{
	return CurrPos;
}