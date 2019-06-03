// TArrayTable.h
#ifndef _ARRAY_TABLE_H
#define _ARRAY_TABLE_H
#include "TTabRecord.h"
#include "TTable.h"
#define TabMaxSize 25
enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class  TArrayTable : public TTable {
protected:
    PTTabRecord *pRecs; // память для записей таблицы
    int TabSize;        // макс. возм.количество записей в таблице
    int CurrPos;        // номер текущей записи (нумерация с 0)
public:
    TArrayTable(int Size = TabMaxSize) { // конструктор
        pRecs = new PTTabRecord[Size];
        for (int i = 0; i < Size; ++i) pRecs[i] = nullptr;
        TabSize = Size; DataCount = CurrPos = 0;
    }

    ~TArrayTable() {
        for (int i = 0; i < DataCount; ++i)
            delete pRecs[i];
        delete[] pRecs;
    }

    // информационные методы
    virtual int IsFull() const { // заполнена?
        return DataCount >= TabSize;
    }
    
    int GetTabSize() const { return TabSize; }      // к-во записей
    
    // доступ
    virtual TKey GetKey() const { return GetKey(CURRENT_POS); }
    virtual PTDatValue GetValuePTR() const { return GetValuePTR(CURRENT_POS); }
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
    int GetCurrentPos() const { return CurrPos; }     //получить номер текущей записи
    friend TSortTable;
};

#endif