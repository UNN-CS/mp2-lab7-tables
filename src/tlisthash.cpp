#include "tlisthash.hpp"
#include "ttabrecord.hpp"

TListHash::TListHash(int Size): THashTable(), TabSize(Size)
{
    pList = new PTDatList[Size];

    for (int i = 0; i < TabSize; ++i)
        pList[i] = new TDatList();

    CurrList = 0;
}

TListHash::~TListHash()
{
    for (int i = 0; i < TabSize; ++i)
        delete pList[i];

    delete[] pList;
}

int TListHash::IsFull ( ) const
{
    return 0;
}

TKey TListHash::GetKey (void) const
{
    if (CurrList >= TabSize)
        throw std::runtime_error("current position out of range");

    return ((PTTabRecord)pList[CurrList]->GetDatValue())->GetKey();
}

PTDatValue TListHash::GetValuePtr (void) const
{
    if (CurrList >= TabSize)
        throw std::runtime_error("current position out of range");

    return ((PTTabRecord)pList[CurrList]->GetDatValue())->GetValuePTR();
}

PTDatValue TListHash::FindRecord (TKey k)
{
    PTTabRecord p = nullptr;
    int j = HashFunc(k) % TabSize;

    for (pList[j]->Reset(); !pList[j]->IsListEnded(); pList[j]->GoNext())
        if (((PTTabRecord)pList[j]->GetDatValue())->GetKey() == k)
        {
            p = (PTTabRecord)pList[j]->GetDatValue();
            break;
        }

    Efficiency += pList[j]->GetCurrentPos() + 1;

    return p;
}

void TListHash::InsRecord (TKey k, PTDatValue pVal )
{
    int j = HashFunc(k) % TabSize;

    for (pList[j]->Reset(); !pList[j]->IsListEnded(); pList[j]->GoNext())
    {
        if (((PTTabRecord)pList[j]->GetDatValue())->GetKey() == k)
        {
            Efficiency += pList[j]->GetCurrentPos() + 1;
            ((PTTabRecord)pList[j]->GetDatValue())->SetValuePtr(pVal);

            return;
        }
    }

    Efficiency += pList[j]->GetCurrentPos() + 1;
    ++DataCount;

    pList[j]->InsLast(new TTabRecord(k, pVal));
}

void TListHash::DelRecord (TKey k)
{
    int j = HashFunc(k) % TabSize;

    for (pList[j]->Reset(); !pList[j]->IsListEnded(); pList[j]->GoNext())
    {
        if (((PTTabRecord)pList[j]->GetDatValue())->GetKey() == k)
        {
            Efficiency += pList[j]->GetCurrentPos() + 1;
            pList[j]->DelCurrent();

            --DataCount;

            return;
        }
    }
    Efficiency += pList[j]->GetCurrentPos() + 1;
}

int TListHash::Reset (void)
{
    for (CurrList = 0; CurrList < TabSize; ++CurrList)
    {
        if (!pList[CurrList]->IsEmpty())
        {
            pList[CurrList]->Reset();
            break;
        }
    }
    return IsTabEnded();
}

int TListHash::IsTabEnded (void) const
{
    return CurrList == TabSize;
}

int TListHash::GoNext (void)
{
    if (IsTabEnded())
        return IsTabEnded();

    pList[CurrList]->GoNext();

    if (!pList[CurrList]->IsListEnded())
        return IsTabEnded();
    for (++CurrList; CurrList < TabSize; ++CurrList)
    {
        if (!pList[CurrList]->IsEmpty())
        {
            pList[CurrList]->Reset();
            break;
        }
    }
    
    return IsTabEnded();
}
