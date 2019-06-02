#include "TTabRecord.h"

TDatValue * TTabRecord::GetCopy() {
    TDatValue *temp = new TTabRecord(Key, pValue);
    return temp;
}