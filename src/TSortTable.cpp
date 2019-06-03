// TSortTable.cpp
#include "TSortTable.h"
#include <iostream>
TSortTable::TSortTable(const TScanTable &tab, TSortMethod sm) {
    TabSize = tab.GetTabSize();
    DataCount = tab.GetDataCount();
    pRecs = new PTTabRecord[TabSize];
    for (int i = 0; i < DataCount; ++i)
        pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
    SortMethod = sm;
    SortData();
    CurrPos = 0;
}

TSortTable & TSortTable::operator=(const TScanTable &tab) {
    if (pRecs) {
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

PTDatValue TSortTable::FindRecord(TKey k) {
    int left = 0, right = DataCount - 1, c;
    while (left <= right)
    {
        ++Efficiency;
        c = (left + right) / 2;
        if (pRecs[c]->GetKey() == k)
            return pRecs[c];
        if (pRecs[c]->GetKey() < k)
            left = c + 1;
        else
            right = c - 1;
    }
    return nullptr;
}

void TSortTable::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull())
        throw "insert in full table";
    PTTabRecord t = (PTTabRecord)FindRecord(k);
    if (t != nullptr) {
        t->SetValuePtr(pVal);
        return;
    }
    for (int i = 0; i < DataCount; ++i) {
        if (pRecs[i]->GetKey() > k) {
            for (int j = DataCount; j > i; --j)
                pRecs[j] = pRecs[j - 1];
            DataCount++;
            Efficiency += DataCount;
            pRecs[i] = new TTabRecord(k, pVal);
            return;
        }
    }
    Efficiency += DataCount + 1;
    pRecs[DataCount++] = new TTabRecord(k, pVal);
}

void TSortTable::DelRecord(TKey k) {
    if (FindRecord(k) != nullptr) {
        for (int i = 0; i < DataCount; ++i) {
            if (pRecs[i]->GetKey() == k) {
                Efficiency += i;
                delete pRecs[i];
                int j;
                for (j = i + 1; j < DataCount; ++j)
                    pRecs[j - 1] = pRecs[j];
                Efficiency += j;
                DataCount--;
                return;
            }
        }
    }
}

void TSortTable::SortData() {
    Efficiency = 0;
    switch (SortMethod) {
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
        return;
    }
}

void TSortTable::InsertSort(PTTabRecord *pRecs, int dataCount) {
    PTTabRecord pR;
    Efficiency += DataCount;
    for (int i = 1, j; i < DataCount; ++i) {
        pR = pRecs[i];
        for(j = i -1; j> -1; j--)
            if (pRecs[j]->Key > pR->Key) {
                pRecs[j + 1] = pRecs[j];
                Efficiency++;
            }
            else break;
        pRecs[j + 1] = pR;
    }
}

void TSortTable::MergeSort(PTTabRecord *pRecs, int DataCount) {
    PTTabRecord* p = new PTTabRecord[DataCount];
    for (int i = 0; i < DataCount; ++i)
        p[i] = pRecs[i];
    Efficiency += DataCount;
    MergeSorter(pRecs, p, DataCount);
    delete[] p;
}

void TSortTable::MergeSorter(PTTabRecord* &pData, PTTabRecord* &pBuff, int Size) {
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

void TSortTable::MergeData(PTTabRecord* &pData, PTTabRecord* &pBuff, int n1, int n2) {
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

void TSortTable::QuiqSort(PTTabRecord *pRecs, int DataCount) {
    int piv;
    if (DataCount > 1)
    {
        QuiqSplit(pRecs, DataCount, piv);
        QuiqSort(pRecs, piv);
        QuiqSort(pRecs + piv, DataCount - piv);
    }
}

void TSortTable::QuiqSplit(PTTabRecord *pData, int size, int &pivot) {
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
            std::swap(pData[i++], pData[j--]);
    }
    pivot = j;
    Efficiency += size;
}
