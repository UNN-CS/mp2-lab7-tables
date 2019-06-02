#include "ttabrecord.h"

TDatValue* TTabRecord::GetCopy() {
    TDatValue* tmp = new TTabRecord(Key, pValue);
    return tmp;
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

PTDatValue TTabRecord::GetValuePTR() {
    return pValue;
}

bool TTabRecord::operator==(const TTabRecord& tr) {
    return Key == tr.Key;
}

bool TTabRecord::operator<(const TTabRecord& tr) {
    return Key < tr.Key;
}

bool TTabRecord::operator>(const TTabRecord& tr) {
    return Key > tr.Key;
}

TTabRecord& TTabRecord::operator=(TTabRecord& tr) {
    Key = tr.Key;
    pValue = tr.pValue->GetCopy();
    return *this;
}
