#include "arraytable.h"

#include "tabrecord.h"

TArrayTable::TArrayTable(int size) {
    if (size < 1) {
        throw -1;
    }

    tabSize = size;
    currPos = 0;

    pRecs = new PTTabRecord[size];
}

TArrayTable::~TArrayTable() {}

bool TArrayTable::IsFull() const {
    return dataCount >= tabSize;
}

TKey TArrayTable::GetKey() const {
    return GetKey(CURRENT_POS);
}

PTDatValue TArrayTable::GetValuePtr() const {
    return GetValuePtr(CURRENT_POS);
}

TKey TArrayTable::GetKey(TDataPos mode) const {
    if (dataCount <= 0) {
        return "";
    }

    switch (mode) {
      case FIRST_POS:
        return pRecs[0]->GetKey();
        break;
      case LAST_POS:
        return pRecs[dataCount - 1]->GetKey();
        break;
      case CURRENT_POS:
      default:
        return pRecs[currPos]->GetKey();
        break;
    }
}

PTDatValue TArrayTable::GetValuePtr(TDataPos mode) const {
    if (dataCount <= 0) {
        return nullptr;
    }

    switch (mode) {
      case FIRST_POS:
        return pRecs[0]->GetValuePtr();
        break;
      case LAST_POS:
        return pRecs[dataCount - 1]->GetValuePtr();
        break;
      case CURRENT_POS:
      default:
        return pRecs[currPos]->GetValuePtr();
        break;
    }
}

bool TArrayTable::Reset() {
    currPos = 0;
    return IsTabEnded();
}

bool TArrayTable::IsTabEnded() const {
    return currPos >= dataCount;
}

bool TArrayTable::GoNext() {
    if (IsTabEnded()) {
        return false;
    }

    ++currPos;

    return true;
}

int TArrayTable::GetTabSize() const {
    return tabSize;
}

bool TArrayTable::SetCurrentPos(int pos) {
    if (pos < 0 || pos > dataCount) {
        return false;
    }

    currPos = pos;

    return true;
}

int TArrayTable::GetCurrentPos() const {
    return currPos;
}
