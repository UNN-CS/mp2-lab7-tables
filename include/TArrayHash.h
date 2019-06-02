// таблицы с вычислимым входом - открытое перемешивание
#ifndef _ARRAYHASH_H
#define _ARRAYHASH_H

#include "THashTable.h"

#define TabMaxSize 25
#define TabHashStep 5

class  TArrayHash : public THashTable {
protected:
    PTTabRecord * pRecs; // память для записей таблицы
    int TabSize;         // макс возм кол-во записей
    int HashStep;        // шаг втроичного перемешивания
    int FreePos;         // первая свободная строка, обнаруженная при поиске
    int CurrPos;         // строка памяти при завершении поиска
    PTTabRecord pMark;   // маркер для строк с удаленными записями
	// функция открытого перемешивания
    int GetNextPos(int pos) { return (pos + HashStep) % TabSize; };
public:
    TArrayHash(int Size = TabMaxSize, int Step = TabHashStep);
    ~TArrayHash();
	//иниформационные методы
    virtual int IsFull() const { return DataCount >= TabSize; }
	// основные методы
    virtual PTDatValue FindRecord(TKey k);
    virtual void InsRecord(TKey k, PTDatValue pVal);
    virtual void DelRecord(TKey k);
	//доступ
    virtual TKey GetKey() const;
    virtual PTDatValue GetValuePTR() const;
	//навигация
    virtual int Reset();
    virtual int IsTabEnded() const;
    virtual int GoNext();
};

#endif 