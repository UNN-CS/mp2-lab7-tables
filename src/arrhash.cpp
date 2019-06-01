#include "arrhash.h"

TArrayHash::TArrayHash(int Size, int Step) : THashTable()
{
    pRecs = new PTTabRecord[Size];
    TabSize = Size;
    HashStep = Step;
    for (int i = 0; i < TabSize; i++)
        pRecs[i] = nullptr;
    string s = "";
    pMark = new TTabRecord(s, nullptr);
}

TArrayHash::~TArrayHash()
{
    for (int i = 0; i < TabSize; i++)
        if ((pRecs[i] != nullptr) && (pRecs[i] != pMark))
            delete pRecs[i];
    delete[] pRecs;
    delete pMark;
}

PTDatValue TArrayHash::FindRecord(TKey k)
{
    PTDatValue pValue = nullptr;
    FreePos = -1;
    Efficiency = 0;
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
    if (DataCount == TabSize)
        SetRetCode(TabFull);
    else
    {
        Efficiency = 0;
        FreePos = -1;
        CurrPos = HashFunc(k) % TabSize;

        for (int i = 0; i < TabSize; i++)
        {
            Efficiency++;

            if (pRecs[CurrPos] == pMark)
            {
                pRecs[CurrPos] = new TTabRecord(k, pVal);
                DataCount++;
                if (FreePos == CurrPos)
                    FreePos = -1;
                break;
            }
            else if (pRecs[CurrPos] == nullptr)
            {
                if (FreePos < 0)
                {
                    pRecs[CurrPos] = new TTabRecord(k, pVal);
                    DataCount++;
                    break;
                }
                else if (FreePos > -1)
                {
                    pRecs[FreePos]->Key = k;
                    pRecs[FreePos]->pValue = pVal;
                    DataCount++;
                    break;
                }
            }
            else if (pRecs[CurrPos]->Key == k)
            {
                SetRetCode(TabRecDbl);
                break;
            }
            CurrPos = GetNextPos(CurrPos);
        }
    }
}

void TArrayHash::DelRecord(TKey k)
{
    PTDatValue tmp = FindRecord(k);
    if (tmp == nullptr) 
        SetRetCode(TabNoRec);
    else 
    {
        SetRetCode(TabOK);
        delete pRecs[CurrPos];
        pRecs[CurrPos] = pMark;
        DataCount--;
    }
}

int TArrayHash::Reset(void)
{
    for (CurrPos = 0; CurrPos < TabSize; ++CurrPos)
    {
        if ((pRecs[CurrPos] != nullptr) && (pRecs[CurrPos] != pMark))
            break;
    }
    return IsTabEnded();
}

int TArrayHash::IsTabEnded(void) const
{
    return CurrPos >= TabSize;
}

int TArrayHash::GoNext(void)
{
    if (!IsTabEnded())
    {
        while (++CurrPos < TabSize)
            if ((pRecs[CurrPos] != nullptr) && (pRecs[CurrPos] != pMark))
                break;
    }
    return IsTabEnded();
}

int TArrayHash::IsFull() const
{
    return DataCount >= TabSize;
}

TKey TArrayHash::GetKey(void) const
{
    return (CurrPos < 0 || CurrPos >= TabSize) ? "" : pRecs[CurrPos]->Key;
}

PTDatValue TArrayHash::GetValuePtr(void) const {
    return (CurrPos < 0 || CurrPos >= TabSize) ? nullptr : pRecs[CurrPos]->pValue;
}




