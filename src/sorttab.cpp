#include "sorttab.h"

TSortTable::TSortTable(const TScanTable &tab)
{
    *this = tab;
}

TSortTable & TSortTable::operator=(const TScanTable &tab)
{
    if (pRecs != nullptr)
    {
        for (int i = 0; i < DataCount; i++)
            delete pRecs[i];
        delete [] pRecs;
        pRecs = nullptr;
    }
    TabSize = tab.GetTabSize();
    DataCount = tab.GetDataCount();
    pRecs = new PTTabRecord[TabSize];
    for (int i = 0; i < DataCount; i++)
        pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
    SortData();
    CurrPos = 0;
    return *this;
}

PTDatValue TSortTable::FindRecord(TKey k)
{
    SetRetCode(TabOK);

    int i, i1 = 0, i2 = DataCount - 1;

    Efficiency = 0;

    while (i1 <= i2)
    {
        Efficiency++;

        i = (i1 + i2) / 2;

        if (k == pRecs[i]->GetKey())
        {
            CurrPos = i;
            return pRecs[CurrPos]->GetValuePtr();
        }

        if (k < pRecs[i]->GetKey())
            i2 = i - 1;
        else
            i1 = i + 1;
    }

    CurrPos = i1;

    SetRetCode(TabNoRec);
}

void TSortTable::InsRecord(TKey k, PTDatValue pVal)
{
    if (IsFull())
        SetRetCode(TabFull);
    else
    {
        FindRecord(k);
        if (RetCode == TabOK)
            SetRetCode(TabRecDbl);
        else
        {
            for (int i = DataCount; i > CurrPos; i--)
            {
                pRecs[i] = pRecs[i - 1];
                Efficiency++;
            }
            pRecs[CurrPos] = new TTabRecord(k, pVal);
            DataCount++;
        }
    }
}

void TSortTable::DelRecord(TKey k)
{
    FindRecord(k);
    if (RetCode == TabOK)
    {
        for (int i = CurrPos; i < DataCount; i++)
        {
            pRecs[i] = pRecs[i + 1];
            Efficiency++;
        }
        DataCount--;
    }
}

void TSortTable::SortData(void)
{
    Efficiency = 0;
    switch (SortMethod)
    {
        case INSERT_SORT: InsertSort(pRecs, DataCount); break;
        case MERGE_SORT: MergeSort(pRecs, DataCount); break;
        case QUICK_SORT: QuickSort(pRecs, DataCount); break;
    }
}

void TSortTable::InsertSort(PTTabRecord *pMem, int DataCount)
{
    int j;
    PTTabRecord pR;
    Efficiency = DataCount;
    for (int i = 1; i < DataCount; i++)
    {
        pR = pRecs[i];
        for (j = i - 1; j > -1; j--)
        {
            if (pRecs[j]->Key > pR->Key)
            {
                pRecs[j + 1] = pRecs[j];
                Efficiency++;
            }
            else break;
        }
        pRecs[j + 1] = pR;
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

void TSortTable::MergeSorter(PTTabRecord * &pData, PTTabRecord * &pBuff, int Size)
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

void TSortTable::MergeSort(PTTabRecord *pMem, int DataCount)
{

    PTTabRecord* pBuff = new PTTabRecord[DataCount];
    for (int i = 0; i < DataCount; ++i)
        pBuff[i] = pMem[i];
    Efficiency += DataCount;
    MergeSorter(pMem, pBuff, DataCount);
    delete [] pBuff;
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

void TSortTable::QuickSplit(PTTabRecord *pData, int Size, int &Pivot)
{
    int bel;
    int sr = Size / 2;
    PTTabRecord x = pData[0];
    PTTabRecord y = pData[sr];
    PTTabRecord z = pData[Size - 1];
    if ((x->GetKey() >= z->GetKey()) && (x->GetKey() >= y->GetKey()))
    {
        if (z->GetKey() >= y->GetKey())
            bel = Size - 1;
        else
            bel = sr;
    }
    else if ((y->GetKey() >= z->GetKey()) && (y->GetKey() >= x->GetKey()))
    {
        if (z->GetKey() >= x->GetKey())
            bel = Size - 1;
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
            swap(pData[i++], pData[j--]);
    }
    Pivot = j;
    Efficiency += Size;
}

TSortMethod TSortTable::GetSortMethod(void)
{
    return SortMethod;
}

void TSortTable::SetSortMethod(TSortMethod sm)
{
    SortMethod = sm;
}

