#include "TArrayTable.h"
#include <string>

TArrayTable::TArrayTable(int Size) {
	pRecs = new PTTabRecord[Size];
	for (int i = 0; i < Size; ++i) pRecs[i] = nullptr;
	TabSize = Size; DataCount = CurrPos = 0;
}

TArrayTable::~TArrayTable() {
	delete[] pRecs;
}

int TArrayTable::IsFull() const {
	return DataCount >= TabSize;
}

int TArrayTable::GetTabSize() const {
	return TabSize;
}

TKey TArrayTable::GetKey(void) const {
    return GetKey(CURRENT_POS);
}

PTDatValue TArrayTable::GetValuePTR() const{
	return GetValuePTR(CURRENT_POS);
}

TKey TArrayTable::GetKey(TDataPos mode) const {
	int pos = -1;
	if (!IsEmpty()) {
		switch (mode) {
		case FIRST_POS: pos = 0; break;
		case LAST_POS: pos = DataCount - 1; break;
		default: pos = CurrPos;
		}
	}
	return (pos == -1) ? std::string("") : pRecs[pos]->Key;
}

PTDatValue TArrayTable::GetValuePTR(TDataPos mode) const {
	int pos = -1;
	if (!IsEmpty()) {
		switch (mode) {
		case FIRST_POS: pos = 0; break;
		case LAST_POS: pos = DataCount - 1; break;
		default: pos = CurrPos;
		}
	}
	return (pos == -1) ? nullptr : pRecs[pos]->pValue;
}

int TArrayTable::Reset() {
	CurrPos = 0;
	return IsTabEnded();
}

int TArrayTable::IsTabEnded() const {
	return CurrPos >= DataCount;
}

int TArrayTable::GoNext() {
	if (!IsTabEnded()) CurrPos++;
	return IsTabEnded();
}

int TArrayTable::SetCurrentPos(int pos) {
	CurrPos = ((pos > -1) && (pos < DataCount)) ? pos : 0;
	return IsTabEnded();
}

int TArrayTable::GetCurrentPos(void) const {
	return CurrPos;
}