#include "sorttable.h"

#include "tabrecord.h"

TSortTable::TSortTable(int size) : TScanTable(size) {}

TSortTable::TSortTable(const TScanTable &tab) {
    *this = tab;
}

TSortTable & TSortTable::operator=(const TScanTable &tab) {
    if (this != &tab) {
        if (pRecs != nullptr) {
            for (int i; i < dataCount; ++i) {
                delete pRecs[i];
            }

            if (tabSize != tab.tabSize) {
                delete pRecs;
                pRecs = new PTTabRecord[tab.tabSize];
            }
        }

        tabSize = tab.tabSize;
        dataCount = tab.dataCount;
        currPos = tab.currPos;

        for (int i = 0; i < dataCount; ++i) {
            pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
        }

        SortData();
    }

    return *this;
}

TSortMethod TSortTable::GetSortMethod() {
    return sortMethod;
}

void TSortTable::SetSortMethod(TSortMethod sm) {
    sortMethod = sm;
}

PTDatValue TSortTable::FindRecord(TKey k) {
    int l = 0;
    int r = dataCount;
    int m;

    while (l < r) {
        ++efficiency;
        m = (l + r) / 2;
        if (k < pRecs[m]->GetKey()) {
            r = m;
        } else if (pRecs[m]->GetKey() < k) {
            l = m + 1;
        } else {
            currPos = m;
            return pRecs[m];
        }
    }

    currPos = m;
    return nullptr;
}

void TSortTable::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull()) {
        return;
    }

    if (FindRecord(k) != nullptr) {
        return;
    }

    pRecs[dataCount++] = new TTabRecord(k, pVal);

    SortData();
}

void TSortTable::DelRecord(TKey k) {
    if (FindRecord(k) != nullptr) {
        delete pRecs[currPos];

        for (int i = currPos + 1; i < dataCount; ++i) {
            pRecs[i - 1] = pRecs[i];
            ++efficiency;
        }

        --dataCount;
    }

    Reset();
}

void TSortTable::InsertSort(PTTabRecord *pMem, int dataCount) {
    if (dataCount < 1) {
        return;
    }

    PTTabRecord pR;
    efficiency += dataCount;

    int i, j;

    for (i = 1; i < dataCount; ++i) {
        pR = pRecs[i];
        for (j = i - 1; j > -1; --j) {
            if (pRecs[j]->GetKey() > pR->GetKey()) {
                pRecs[j+1] = pRecs[j];
                ++efficiency;
            } else {
                break;
            }
        }
        pRecs[j+1] = pR;
    }
}

void TSortTable::MergeSort(PTTabRecord *pMem, int dataCount) {
    PTTabRecord* p = new PTTabRecord[dataCount];

    for (int i = 0; i < dataCount; ++i) {
        p[i] = pMem[i];
    }

    efficiency += dataCount;

    MergeSorter(pMem, p, dataCount);

    delete[] p;
}

void TSortTable::MergeSorter(PTTabRecord *&pData, PTTabRecord *&pBuff, int size) {
    int n = size / 2;

    PTTabRecord* p = pBuff + n;
    PTTabRecord* q = pData + n;

    if (size > 1) {
        MergeSorter(pBuff, pData, n);
        MergeSorter(p, q, size - n);
        MergeData(pData, pBuff, n, size);
    }
}

void TSortTable::MergeData(PTTabRecord *&pData, PTTabRecord *&pBuff, int n1, int n2) {
    int i = 0;
    int j = n1;
    int k = 0;

    while ((i < n1) && (j < n2)) {
        if (pBuff[i]->GetKey() < pBuff[j]->GetKey()) {
            pData[k++] = pBuff[i++];
        } else {
            pData[k++] = pBuff[j++];
        }
    }

    while (i < n1) {
        pData[k++] = pBuff[i++];
    }

    while (j < n2) {
        pData[k++] = pBuff[j++];
    }

    efficiency += n2;
}

void TSortTable::QuickSort(PTTabRecord *pMem, int dataCount) {
    int piv;

    if (dataCount > 1) {
        QuickSplit(pMem, dataCount, piv);
        QuickSort(pMem, piv);
        QuickSort(pMem + piv, dataCount - piv);
    }
}

void TSortTable::QuickSplit(PTTabRecord *pData, int size, int &pivot) {
    int bel;
    int sr = size / 2;

    PTTabRecord x = pData[0];
    PTTabRecord y = pData[sr];
    PTTabRecord z = pData[size - 1];

    if ((x->GetKey() >= z->GetKey()) && (x->GetKey() >= y->GetKey())) {
        if (z->GetKey() >= y->GetKey()) {
            bel = size -1;
        } else {
            bel = sr;
        }
    } else if ((y->GetKey() >= z->GetKey()) && (y->GetKey() >= x->GetKey())) {
        if (z->GetKey() >= x->GetKey()) {
            bel = size -1;
        } else {
            bel = 0;
        }
    } else {
        if (y->GetKey() >= x->GetKey()) {
            bel = sr;
        }
        else {
            bel = 0;
        }
    }
    int i = 0, j = size - 1;
    while (i < j) {
        while (pData[i]->GetKey() < pData[bel]->GetKey()) {
            ++i;
        }
        while (pData[j]->GetKey() > pData[bel]->GetKey()) {
            --j;
        }
        if (i < j) {
            PTTabRecord tmp = pData[i];
            pData[i] = pData[j];
            pData[j] = tmp;
            ++i;
            --j;
        }
    }

    pivot = j;
    efficiency += size;
}

void TSortTable::SortData() {
    switch (sortMethod) {
      case INSERT_SORT:
        InsertSort(pRecs, dataCount);
        break;
      case MERGE_SORT:
        MergeSort(pRecs, dataCount);
        break;
      case QUIQ_SORT:
        QuickSort(pRecs, dataCount);
        break;
    }
}
