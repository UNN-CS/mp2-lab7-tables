#ifndef _ARRAHASH_H
#define _ARRAHASH_H

#include "THashTable.h"

#define TabMaxSize 40
#define TabHashStep 3

class  TArrayHash : public THashTable {
protected:
	PTTabRecord *pRecs; // память для записей таблицы
	int TabSize;        // макс. возм. к-во записей
	int HashStep;       // шаг вторичного перемешивания
	int FreePos;        // первая свободная строка, обнаруженная при поиске
	int CurrPos;        // строка памяти при завершении поиска
	PTTabRecord pMark;  // маркер для индикации строк с удаленными записями
	int GetNextPos(int pos) { return (pos + HashStep) % TabSize; };// откр. перем.
public:
	TArrayHash(int Size = TabMaxSize, int Step = TabHashStep); // конструктор
	~TArrayHash();

	// информационные методы
	virtual int IsFull() const { return DataCount >= TabSize; } // заполнена?	

	// доступ
	virtual TKey GetKey(void) const;
	virtual PTDatValue GetValuePTR(void) const;

	// основные методы
	virtual PTDatValue FindRecord(TKey k); // найти запись
	virtual void InsRecord(TKey k, PTDatValue pVal); // вставить
	virtual void DelRecord(TKey k);        // удалить запись

	// навигация
	virtual int Reset(void);   // установить на первую запись
	virtual int IsTabEnded(void) const; // таблица завершена?
	virtual int GoNext(void); // переход к следующей записи
							  //(=1 после применения для последней записи таблицы)
};
#endif