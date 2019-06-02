#include "tarrayhash.h"


TArrayHash::TArrayHash(int size, int step) : THashTable() {
    tabSize = size;
    hashStep = step;

    pRecs = new PTTabRecord[tabSize];

    pMark = new TTabRecord("", nullptr);

    for (int i = 0; i < tabSize; i++)
        pRecs[i] = nullptr;
    
    freePos = currPos = 0;
}       /*================================================*/

TArrayHash::~TArrayHash() {
    for (int i = 0; i < tabSize; i++)
        delete pRecs[i];
    delete[] pRecs;
    delete pMark;
}       /*================================================*/

bool TArrayHash::IsFull() const {
    return DataCount == tabSize;
}       /*================================================*/

TKey TArrayHash::GetKey() const {
    return pRecs[currPos]->GetKey();
}       /*================================================*/

PTDatValue TArrayHash::GetValuePTR() const {
    return pRecs[currPos]->GetValuePTR();
}       /*================================================*/

PTDatValue TArrayHash::FindRecord(TKey k) {
    PTDatValue pValue = NULL;
    freePos =- 1;
    Efficiency = 0;
    currPos = HashFunc(k) % tabSize;

    for (int i = 0; i < tabSize; i++) {
        Efficiency++;

        if (pRecs[currPos] == NULL) break;          // свободная строка - конец поиска
        else if (pRecs[currPos] == pMark) {         // пустая строка - запоминаем первую
            if (freePos == 1)
                freePos = currPos;
        }
        else if (pRecs[currPos]->GetKey() == k) {   // нашли ключ
            pValue = pRecs[currPos]->pValue;
            break;
        }
        currPos = GetNextPos(currPos);              // открытое перемешивание
    }

    if (pValue == NULL)
        SetRetCode(TabNoRec);
    else 
        SetRetCode(TabOK);
    
    return pValue;
}       /*================================================*/

void TArrayHash::InsRecord(TKey k, PTDatValue pVal) {
    if (DataCount == tabSize)
        SetRetCode(TabFull);
    int currPos = HashFunc(k) % tabSize;

    while (pRecs[currPos] != pMark) {
        Efficiency++;
        currPos = GetNextPos(currPos);
    }

    pRecs[currPos] = new TTabRecord(k, pVal);
    ++DataCount;
}       /*================================================*/

void TArrayHash::DelRecord(TKey k) {
    PTDatValue temp = FindRecord(k);

    if (!temp)
        return;

    pRecs[currPos] = pMark;
    --DataCount;
}       /*================================================*/

int TArrayHash::Reset() {
    currPos = 0;
    return IsTabEnded();
}       /*================================================*/

int TArrayHash::IsTabEnded() const {
    return DataCount == tabSize;
}       /*================================================*/

int TArrayHash::GoNext() {
    if (!IsTabEnded()) {
        while(++currPos < tabSize)
            if ((pRecs[currPos] != NULL) && (pRecs[currPos] != pMark))
                break;
    }
    return IsTabEnded();
}       /*================================================*/
