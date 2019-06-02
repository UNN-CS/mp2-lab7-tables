#include "ttabrecord.h"

TDatValue * TTabRecord::GetCopy()
{
    TDatValue *tmp = new TTabRecord(Key, pValue);
    return tmp;
}

TTabRecord & TTabRecord::operator = (TTabRecord &tr)
{
    Key = tr.Key;
    pValue = tr.pValue;
    return *this;
}
