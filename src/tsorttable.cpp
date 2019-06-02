#include "tsorttable.h"

TSortTable::TSortTable(const TScanTable& tab, TSortMethod sm) {
    TabSize = tab.GetTabSize();
    DataCount = tab.GetDataCount();
    pRecs = new PTTabRecord[TabSize];
    for (int i = 0; i < DataCount; ++i)
        pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
    SortMethod = sm;
    SortData();
    CurrPos = 0;
}

TSortTable& TSortTable::operator=(const TScanTable & tab) {
    if (pRecs != nullptr) {
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

void TSortTable::SortData() {
    Efficiency = 0;
    switch (SortMethod)
    {
    case INSERT_SORT:
        InsertSort(pRecs, DataCount);
        break;
    case MERGE_SORT:
        MergeSort(pRecs, DataCount);
        break;
    case QUICK_SORT:
        QuickSort(pRecs, DataCount);
        break;
    }
}

TSortMethod TSortTable::GetSortMethod() {
    return SortMethod;
}

void TSortTable::SetSortMethod(TSortMethod sm) {
    SortMethod = sm;
}

void TSortTable::InsertSort(PTTabRecord* pRecs, int DataCount) {
    if (DataCount == 0)
        return;
    PTTabRecord pR;
    Efficiency = DataCount;
    for (int i = 1, j; i < DataCount; ++i) {
        pR = pRecs[i];
        for (j = i - 1; j > -1; --j) {
            if (pRecs[j]->Key > pR->Key) {
                pRecs[j + 1] = pRecs[j];
                ++Efficiency;
            }
            else
                break;
        }
        pRecs[j + 1] = pR;
    }
}

void TSortTable::MergeSort(PTTabRecord* pRecs, int DataCount) {
    PTTabRecord* p = new PTTabRecord[DataCount];
    for (int i = 0; i < DataCount; ++i)
        p[i] = pRecs[i];
    Efficiency += DataCount;
    MergeSorter(pRecs, p, DataCount);
    delete[] p;
}

void TSortTable::MergeSorter(PTTabRecord*& pData, PTTabRecord*& pBuff, int Size) {
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

void TSortTable::MergeData(PTTabRecord*& pData, PTTabRecord*& pBuff, int n1, int n2) {
    int i = 0, k = 0;
    int j = n1;
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

void TSortTable::QuickSort(PTTabRecord* pRecs, int DataCount) {
    if (DataCount == 0)
        return;
    QuickSplit(pRecs, 0, DataCount - 1);
}

void TSortTable::QuickSplit(PTTabRecord* pData, int l, int r) {
    if (l == r)
        return;
    TTabRecord pivot = *pData[(l + r) / 2];
    int i = l, j = r;
    while (i <= j) {
        while (*pData[i] < pivot)
            ++i;
        while (*pData[j] > pivot)
            --j;
        if (i <= j) {
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

PTDatValue TSortTable::FindRecord(TKey k) {
    int l = 0, r = DataCount - 1;
    CurrPos = 0;
    while (l <= r) {
        ++Efficiency;
        int c = (l + r) / 2;
        if (pRecs[c]->Key == k) {
            CurrPos = c;
            return pRecs[c]->pValue;
        }
        if (pRecs[c]->Key >= k) {
            r = c - 1;
        }
        else {
            l = c + 1;
        }
    }
    CurrPos = l;
    return nullptr;
}

void TSortTable::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull()) throw "Error: is full";
    PTDatValue temp = FindRecord(k);
    if (!temp) {
        for (int i = DataCount; i > CurrPos; --i) {
            pRecs[i] = pRecs[i - 1];
            ++Efficiency;
        }
        pRecs[CurrPos] = new TTabRecord(k, pVal);
        ++DataCount;
    }
}

void TSortTable::DelRecord(TKey k) {
    PTDatValue temp = FindRecord(k);
    if (temp) {
        for (int i = CurrPos; i < DataCount - 1; ++i) {
            pRecs[i] = pRecs[i + 1];
            ++Efficiency;
        }
        --DataCount;
    }
}
