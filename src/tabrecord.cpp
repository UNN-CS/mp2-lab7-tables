#include "tabrecord.h"

TTabRecord::TTabRecord(TKey k, PTDatValue pVal) {
    key = k;
    pValue = pVal;
}

PTDatValue TTabRecord::GetCopy() const {
    if (pValue == nullptr) {
        return new TTabRecord(key, nullptr);
    } else {
        return new TTabRecord(key, pValue->GetCopy());
    }
}

TTabRecord & TTabRecord::operator=(const TTabRecord &tr) {
    if (this != &tr) {
        delete tr.pValue;
        key = tr.key;
    }

    return *this;
}

bool TTabRecord::operator==(const TTabRecord &tr) const {
    return key == tr.key;
}

bool TTabRecord::operator<(const TTabRecord &tr) const {
    return key < tr.key;
}

bool TTabRecord::operator>(const TTabRecord &tr) const {
    return key > tr.key;
}

void TTabRecord::SetKey(TKey k) {
    key = k;
}

TKey TTabRecord::GetKey() {
    return key;
}

void TTabRecord::SetValuePtr(PTDatValue p) {
    delete pValue;
    pValue = p;
}

PTDatValue TTabRecord::GetValuePtr() {
    return pValue;
}
