#include "TScanTable.h"

PTDatValue TScanTable :: FindRecord (TKey k) {
	for (int i = 0; i < GetDataCount(); i++) {
		CurrPos = i;
		if (GetKey(CURRENT_POS) == k) return GetValuePTR(CURRENT_POS);
	}
	throw -1;
}
void TScanTable :: InsRecord (TKey k, PTDatValue pVal ) {
	if (IsFull()) throw -1; // запись невозможна, таблица заполнена
	for (int i = 0; i < GetDataCount(); i++) {
		CurrPos = i;
		if (GetKey(CURRENT_POS) == k) throw -1; // запись с таким ключом существует
	}
	pRecs[DataCount++] = new TTabRecord(k, pVal);
}
void TScanTable :: DelRecord (TKey k) {
	int flag = 0;
	for (int i = 0; i < GetDataCount(); i++) {
		CurrPos = i;
		if (GetKey(CURRENT_POS) == k) {
			flag++;
			break;
		}
	}
	if (flag == 0) 
		throw -1; // записи с таким ключом не существует
	if (GetValuePTR(CURRENT_POS) != nullptr) delete pRecs[GetCurrentPos()]->pValue;
	delete pRecs[GetCurrentPos()]; 
	pRecs[GetCurrentPos()] = nullptr;
	// смещаем последний элемент на пустое место
	pRecs[GetCurrentPos()] = pRecs[DataCount - 1];
    pRecs[DataCount - 1] = nullptr;
    DataCount--;
}