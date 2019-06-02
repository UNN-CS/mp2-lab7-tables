#include "TArrayTable.h"

TArrayTable::TArrayTable(int size): TTable(), TabSize(size)
{
    pRecs = new PTTabRecord[size];
    for (int i = 0; i < size; ++i)
        pRecs[i] = nullptr;
    TabSize = size;
    DataCount = CurrPos = 0;
}

TArrayTable::~TArrayTable()
{
    for (int i = 0; i < DataCount; ++i)
        delete pRecs[i];
    delete[] pRecs;
}

int TArrayTable::IsFull ( ) const
{
    return DataCount >= TabSize;
}

int TArrayTable::GetTabSize( ) const
{
    return TabSize;
}

TKey TArrayTable::GetKey (void) const
{
    if (IsEmpty())
        throw ("tab is empty");
    return pRecs[CurrPos]->GetKey();
}

PTDatValue TArrayTable::GetValuePTR() const
{
    int pos = -1;
    if (!IsEmpty())
        pos = CurrPos;
    if (pos == -1)
        return NULL;
    else
        return pRecs[pos]->pValue;
}

TKey TArrayTable::GetKey(TDataPos mode) const
{
    int pos = -1;
    if (!IsEmpty())
    {
        switch (mode)
        {
        case FIRST_POS:
            pos = 0;
            break;
        case LAST_POS:
            pos = DataCount - 1;
            break;
        default:
            pos = CurrPos;
            break;
        }
    }
    if (pos == -1)
        return "";
    else
        return pRecs[pos]->Key;
}

PTDatValue TArrayTable::GetValuePTR(TDataPos mode) const
{
    int pos = -1;
    if (!IsEmpty())
    {
        switch (mode)
        {
        case FIRST_POS:
            pos = 0;
            break;
        case LAST_POS:
            pos = DataCount - 1;
            break;
        default:
            pos = CurrPos;
            break;
        }
    }

    if (pos == -1)
        return NULL;
    else
        return pRecs[pos]->pValue;
}

int TArrayTable::Reset()
{
    CurrPos = 0;
    return IsTabEnded();
}

int TArrayTable::IsTabEnded (void) const
{
    return CurrPos >= DataCount;
}

int TArrayTable::GoNext()
{
   if (!IsTabEnded())
        CurrPos++;
    else
        SetRetCode(TabFull);
    return GetRetCode();
}

int TArrayTable::SetCurrentPos(int pos)
{
    if ((pos > -1) && (pos < DataCount))
        CurrPos = pos;
    else
        pos = 0;
    return IsTabEnded();
}

int TArrayTable::GetCurrentPos (void) const
{
    return CurrPos;
}

