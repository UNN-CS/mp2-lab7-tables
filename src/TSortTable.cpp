#include "TSortTable.h"

TSortTable::TSortTable(const TScanTable &tab) { // from scantable to sorttable
    *this = tab;
}

TSortTable & TSortTable::operator=(const TScanTable &tab) {
    if (pRecs != nullptr) {
        for (int i = 0; i < DataCount; i++)
            delete pRecs[i];
        delete[] pRecs;
        pRecs = nullptr;
    }
    TabSize = tab.GetTabSize();
    DataCount = tab.GetDataCount();
    pRecs = new PTTabRecord[TabSize];
    for (int i = 0; i < DataCount; i++)
        pRecs[i] = PTTabRecord(tab.pRecs[i]->GetCopy());
    SortData();
    CurrPos = 0;
    return *this;
}

PTDatValue TSortTable::FindRecord(TKey k) { // bibary search
    int i, i1 = 0, i2 = DataCount - 1;
    while (i1 <= i2) {
        i = (i1 + i2) / 2;
        if (pRecs[i]->Key == k) {
            SetRetCode(TabOK);
            CurrPos = i;
            return pRecs[i]->pValue;
        }
        if (pRecs[i]->Key < k)
            i1 = i + 1;
        else // >=
            i2 = i - 1;
    }
    SetRetCode(TabNoRec); // if did not find
    return nullptr;
}

void TSortTable::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull())
        SetRetCode(TabFull);
    else {
        PTDatValue temp = FindRecord(k);
        if (RetCode == TabOK)
            SetRetCode(TabRecDbl);
        else {
            SetRetCode(TabOK);
            for (int i = DataCount; i > CurrPos; i--) // why CurrPos??
                pRecs[i] = pRecs[i - 1]; // repack
            pRecs[CurrPos] = new TTabRecord(k, pVal);
            DataCount++;    
        }
    }
}

void TSortTable::DelRecord(TKey k) {
    PTDatValue tmp = FindRecord(k);
    if (tmp == nullptr)
        SetRetCode(TabNoRec);
    else
    {
        SetRetCode(TabOK);
        PTTabRecord tmp = pRecs[CurrPos];
        for (int i = CurrPos; i < DataCount - 1; i++) pRecs[i] = pRecs[i + 1];
        delete tmp;
        DataCount--;
    }
}

void TSortTable::SortData() {
    Efficiency = 0;
    switch (SortMethod) {
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

void TSortTable::InsertSort(PTTabRecord *pMem, int DataCount) {
    PTTabRecord pR;
    Efficiency = DataCount;
    for (int i = 1, j; i < DataCount; i++) { // before i sorted
        pR = pMem[i]; // adding element
        for (j = i - 1; j > -1; j--)
            if (pMem[j]->Key > pR->Key) {
                pMem[j + 1] = pMem[j]; // move right
                Efficiency++;
            }
            else break;
        pMem[j + 1] = pR; // insert
    }
}

void TSortTable::MergeSort(PTTabRecord *pMem, int DataCount) {
    PTTabRecord * pData = pMem;
    PTTabRecord * pBuff = new PTTabRecord[DataCount];
    PTTabRecord * pTemp = pBuff;
    MergeSorter(pData, pBuff, DataCount);
    if (pData = pTemp) // sorted data is in buffer
        for (int i = 0; i < DataCount; i++)
            pBuff[i] = pData[i];
    delete pTemp;
}

void TSortTable::MergeSorter(PTTabRecord * &pData, PTTabRecord * &pBuff, int Size) {
    int n1 = (Size + 1) / 2;
    int n2 = Size - n1;
    if (Size > 2) {
        PTTabRecord * pDat2 = pData + n1, *pBuff2 = pBuff + n1;
        MergeSorter(pData, pBuff, n1); // sorting of halfs of massive
        MergeSorter(pDat2, pBuff2, n2);
    }
    MergeData(pData, pBuff, n1, n2); // merge sorted halfs
}

void TSortTable::MergeData(PTTabRecord *&pData, PTTabRecord *&pBuff, int n1, int n2) {
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

void TSortTable::QuickSort(PTTabRecord *pMem, int DataCount) {
    int pivot;
    int n1, n2; // sizes of splitted blocks of data
    if (DataCount > 1) {
        QuickSplit(pMem, DataCount, pivot);
        n1 = pivot + 1;
        n2 = DataCount - n1;
        QuickSort(pMem, n1 - 1);
        QuickSort(pMem + n1, n2);
    }
}

void TSortTable::QuickSplit(PTTabRecord *pData, int Size, int &Pivot) {
    PTTabRecord pPivot = pData[0], pTemp;
    int i1 = 1, i2 = Size - 1;
    while (i1 <= i2) {
        while ((i1 < Size) && !(pData[i1]->Key > pPivot->Key))
            i1++;
        while (pData[i2]->Key > pPivot->Key)
            i2--;
        if (i1 < i2) {
            pTemp = pData[i1];
            pData[i1] = pData[i2];
            pData[i2] = pTemp;
        }
    }
    pData[0] = pData[i2];
    pData[i2] = pPivot;
    Pivot = i2;
    Efficiency += Size;
}