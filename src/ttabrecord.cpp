#include "ttabrecord.hpp"

TDatValue *TTabRecord::GetCopy()
{
    return new TTabRecord(Key, pValue);
}

bool TTabRecord::operator==(const TTabRecord &tr) const
{
    return Key == tr.Key;
}

bool TTabRecord::operator<(const TTabRecord &tr)
{
    return Key < tr.Key;
}

bool TTabRecord::operator>(const TTabRecord &tr)
{
    return Key > tr.Key;
}

TTabRecord &TTabRecord::operator=(TTabRecord &tr)
{
    Key = tr.Key;
    pValue = tr.pValue->GetCopy();
    return *this;
}

TKey TTabRecord::GetKey()
{
    return Key;
}

void TTabRecord::SetKey(TKey k)
{
    Key = k;
}
