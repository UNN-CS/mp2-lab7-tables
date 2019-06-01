#include "TArrayHash.h"
#include <string>

TArrayHash::TArrayHash(int size, int Step) : THashTable(), TabSize(size), HashStep(Step)
{
    pRecs = new PTTabRecord[TabSize];
    for (int i = 0; i < TabSize; ++i)
        pRecs[i] = nullptr;
    FreePos = CurrPos = 0;
    pMark = new TTabRecord(string(""), nullptr);
}
TArrayHash::~TArrayHash()
{
    for (int i = 0; i < TabSize; i++)
    {
        if ((pRecs[i] != nullptr) && (pRecs[i] != pMark))
            delete pRecs[i];
    }

    delete[] pRecs;
    delete pMark;
}

int TArrayHash::IsFull() const
{
    return DataCount == TabSize;
}

TKey TArrayHash::GetKey() const
{
    if ((CurrPos < 0) || IsTabEnded())
        return string("");
    else
        return pRecs[CurrPos]->Key;
}

PTDatValue TArrayHash::GetValuePTR() const
{
    if ((CurrPos < 0) || IsTabEnded())
        return nullptr;
    else
        return pRecs[CurrPos]->pValue;
}

PTDatValue TArrayHash::FindRecord(TKey k)
{
    PTDatValue pValue = nullptr;
    FreePos = -1;
    CurrPos = HashFunc(k) % TabSize;
    for (int i = 0; i < TabSize; i++)
    {
        Efficiency++;
        if (pRecs[CurrPos] == nullptr)
            break;
        else if (pRecs[CurrPos] == pMark)
        {
            if (FreePos == -1)
                FreePos = CurrPos;
        }
        else if (pRecs[CurrPos]->Key == k)
        {
            pValue = pRecs[CurrPos]->pValue;
            break;
        }
        //collison
        CurrPos = GetNextPos(CurrPos);
    }
    if (pValue == nullptr)
        SetRetCode(TabNoRec);
    else
        SetRetCode(TabOK);
    return pValue;
}

void TArrayHash::InsRecord(TKey k, PTDatValue pVal)
{
    FreePos = -1;
    CurrPos = HashFunc(k) % TabSize;
    if (IsFull())
        throw "ArrayHash table is full";
    for (int i = 0; i < TabSize; i++)
    {
        Efficiency++;
        if (pRecs[CurrPos] == pMark)
        {
            if (FreePos == -1)
                FreePos = CurrPos;
        }
        if ((pRecs[CurrPos] == nullptr) && (FreePos < 0))
        {
            pRecs[CurrPos] = new TTabRecord(k, pVal);
            DataCount++;
            SetRetCode(TabOK);
            break;
        }
        else if ((pRecs[CurrPos] == nullptr) && (FreePos > -1))
        {
            pRecs[FreePos] = new TTabRecord(k, pVal);
            DataCount++;
            SetRetCode(TabOK);
            break;
        }
        if (pRecs[CurrPos]->GetKey() == k)
        {
            SetRetCode(TabRecDbl);
            break;
        }
        //collision
        CurrPos = GetNextPos(CurrPos);
    }
}

void TArrayHash::DelRecord(TKey k)
{
    PTDatValue temp = FindRecord(k);
    if (temp != nullptr)
    {
        pRecs[CurrPos] = pMark;
        SetRetCode(TabOK);
        DataCount--;
        Efficiency++;
    }
}

int TArrayHash::Reset()
{
    return CurrPos = 0;
}

int TArrayHash::IsTabEnded() const
{
    return CurrPos >= DataCount;
}

int TArrayHash::GoNext()
{
    if (!IsTabEnded())
    {
        while (++CurrPos < TabSize)
            if ((pRecs[CurrPos] != nullptr) && (pRecs[CurrPos] != pMark))
                break;
    }
    return IsTabEnded();
}