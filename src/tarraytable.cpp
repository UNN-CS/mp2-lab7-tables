#include "tarraytable.h"


TArrayTable::TArrayTable(int size) : TTable() {
    currPos = 0;
    tabSize = size;

    pRecs = new PTTabRecord[tabSize];

    for (int i = 0; i < size; i++)
        pRecs[i] = nullptr;
}       /*================================================*/

TArrayTable::~TArrayTable() {
    for (int i = 0; i < tabSize; i++)
        delete pRecs[i];

    delete[] pRecs;
}       /*================================================*/

bool TArrayTable::IsFull() const {
    return currPos == tabSize;
}       /*================================================*/

int TArrayTable::GetTabSize() const {
    return tabSize;
}       /*================================================*/

int TArrayTable::GetCurrentPos() const {
    return currPos;
}       /*================================================*/

TKey TArrayTable::GetKey(TDataPos mode) const { // значение
    int pos =- 1;

    if (!IsEmpty()) {
        switch (mode) {
            case FIRST_POS: pos = 0;                break;
            case LAST_POS:  pos = DataCount - 1;    break;
            default:        pos = currPos;          break;
        }
    }

    return (pos == -1) ? std::string("") : pRecs[pos]->key; 
}       /*================================================*/

PTDatValue TArrayTable::GetValuePTR (TDataPos mode) const { // значение
    int pos =- 1;

    if (!IsEmpty()) {
        switch (mode) {
            case FIRST_POS: pos = 0;                break;
            case LAST_POS:  pos = DataCount - 1;    break;
            default:        pos = currPos;          break;
        }
    }

    return (pos == -1) ? NULL : pRecs[pos]->pValue;
}       /*================================================*/

TKey TArrayTable::GetKey () const {
    if (IsEmpty())
        throw ("tab is empty");
    return pRecs[currPos]->GetKey();
}       /*================================================*/

PTDatValue TArrayTable::GetValuePTR() const { // значение 
    if (!IsEmpty())
        return pRecs[currPos]->pValue;

    return NULL;
}       /*================================================*/

int TArrayTable::Reset() { // установить на первую запись
    currPos = 0;
    return IsTabEnded();
}       /*================================================*/

int TArrayTable::IsTabEnded() const { // таблица завершена?
    return currPos >= DataCount;
}       /*================================================*/

int TArrayTable::GoNext() { // переход к следующей записи
    if (!IsTabEnded()) 
        currPos++;

    return IsTabEnded();
}       /*================================================*/

int TArrayTable::SetCurrentPos(int pos) {
    currPos = ((pos > -1) && (pos < DataCount)) ? pos : 0;
    return IsTabEnded();
}       /*================================================*/
