#include "ttabrecord.hpp"

void TTabRecord::SetKey(TKey k)
{
    Key = k;
}

TKey TTabRecord::GetKey()
{
    return Key;
}

void TTabRecord::SetValuePtr(PTDatValue p)
{
    pValue = p;
}

PTDatValue TTabRecord::GetValuePTR()
{
    return pValue;
}

TDatValue * TTabRecord::GetCopy()
{
    return new TTabRecord(Key, pValue);
}

TTabRecord & TTabRecord::operator = (TTabRecord &tr)
{
    if (this == &tr)
        return *this;

    Key = tr.Key;
    delete pValue;
    
    pValue = tr.pValue->GetCopy();
    return *this;
}

bool TTabRecord::operator == (const TTabRecord &tr) const
{
    return Key == tr.Key;
}

bool TTabRecord::operator < (const TTabRecord &tr)
{
    return Key < tr.Key;
}

bool TTabRecord::operator > (const TTabRecord &tr)
{
    return Key > tr.Key;
}
