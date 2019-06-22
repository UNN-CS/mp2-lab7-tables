#include "TArrayTable.h"

TArrayTable::TArrayTable(int Size) {
    pRecs = new PTTabRecord[Size];
    for (int i = 0; i < Size; i++) {
        pRecs[i] = nullptr;
    }
    TabSize = Size;
    DataCount = CurrPos = 0;
}

TArrayTable::~TArrayTable() {
    for (int i = 0; i < DataCount; i++)
        delete pRecs[i];
    delete[] pRecs;
}

TKey TArrayTable::GetKey(TDataPos mode)const {
    int pos = -1;
    if (!IsEmpty()) {
        switch (mode) {
            case FIRST_POS: pos = 0; break;
            case LAST_POS: pos = DataCount - 1; break;
            default: pos = CurrPos; break;
        }
    }
    return (pos == -1) ? string("") : pRecs[pos]->Key;
}

PTDatValue TArrayTable::GetValuePTR(TDataPos mode)const {
    int pos = -1;
    if (!IsEmpty()) {
        switch (mode) {
            case FIRST_POS: pos = 0; break;
            case LAST_POS: pos = DataCount - 1; break;
            default: pos = CurrPos; break;
        }
    }
    return (pos == -1) ? nullptr : pRecs[pos]->pValue;
}

int TArrayTable::Reset() {
    CurrPos = 0;
    return IsTabEnded();
}

int TArrayTable::GoNext() {
    if (!IsTabEnded())
        CurrPos++;
    return IsTabEnded();
}

int TArrayTable::SetCurrentPos(int pos) {
    CurrPos = ((pos > -1) && (pos < DataCount) ? pos : 0);
    return IsTabEnded();
}