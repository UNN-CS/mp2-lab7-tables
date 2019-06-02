#include "tsorttable.h"


TSortTable::TSortTable(const TScanTable &tab) {
    *this = tab;
}       /*================================================*/

TSortTable& TSortTable::operator=(const TScanTable &tab) {
    if (pRecs != NULL) {
        for (int i = 0; i < DataCount; i++) 
            delete pRecs[i];
        delete[] pRecs;
        pRecs = NULL;
    }

    tabSize     = tab.GetTabSize();
    DataCount   = tab.GetDataCount();
    pRecs       = new PTTabRecord[tabSize];

    for (int i = 0; i < DataCount; i++)
        pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
    SortData();
    currPos = 0;
    return *this;
}       /*================================================*/

PTDatValue TSortTable::FindRecord(TKey k) {
    int i, i1 = 0, i2 = DataCount - 1;
}       /*================================================*/

void TSortTable::InsRecord(TKey k, PTDatValue pVal) {

}       /*================================================*/

void TSortTable::DelRecord(TKey k) {

}       /*================================================*/

void TSortTable::SortData() {
    Efficiency = 0;
    if (SortMethod == INSERT_SORT) {
        InsertSort(pRecs, DataCount);
    } else if (SortMethod == QUIQ_SORT) {
        QuiqSort(pRecs, DataCount);
    } else if (SortMethod == MERGE_SORT) {
        MergeSort(pRecs, DataCount);
    } else {
        SetRetCode(NoSortMethod);
    }
}       /*================================================*/

TSortMethod TSortTable::GetSortMethod() {
    return SortMethod;
}       /*================================================*/

void TSortTable::SetSortMethod(TSortMethod sm) {
    SortMethod = sm;
}       /*================================================*/

void TSortTable::InsertSort(PTTabRecord *pMem, int dataCount) {
    if (DataCount == 0)
        return;

    Efficiency = DataCount;
    for (int i = 1, j; i < DataCount; ++i) {
        for (j = i - 1; j > -1; --j) {
            if (pRecs[j]->key > pRecs[i]->key) {
                pRecs[j+1] = pRecs[j];
                ++Efficiency;
            } 
            else
                break;
        }
        pRecs[j+1] = pRecs[i];
    }
}       /*================================================*/

void TSortTable::MergeSort(PTTabRecord *pMem, int dataCount) {
    if (DataCount == 0)
        return;

    PTTabRecord* temp = new PTTabRecord[DataCount];
    MergeSorter(pRecs, temp, 0, DataCount - 1);
    
    delete temp;
}       /*================================================*/

void TSortTable::MergeSorter(PTTabRecord * &pData, PTTabRecord * &pBuff, int left, int right) {
    int middle = (left + right) / 2;

    if (left == right)
        return;

    MergeSorter(pData, pBuff, left, middle);
    MergeSorter(pData, pBuff, middle + 1, right);
    MergeData(pData, pBuff, left, middle + 1, right);

    for (int i = left; i <= right; ++i)
        pData[i] = pBuff[i];
    Efficiency += DataCount;
}       /*================================================*/

void TSortTable::MergeData(PTTabRecord *&pData, PTTabRecord *&pBuff, int left, int middle, int right) {
    int i = left, j = middle, k = left;
    while ((i <= j) && (j <= right)) {
        if (pData[i]->key <= pData[j]->key)
            pBuff[k++] = pData[i++];
        else
            pBuff[k++] = pData[j++];
    }

    while (j <= right)
        pBuff[k++] = pData[j++];
    while (i <= middle)
        pBuff[k++] = pData[i++];

    Efficiency += right - left;
}       /*================================================*/

void TSortTable::QuiqSort(PTTabRecord *pMem, int DataCount) {
    if (DataCount == 0)
        return;
    QuiqSplit(pRecs, 0, DataCount - 1);
}       /*================================================*/

void TSortTable::QuiqSplit(PTTabRecord *pData, int left, int right) {
    if (left == right)
        return;

    TTabRecord pivot = *pData[(left + right) / 2];
    int i = left, j = right;
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
    Efficiency += right - left;
    QuiqSplit(pData, left, i-1);
    QuiqSplit(pData, i, right);
}       /*================================================*/
