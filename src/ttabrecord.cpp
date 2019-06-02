#include "ttabrecord.h"
#include <iostream>

TTabRecord::TTabRecord(TKey k, PTDatValue pVal) {
    Key = k;
    pValue = pVal;
}

void TTabRecord::SetKey(TKey k) {
    Key = k;
}

TKey TTabRecord::GetKey() {
    return Key;
}

void TTabRecord::SetValuePtr(PTDatValue p) {
    pValue = p;
}

PTDatValue TTabRecord::GetValuePtr() {
    return pValue;
}

TDatValue * TTabRecord::GetCopy() {
    TDatValue * tmp = new TTabRecord(Key, pValue);
    return tmp;
}

TTabRecord& TTabRecord::operator=(TTabRecord &tr) {
    Key = tr.Key;
    pValue = tr.pValue;
    return *this;
}

int TTabRecord::operator==(const TTabRecord& tr) {
    return Key == tr.Key;
}

int TTabRecord::operator>(const TTabRecord& tr) {
    return Key > tr.Key;
}

int TTabRecord::operator<(const TTabRecord& tr) {
    return Key < tr.Key;
}

