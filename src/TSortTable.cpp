#include "TSortTable.h"

TSortTable::TSortTable(const TScanTable &tab) : TScanTable(tab.GetTabSize())
{
    CurrPos = tab.CurrPos;
    DataCount = tab.DataCount;
    for (int i = 0; i < DataCount; ++i)
        pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
    SortMethod = QUICK_SORT;
    SortData();
}

TSortTable &TSortTable::operator=(const TScanTable &tab)
{
    if (pRecs != nullptr)
    {
        for (int i = 0; i < DataCount; ++i)
            delete pRecs[i];
        delete[] pRecs;
        pRecs = nullptr;
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

void TSortTable::SetSortMethod(TSortMethod sm)
{
    SortMethod = sm;
}

void TSortTable::SortData(void)
{
    switch (SortMethod)
    {
    case INSERT_SORT:
        InsertSort(pRecs, DataCount);
        return;
    case MERGE_SORT:
        MergeSort(pRecs, DataCount);
        return;
    case QUICK_SORT:
        QuickSort(pRecs, DataCount);
        return;
    default:
        throw "wrong SortMethod";
    }
}

void TSortTable::InsertSort(PTTabRecord *pMem, int DataCount)
{
    PTTabRecord pR;
    Efficiency = DataCount;
    for (int i = 1, j; i < DataCount; i++)
    {
        pR = pRecs[i];
        for (j = i - 1; j > -1; j--)
            if (pRecs[j]->Key > pR->Key)
            {
                pRecs[j + 1] = pRecs[j];
                Efficiency++;
            }
            else
                break;
        pRecs[j + 1] = pR;
    }
}

void TSortTable::MergeSort(PTTabRecord *pMem, int DataCount)
{
    PTTabRecord *p = new PTTabRecord[DataCount];
    for (int i = 0; i < DataCount; ++i)
        p[i] = pMem[i];
    Efficiency += DataCount;
    MergeSorter(pMem, p, DataCount);
    delete[] p;
}

void TSortTable::MergeSorter(PTTabRecord *&pData, PTTabRecord *&pBuff, int size)
{
    int n = size / 2;
    PTTabRecord *p = pBuff + n;
    PTTabRecord *q = pData + n;
    if (size > 1)
    {
        MergeSorter(pBuff, pData, n);
        MergeSorter(p, q, size - n);
        MergeData(pData, pBuff, n, size);
    }
}

void TSortTable::MergeData(PTTabRecord *&pData, PTTabRecord *&pBuff, int n1, int n2)
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

void TSortTable::QuickSort(PTTabRecord *pMem, int DataCount)
{
    int piv;
    if (DataCount > 1)
    {
        QuickSplit(pMem, DataCount, piv);
        QuickSort(pMem, piv);
        QuickSort(pMem + piv, DataCount - piv);
    }
}

void TSortTable::QuickSplit(PTTabRecord *pData, int size, int &Pivot)
{
    int bel;
    int sr = size / 2;
    PTTabRecord x = pData[0];
    PTTabRecord y = pData[sr];
    PTTabRecord z = pData[size - 1];
    if ((x->GetKey() >= z->GetKey()) && (x->GetKey() >= y->GetKey()))
    {
        if (z->GetKey() >= y->GetKey())
            bel = size - 1;
        else
            bel = sr;
    }
    else if ((y->GetKey() >= z->GetKey()) && (y->GetKey() >= x->GetKey()))
    {
        if (z->GetKey() >= x->GetKey())
            bel = size - 1;
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
    int i = 0, j = size - 1;
    while (i < j)
    {
        while (pData[i]->GetKey() < pData[bel]->GetKey())
            ++i;
        while (pData[j]->GetKey() > pData[bel]->GetKey())
            --j;
        if (i < j)
            swap(pData[i++], pData[j--]);
    }
    Pivot = j;
    Efficiency += size;
}

PTDatValue TSortTable::FindRecord(TKey key)
{
    //binary search
    SetRetCode(TabNoRec);
    int left = 0, right = DataCount - 1, mid;
    while (left <= right)
    {
        Efficiency++;
        mid = (right + left) / 2;
        if (pRecs[mid]->GetKey() == key)
        {
            SetRetCode(TabOK);
            CurrPos = mid;
            return pRecs[mid]->GetValuePTR();
        }
        if (key < pRecs[mid]->GetKey())
            right = mid - 1;
        else
            left = mid + 1;
    }
    SetRetCode(TabNoRec);
    return nullptr;
}

void TSortTable::InsRecord(TKey key, PTDatValue pVal)
{
    if (IsFull())
    {
        SetRetCode(TabFull);
        throw "tab is full";
    }
    else
    {
        PTDatValue tmp = FindRecord(key);
        if (tmp != nullptr)
            SetRetCode(TabRecDbl);
        else
        {
            SetRetCode(TabOK);
            for (int i = DataCount; i > CurrPos; i--)
                pRecs[i] = pRecs[i - 1];
            pRecs[CurrPos] = new TTabRecord(key, pVal);
            Efficiency += DataCount;
            DataCount++;
        }
    }
}

void TSortTable::DelRecord(TKey k)
{
    FindRecord(k);
    if (GetRetCode() == TabOK)
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
