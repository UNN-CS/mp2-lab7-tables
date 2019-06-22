#include "TTabRecord.h"

TTabRecord::TTabRecord(TKey k, PTDatValue pVal) {
    Key = k;
    pValue = pVal;
}

TTabRecord & TTabRecord::operator= (TTabRecord &tr) {
    Key = tr.Key;
    pValue = tr.pValue;
    return *this;
}

int TTabRecord::operator== (const TTabRecord &tr) {
    return Key == tr.Key;
}

int TTabRecord::operator< (const TTabRecord &tr) {
    return Key > tr.Key; // why inversion: >, but not < ?
}

int TTabRecord::operator> (const TTabRecord &tr) {
    return Key < tr.Key;
}

TDatValue * TTabRecord::GetCopy() {
    TDatValue * temp = new TTabRecord(Key, pValue);
    return temp;
}

void TTabRecord::Print(ostream& os) {
    os << Key << " " << *pValue;
}