#include "TDatLink.h"

void TDatLink::SetDatValue(PTDatValue pDat)
{
	pValue = pDat;
}

PTDatValue TDatLink::GetDatValue()
{
	return pValue;
}

PTDatLink TDatLink::GetNextDatLink()
{
	return PTDatLink(pNext);
}