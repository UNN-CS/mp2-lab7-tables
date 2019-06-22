#include "TArrayHash.h"

TArrayHash::TArrayHash(int Size, int Step) : THashTable() {
    pRecs = new PTTabRecord[Size];
    TabSize = Size;
    HashStep = Step;
    for (int i = 0; i < TabSize; ++i) pRecs[i] = NULL;
    pMark = new TTabRecord(string(""), NULL);
}

TArrayHash::~TArrayHash() {
    for (int i = 0; i < TabSize; ++i)
        if ((pRecs[i] != NULL) && (pRecs[i] != pMark)) delete pRecs[i];
    delete[]pRecs;
    delete pMark;
}

PTDatValue TArrayHash::FindRecord(TKey k) {
    PTDatValue pVal = NULL;
    FreePos = -1;
    Efficiency = 0;
    CurrPos = HashFunc(k) % TabSize;
    for (int i = 0; i < TabSize; ++i) {
        Efficiency++;
        if (pRecs[CurrPos] == NULL) break;
        else if (pRecs[CurrPos] == pMark)
        {
            if (FreePos == -1)
                FreePos = CurrPos;
        }
        else if (pRecs[CurrPos]->GetKey() == k)
        {
            pVal = pRecs[CurrPos]->GetValuePTR();
            break;
        }
        CurrPos = GetNextPos(CurrPos);
    }
    if (pVal == NULL) SetRetCode(TabNoRec);
    else SetRetCode(TabOK);
    return pVal;
}

void TArrayHash::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull()) SetRetCode(TabNoMem);
    else {
        PTDatValue tmp = FindRecord(k);
        if (tmp != NULL) SetRetCode(TabRecDbl);
        else
        {
            SetRetCode(TabOK);
            if (FreePos != -1) CurrPos = FreePos;
            if (pRecs[CurrPos] != NULL && pRecs[CurrPos] != pMark)
            {
                delete pRecs[CurrPos];
                DataCount--;
            }
            pRecs[CurrPos] = new TTabRecord(k, pVal);
            DataCount++;
        }
    }
}

void TArrayHash::DelRecord(TKey k)
{
    PTDatValue tmp = FindRecord(k);
    if (tmp == NULL) SetRetCode(TabNoRec);
    else {
        SetRetCode(TabOK);
        delete pRecs[CurrPos];
        pRecs[CurrPos] = pMark;
        //cout << DataCount << endl;
        DataCount--;
    }
}

int TArrayHash::Reset() {
    CurrPos = 0;
    for (; CurrPos<TabSize; ++CurrPos)
        if ((pRecs[CurrPos] != NULL) && (pRecs[CurrPos] != pMark)) break;
    return IsTabEnded();
}

int TArrayHash::IsTabEnded() const {
    return CurrPos >= TabSize;
}

int TArrayHash::GoNext() {
    if (!IsTabEnded()) {
        while (++CurrPos < TabSize)
            if ((pRecs[CurrPos] != NULL) && (pRecs[CurrPos] != pMark)) break;
    }
    return IsTabEnded();
}

TKey TArrayHash::GetKey() const {
    return ((CurrPos < 0) || (CurrPos >= TabSize)) ? string("") : pRecs[CurrPos]->GetKey();
}

PTDatValue TArrayHash::GetValuePTR()const {
    return ((CurrPos < 0) || (CurrPos >= TabSize)) ? NULL : pRecs[CurrPos]->GetValuePTR();
}
