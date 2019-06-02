#include "tlisthash.h"


TListHash::TListHash(int size) : THashTable() {
    TabSize  = size;
    CurrList = 0;

    pList = new PTDatList[TabSize];
    for (int i = 0; i < TabSize; i++)
        pList[i] = new TDatList();
}       /*================================================*/

TListHash::~TListHash() {
    for (int i = 0; i < TabSize; i++)
        delete pList[i];
    
    delete[] pList;
}       /*================================================*/

bool TListHash::IsFull() const {
    PTDatLink pLink = new TDatLink();
    bool temp = (pLink == NULL);
    delete pLink;
    return temp;
}       /*================================================*/

PTDatValue TListHash::FindRecord(TKey k) {
    PTDatValue pValue = NULL;
    CurrList = HashFunc(k) % TabSize;                       // функции расстановки
    PTDatList pL = pList[CurrList]; Efficiency = 0;
    for (pL->Reset(); !pL->IsListEnded(); pL->GoNext())     // поиск по списку
        if (PTTabRecord(pL->GetDatValue())->key == k) {
            pValue = PTTabRecord(pL->GetDatValue())->pValue;
            break;
        }
    Efficiency = pL->GetCurrentPos() + 1;                   // номер текущей позиции = количеству итераций поиска
    if (pValue == NULL)
        SetRetCode(TabNoRec);
    else 
        SetRetCode(TabOK);

    return pValue;
}

void TListHash::InsRecord(TKey k, PTDatValue pVal) { // вставить запись
    CurrList = HashFunc(k) % TabSize;
    pList[CurrList]->InsLast(new TTabRecord(k, pVal));
    DataCount++;
    Efficiency++;
}       /*================================================*/

void TListHash::DelRecord(TKey k) {
    PTDatValue temp = FindRecord(k);
    PTDatList pL = pList[CurrList];
    for (pL->Reset(); !pL->IsListEnded(); pL->GoNext()) {
        ++Efficiency;
        if (PTTabRecord(pL->GetDatValue())->key == k) {
            pL->DelCurrent();
            --DataCount;
            break;
        }
    }
}       /*================================================*/

int TListHash::Reset() { // установить на первую запись
    CurrList = 0;
    pList[CurrList]->Reset();
    return IsTabEnded();
}       /*================================================*/

int TListHash::IsTabEnded() const {
    return CurrList >= TabSize;
}       /*================================================*/

int TListHash::GoNext() { // переход к следующей записи
    if (!pList[CurrList]->IsListEnded())
        pList[CurrList]->GoNext();

    while (pList[CurrList]->IsListEnded()) {
        CurrList = (CurrList + 1) % TabSize;
        pList[CurrList]->Reset();
    }
    
    return IsTabEnded();
}       /*================================================*/

TKey TListHash::GetKey() const {
    if ((CurrList < 0) || (CurrList >= TabSize))
        return std::string("");

    PTTabRecord pRec = PTTabRecord(pList[CurrList]->GetDatValue());
    return (pRec == NULL) ? NULL : pRec->key;
}       /*================================================*/

PTDatValue TListHash::GetValuePTR() const {
    if ((CurrList < 0) || (CurrList >= TabSize))
        return NULL;
    
    PTTabRecord pRec = PTTabRecord(pList[CurrList]->GetDatValue());
    return (pRec == NULL) ? NULL : pRec->pValue;
}       /*================================================*/
