#include "TDatLink.h"

TDatLink::TDatLink(PTDatValue pVal, PTRootLink pN): TRootLink(pN), pValue(pVal) {}

void TDatLink::SetDatValue(PTDatValue pVal)
{
	pValue = pVal;
}

PTDatValue TDatLink::GetDatValue()
{
	return pValue;
}

PTDatLink TDatLink::GetNextDatLink()
{
	return (PTDatLink)pNext;
}