#include "ttabrecord.h"

TTabRecord::TTabRecord(TKey k, PTDatValue pVal) :
            key(k), pValue(pVal) {}

void TTabRecord::SetKey(TKey k) {
    key = k; 
}       /*================================================*/

TKey TTabRecord::GetKey() {
    return key;
}       /*================================================*/

void TTabRecord::SetValuePtr(PTDatValue p) {
    pValue = p;
}       /*================================================*/

PTDatValue  TTabRecord::GetValuePTR() {
    return pValue;
}       /*================================================*/

TDatValue* TTabRecord::GetCopy() {
    return new TTabRecord(key, pValue);
}       /*================================================*/

TTabRecord& TTabRecord::operator=(TTabRecord &tr) {
    if (&tr == this)
        return *this;

    key = tr.key;

    delete pValue;
    pValue = tr.pValue;

    return *this;
}       /*================================================*/

bool TTabRecord::operator==(const TTabRecord &tr) {
    return key == tr.key;
}       /*================================================*/

bool TTabRecord::operator<(const TTabRecord &tr) {
    return key < tr.key;
}       /*================================================*/

bool TTabRecord::operator>(const TTabRecord &tr) {
    return key > tr.key;
}
