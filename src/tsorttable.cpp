#include <iostream>

#include "tsorttable.hpp"
#include "ttabrecord.hpp"

TSortTable::TSortTable(const TScanTable &tab): TScanTable(tab.GetTabSize())
{
    CurrPos = tab.CurrPos;

    for (int i = 0; i < DataCount; ++i)
        pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
    SortMethod = QUIQ_SORT;

    SortData();
}

TSortTable & TSortTable::operator=(const TScanTable &tab)
{
    if (pRecs)
    {
        for (int i = 0; i < DataCount; ++i)
            delete pRecs[i];
        delete[] pRecs;
    }

    TabSize = tab.TabSize;
    DataCount = tab.DataCount;
    CurrPos = tab.CurrPos;

    pRecs = new PTTabRecord[TabSize];

    for (int i = 0; i < DataCount; ++i)
        pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
    SortData();

    return *this;
}

TSortMethod TSortTable::GetSortMethod(void)
{
    return SortMethod;
}

void TSortTable::SetSortMethod (TSortMethod sm)
{
    SortMethod = sm;
}

void TSortTable::SortData (void)
{
    switch (SortMethod)
    {
    case INSERT_SORT:
        InsertSort(pRecs, DataCount);
        return;

    case MERGE_SORT:
        MergeSort(pRecs, DataCount);
        return;

    case QUIQ_SORT:
        QuiqSort(pRecs, DataCount);
        return;

    default:
        throw std::runtime_error("invalid SortMethod");
    }
}

void TSortTable::InsertSort (PTTabRecord *pMem, int DataCount)
{
    Efficiency += DataCount;
    for (int i = 1, j; i < DataCount; ++i)
    {
        PTTabRecord p = pMem[i];
        for (j = i - 1; j >= 0; --j)
            if (p->GetKey() < pMem[j]->GetKey())
            {
                ++Efficiency;
                pMem[j + 1] = pMem[j];
            }
            else
                break;

        pMem[j + 1] = p;
    }
}

void TSortTable::MergeSort (PTTabRecord *pMem, int DataCount)
{
    PTTabRecord* p = new PTTabRecord[DataCount];

    for (int i = 0; i < DataCount; ++i)
        p[i] = pMem[i];

    Efficiency += DataCount;
    MergeSorter(pMem, p, DataCount);

    delete[] p;
}

void TSortTable::MergeSorter (PTTabRecord * &pData,PTTabRecord * &pBuff,int Size)
{
    int n = Size / 2;

    PTTabRecord* p = pBuff + n;
    PTTabRecord* q = pData + n;

    if (Size > 1)
    {
        MergeSorter(pBuff, pData, n);
        MergeSorter(p, q, Size - n);
        MergeData(pData, pBuff, n, Size);
    }
}

void TSortTable::MergeData (PTTabRecord *&pData,PTTabRecord *&pBuff,int n1,int n2)
{
    int i = 0;
    int j = n1;
    int k = 0;

    while ((i < n1) && (j < n2))
        if (pBuff[i]->GetKey() < pBuff[j]->GetKey())
            pData[k++] = pBuff[i++];
        else
            pData[k++] = pBuff[j++];
    while (i < n1)
        pData[k++] = pBuff[i++];
    while (j < n2)
        pData[k++] = pBuff[j++];

    Efficiency += n2;
}

void TSortTable::QuiqSort (PTTabRecord *pMem, int DataCount)
{
    int piv;

    if (DataCount > 1)
    {
        QuiqSplit(pMem, DataCount, piv);
        QuiqSort(pMem, piv);
        QuiqSort(pMem + piv, DataCount - piv);
    }
}

void TSortTable::QuiqSplit (PTTabRecord *pData, int Size, int &Pivot)
{
    int bel;
    int sr = Size / 2;

    PTTabRecord x = pData[0];
    PTTabRecord y = pData[sr];
    PTTabRecord z = pData[Size - 1];

    if ((x->GetKey() >= z->GetKey()) && (x->GetKey() >= y->GetKey()))
    {
        if (z->GetKey() >= y->GetKey())
            bel = Size -1;
        else
            bel = sr;
    }
    else if ((y->GetKey() >= z->GetKey()) && (y->GetKey() >= x->GetKey()))
    {
        if (z->GetKey() >= x->GetKey())
            bel = Size -1;
        else
            bel = 0;
    }
    else
    {
        if (y->GetKey() >= x->GetKey())
            bel = sr;
        else
            bel = 0;
    }

    int i = 0, j = Size - 1;

    while (i < j)
    {
        while (pData[i]->GetKey() < pData[bel]->GetKey())
            ++i;
        while (pData[j]->GetKey() > pData[bel]->GetKey())
            --j;
        if (i < j)
            std::swap(pData[i++], pData[j--]);
    }

    Pivot = j;
    Efficiency += Size;
}

PTDatValue TSortTable::FindRecord (TKey k)
{
    int i = 0, j = DataCount - 1, c;

    while (i <= j)
    {
        ++Efficiency;
        c = (i + j) / 2;
        if (pRecs[c]->GetKey() == k)
            return pRecs[c];
        if (pRecs[c]->GetKey() < k)
            i = c + 1;
        else
            j = c - 1;
    }

    return nullptr;
}

void TSortTable::InsRecord (TKey k, PTDatValue pVal )
{
    PTTabRecord p;

    if ((p = (PTTabRecord)FindRecord(k)) != nullptr)
    {
        p->SetValuePtr(pVal);
        return;
    }

    if (IsFull())
        throw std::runtime_error("insert when table is full");

    for (int i = 0; i < DataCount; ++i)
    {
        if (pRecs[i]->GetKey() > k)
        {
            for (int j = DataCount; j > i; --j)
                pRecs[j] = pRecs[j - 1];
            ++DataCount;
            Efficiency += DataCount;
            pRecs[i] = new TTabRecord(k, pVal);
            return;
        }
    }

    Efficiency += DataCount + 1;
    pRecs[DataCount++] = new TTabRecord(k, pVal);
}

void TSortTable::DelRecord (TKey k)
{
    if (FindRecord(k) != nullptr)
    {
        for (int i = 0; i < DataCount; ++i)
            if (pRecs[i]->GetKey() == k)
            {
                Efficiency += i + 1;
                delete pRecs[i];

                for (int j = i + 1; j < DataCount; ++j)
                    pRecs[j - 1] = pRecs[j];

                Efficiency += DataCount;
                --DataCount;
                
                return;
            }
    }
}

void TSortTable::Print(std::ostream& out) 
{
    for (int i = 0; i < DataCount; ++i) 
    {
        out << pRecs[i]->Key << " " << ((PTTabRecord)pRecs[i]->pValue)->GetKey() << std::endl;
    }
}
