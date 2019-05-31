#ifndef __ARRAYTABLE_H
#define __ARRAYTABLE_H

#include "TTable.h"
#define TabMaxSize 25
enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class  TArrayTable : public TTable {
protected:
	PTRecord * pRecs; // память для записей таблицы
	int TabSize;        // макс. возм.количество записей в таблице
	int CurrPos;        // номер текущей записи (нумерация с 0)
public:
	TArrayTable(int Size = TabMaxSize); // конструктор
	~TArrayTable() ;                // деструктор
	 // информационные методы
	virtual int IsFull() const; // заполнена?
	int GetTabSize() const;      // к-во записей
	// доступ
	virtual TKey GetKey(void) const { return GetKey(CURRENT_POS); }
    virtual PTDatValue GetValuePtr() const { return (GetValuePTR(CURRENT_POS)); }
	virtual TKey GetKey(TDataPos mode) const;
	virtual PTDatValue GetValuePTR(TDataPos mode) const;
	// основные методы
	virtual PTDatValue FindRecord(TKey k) = 0; // найти запись
	virtual void InsRecord(TKey k, PTDatValue pVal) = 0; // вставить
	virtual void DelRecord(TKey k) = 0;        // удалить запись
	//навигация
	virtual int Reset(void) { CurrPos = 0; return IsTabEnded(); };   // установить на первую запись
	virtual int IsTabEnded(void) const { return CurrPos >= DataCount; }; // таблица завершена?
	virtual int GoNext(void) { if (!IsTabEnded()) CurrPos++; else CurrPos = 0; cout << "tu"; return IsTabEnded(); }; // переход к следующей записи
							  //(=1 после применения для последней записи таблицы)
	virtual int SetCurrentPos(int pos) { CurrPos = ((pos > -1) && (pos < DataCount)) ? pos : 0; return IsTabEnded(); };// установить текущую запись
	int GetCurrentPos(void) const { return CurrPos; };     //получить номер текущей записи
	friend class SortTable;
};

#endif // !