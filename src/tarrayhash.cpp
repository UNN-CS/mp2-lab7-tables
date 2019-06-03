#include "tarrayhash.hpp"

TArrayHash::TArrayHash(int Size, int Step): THashTable(), TabSize(Size), HashStep(Step)
{
    pRecs = new PTTabRecord[TabSize];

    for (int i = 0; i < TabSize; ++i)
        pRecs[i] = nullptr;

    FreePos = CurrPos = 0;
}

TArrayHash::~TArrayHash()
{
    delete[] pRecs;
}

int TArrayHash::IsFull ( ) const
{
    return DataCount == TabSize;
}

TKey TArrayHash::GetKey (void) const
{
    if (CurrPos >= TabSize)
        throw std::runtime_error("current position out of range");

    return pRecs[CurrPos]->GetKey();
}

PTDatValue TArrayHash::GetValuePtr (void) const
{
    if (CurrPos >= TabSize)
        throw std::runtime_error("current position out of range");

    return pRecs[CurrPos]->GetValuePTR();
}

PTDatValue TArrayHash::FindRecord (TKey k)
{
    PTTabRecord p = nullptr;
    int eff = DataCount;
    int j = HashFunc(k) % TabSize;

    for (int i = 0; i < TabSize; ++i)
    {
        if (pRecs[j] == nullptr)
        {
            eff = i + 1;
            break;
        }
        if (pRecs[j]->GetKey() == k)
        {
            eff = i + 1;
            p = pRecs[j];
            break;
        }
        j = GetNextPos(j);
    }

    Efficiency += eff;

    return p;
}

void TArrayHash::InsRecord (TKey k, PTDatValue pVal )
{
    int pre = -1;
    int j = HashFunc(k) % TabSize;

    for (int i = 0; i < TabSize; ++i)
    {
        if (pRecs[j] == nullptr)
        {
            Efficiency += i + 1;
            ++DataCount;
            if (pre > -1)
            {
                pRecs[pre]->SetKey(k);
                pRecs[pre]->SetValuePtr(pVal);
                return;
            }
            pRecs[j] = new TTabRecord(k, pVal);
            return;
        }

        if ((pre < 0)&&(pRecs[j]->GetKey() == "")&&(pRecs[j]->GetValuePTR() == nullptr))
            pre = j;
        else if (pRecs[j]->GetKey() == k)
        {
            Efficiency += i + 1;
            pRecs[j]->SetValuePtr(pVal);
            return;
        }

        j = GetNextPos(j);
    }

    if (pre > -1)
    {
        Efficiency += TabSize;
        ++DataCount;
        pRecs[pre]->SetKey(k);
        pRecs[pre]->SetValuePtr(pVal);
        return;
    }

    throw std::runtime_error("insert into full table");
}

void TArrayHash::DelRecord (TKey k)
{
    int j = HashFunc(k) % TabSize;

    for (int i = 0; i < TabSize; ++i)
    {
        if (pRecs[j] == nullptr)
        {
            Efficiency += i + 1;
            return;
        }
        
        if (pRecs[j]->GetKey() == k)
        {
            Efficiency += i + 1;
            pRecs[j]->SetKey("");
            pRecs[j]->SetValuePtr(nullptr);
            --DataCount;
            return;
        }

        j = GetNextPos(j);
    }
    Efficiency += TabSize;
}

int TArrayHash::Reset (void)
{
    for (CurrPos = 0; CurrPos < TabSize; ++CurrPos)
    {
        if ((pRecs[CurrPos] != nullptr) && ((pRecs[CurrPos]->GetKey() != "") || (pRecs[CurrPos]->GetValuePTR() != nullptr)))
            break;
    }
    return IsTabEnded();
}

int TArrayHash::IsTabEnded (void) const
{
    return CurrPos == TabSize;
}

int TArrayHash::GoNext (void)
{
    if (!IsTabEnded())
        while (++CurrPos < TabSize)
        {
            if ((pRecs[CurrPos] != nullptr) && ((pRecs[CurrPos]->GetKey() != "") || (pRecs[CurrPos]->GetValuePTR() != nullptr)))
                break;
        }
        
    return IsTabEnded();
}
