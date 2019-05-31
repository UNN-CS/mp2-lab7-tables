#include "TTabRecord.h"

TDatValue* TRecord::GetCopy()
{
	TDatValue * tmp = new TRecord(Key, pValue);
	return tmp;
}