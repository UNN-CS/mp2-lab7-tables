#include "TTabRecord.h"

TTabRecord::TTabRecord(TKey k , PTDatValue pVal): Key(k), pValue(pVal) {}

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

TDatValue *TTabRecord::GetCopy()
{
	return new TTabRecord(Key, pValue);
}

TTabRecord &TTabRecord::operator=(TTabRecord &tr)
{
	Key = tr.Key;
	pValue = tr.pValue->GetCopy();
	return *this;
}

int TTabRecord::operator==(const TTabRecord &tr)
{
	return Key == tr.Key;
}

int TTabRecord::operator<(const TTabRecord &tr)
{
	return Key < tr.Key;
}

int TTabRecord::operator>(const TTabRecord &tr)
{
	return Key > tr.Key;
}