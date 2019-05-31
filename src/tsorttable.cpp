#include <iostream>

#include "tsorttable.hpp"
#include "ttabrecord.hpp"

TSortTable::TSortTable(const TScanTable &tab, TSortMethod sm)
{
    TabSize = tab.GetTabSize();
    DataCount = tab.GetDataCount();

    pRecs = new PTTabRecord[TabSize];
    for (int i = 0; i < DataCount; ++i)
        pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
    SortMethod = sm;
    SortData();
    CurrPos = 0;
}

TSortTable &TSortTable::operator=(const TScanTable &tab)
{
    if (pRecs)
    {
        for (int i = 0; i < DataCount; ++i)
            delete pRecs[i];
        delete[] pRecs;
    }

    TabSize = tab.GetTabSize();
    DataCount = tab.GetDataCount();

    pRecs = new PTTabRecord[TabSize];
    for (int i = 0; i < DataCount; ++i)
        pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
    SortData();
    CurrPos = 0;

    return *this;
}

void TSortTable::SortData()
{
    Efficiency = 0;

    switch (SortMethod)
    {
    case INSERT_SORT:
        InsertSort(pRecs, DataCount);
        break;
    case QUICK_SORT:
        QuickSort(pRecs, DataCount);
        break;
    case MERGE_SORT:
        MergeSort(pRecs, DataCount);
        break;
    default:
        throw - 1;
        break;
    }
}

TSortMethod TSortTable::GetSortMethod()
{
    return SortMethod;
}

void TSortTable::SetSortMethod(TSortMethod sm)
{
    SortMethod = sm;
}

void TSortTable::InsertSort(PTTabRecord *pRecs, int DataCount)
{
    if (DataCount == 0)
        return;

    PTTabRecord pR;
    Efficiency = DataCount;

    for (int i = 1, j; i < DataCount; ++i)
    {
        pR = pRecs[i];
        for (j = i - 1; j > -1; --j)
        {
            if (pRecs[j]->Key > pR->Key)
            {
                pRecs[j + 1] = pRecs[j];
                ++Efficiency;
            }
            else
                break;
        }
        pRecs[j + 1] = pR;
    }
}

void TSortTable::MergeSort(PTTabRecord *pRecs, int DataCount)
{
    if (DataCount == 0)
        return;
    PTTabRecord *t = (PTTabRecord *)calloc(DataCount, sizeof(PTTabRecord));
    MergeSorter(pRecs, t, 0, DataCount - 1);
    free(t);
}

void TSortTable::MergeSorter(PTTabRecord *a, PTTabRecord *tmp, int l, int r)
{
    int c = (l + r) / 2;
    if (l == r)
        return;

    MergeSorter(a, tmp, l, c);
    MergeSorter(a, tmp, c + 1, r);
    MergeData(a, tmp, l, c, r);

    for (int i = l; i <= r; ++i)
        a[i] = tmp[i];

    Efficiency += DataCount;
}

void TSortTable::MergeData(PTTabRecord *a, PTTabRecord *tmp, int l, int c, int r)
{
    int i = l, j = c + 1, k = l;

    while ((i <= c) && (j <= r))
    {
        if (a[i]->Key <= a[j]->Key)
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }
    while (j <= r)
        tmp[k++] = a[j++];
    while (i <= c)
        tmp[k++] = a[i++];

    Efficiency += r - l;
}

void TSortTable::QuickSort(PTTabRecord *pRecs, int DataCount)
{
    if (DataCount == 0)
        return;
    QuickSplit(pRecs, 0, DataCount - 1);
}

void TSortTable::QuickSplit(PTTabRecord *pData, int l, int r)
{
    if (l == r)
        return;
    TTabRecord pivot = *pData[(l + r) / 2];

    int i = l, j = r;
    while (i <= j)
    {
        while (*pData[i] < pivot)
            ++i;
        while (*pData[j] > pivot)
            --j;
        if (i <= j)
        {
            TTabRecord tmp = *pData[i];
            *pData[i] = *pData[j];
            *pData[j] = tmp;
            ++i, --j;
        }
    }

    Efficiency += r - l;

    QuickSplit(pData, l, i - 1);
    QuickSplit(pData, i, r);
}

PTDatValue TSortTable::FindRecord(TKey k)
{
    int l = 0, r = DataCount - 1;
    CurrPos = 0;

    while (l <= r)
    {
        ++Efficiency;
        int c = (l + r) / 2;
        if (pRecs[c]->Key == k)
        {
            CurrPos = c;
            return pRecs[c]->pValue;
        }
        if (pRecs[c]->Key >= k)
        {
            r = c - 1;
        }
        else
        {
            l = c + 1;
        }
    }

    CurrPos = l;

    return nullptr;
}

void TSortTable::InsRecord(TKey k, PTDatValue pVal)
{
    if (IsFull())
        throw - 1;

    PTDatValue temp = FindRecord(k);

    if (!temp)
    {
        for (int i = DataCount; i > CurrPos; --i)
        {
            pRecs[i] = pRecs[i - 1];
            ++Efficiency;
        }
        pRecs[CurrPos] = new TTabRecord(k, pVal);
        ++DataCount;
    }
}

void TSortTable::DelRecord(TKey k)
{
    PTDatValue temp = FindRecord(k);

    if (temp)
    {
        for (int i = CurrPos; i < DataCount - 1; ++i)
        {
            pRecs[i] = pRecs[i + 1];
            ++Efficiency;
        }
        --DataCount;
    }
}

void TSortTable::Print(std::ostream &out)
{
    for (int i = 0; i < DataCount; ++i)
    {
        out << pRecs[i]->Key << " " << ((PTTabRecord)pRecs[i]->pValue)->GetKey() << std::endl;
    }
}
