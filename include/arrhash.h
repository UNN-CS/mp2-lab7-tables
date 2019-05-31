#ifndef __arrhash_h
#define __arrhash_h

#include "hashtab.h"

#define TabMaxSize 25
#define TabHashStep 5
class ArrayHash :public HashTable {
protected:
	PTRecord * pRecs; // память для записей таблицы
	int TabSize; // максимально возможное кол-во записей 
	int HashStep; // шаг вторичного перемешивания
	int FreePos; // первая свободная строка, обнаруженная при поиске
	int CurrPos; // строка памяти при завершении поиска
	PTRecord pMark; // маркер для инициализации строк с удаленными записями
	// функция открытого перемешивания
	int GetNextPos(int pos) { return (pos + HashStep) % TabSize; }
public:
	ArrayHash(int Size = TabMaxSize, int Step = TabHashStep);
	~ArrayHash();
	// информационные методы
	virtual int IsFull() const { return DataCount >= TabSize; }
	//основные методы 
	virtual PTDatValue FindRecord(TKey key);
	virtual void InsRecord(TKey key, PTDatValue pVal);
	virtual void DelRecord(TKey k);
	// навигация 
	virtual int Reset();
	virtual int IsTabEnded() const;
	virtual int GoNext();
	// доступ 
	virtual TKey GetKey() const;
	virtual PTDatValue GetValuePtr() const;
};
#endif