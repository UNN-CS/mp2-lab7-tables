#ifndef __ARRAYTABLE_H__
#define __ARRAYTABLE_H__

#include "TTable.h"

#define TabMaxSize 1000

enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class  TArrayTable : public TTable {
protected:
	PTTabRecord *pRecs; // память для записей таблицы
	int TabSize;        // макс. возм.количество записей в таблице
	int CurrPos;        // номер текущей записи (нумерация с 0)
public:
	TArrayTable(int Size = TabMaxSize); // конструктор
	~TArrayTable();                // деструктор
	// информационные методы
	virtual int IsFull() const; // заполнена?
	int GetTabSize() const;      // к-во записей
	// доступ
	virtual TKey GetKey() const;
	virtual PTDatValue GetValuePTR() const;
	virtual TKey GetKey(TDataPos mode) const;
	virtual PTDatValue GetValuePTR(TDataPos mode) const;
	// основные методы
	virtual PTDatValue FindRecord(TKey k) = 0; // найти запись
	virtual void InsRecord(TKey k, PTDatValue pVal) = 0; // вставить
	virtual void DelRecord(TKey k) = 0;        // удалить запись
	//навигация
	virtual int Reset();   // установить на первую запись
	virtual int IsTabEnded() const; // таблица завершена?
	virtual int GoNext(); // переход к следующей записи
	//(=1 после применения для последней записи таблицы)
	virtual int SetCurrentPos(int pos);// установить текущую запись
	int GetCurrentPos() const;     //получить номер текущей записи
	friend TSortTable;
};

#endif