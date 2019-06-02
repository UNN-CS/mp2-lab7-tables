// TListHash.h
#ifndef _LISTHASH_H
#define _LISTHASH_H

#include "THashTable.h"
#include "TDatList.h"
#define TabMaxSize 25
class  TListHash : public THashTable {
protected:
    PTDatList *pList; // память для массива указателей на списки записей 
    int TabSize;      // размер массива указателей
    int CurrList;     // список, в котором выполнялся поиск
public:
    TListHash(int Size = TabMaxSize); // конструктор
    ~TListHash();
    // информационные методы
    virtual int IsFull() const; // заполнена?
    // доступ
    virtual TKey GetKey() const;
    virtual PTDatValue GetValuePTR() const;
    // основные методы
    virtual PTDatValue FindRecord(TKey k); // найти запись
    virtual void InsRecord(TKey k, PTDatValue pVal); // вставить
    virtual void DelRecord(TKey k);        // удалить запись
    // навигация
    virtual int Reset();   // установить на первую запись
    virtual int IsTabEnded() const; // таблица завершена?
    virtual int GoNext(); // переход к следующей записи
    //(=1 после применения для последней записи таблицы)
};

#endif