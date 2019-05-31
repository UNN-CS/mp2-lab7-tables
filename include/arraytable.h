#ifndef ARRAYTABLE_H_
#define ARRAYTABLE_H_
#include "table.h"

enum TDataPos {FIRST_POS, CURRENT_POS, LAST_POS};

class TArrayTable : public TTable {
 protected:
    PTTabRecord *pRecs; // память для записей таблицы
    int TabSize;        // макс. возм.количество записей в таблице
    int CurrPos;        // номер текущей записи (нумерация с 0)
 public:
    TArrayTable(int Size = TabMaxSize); // конструктор
    ~TArrayTable() {};                // деструктор
    // информационные методы
    virtual int IsFull() const override; // заполнена?
    int GetTabSize() const;      // к-во записей
    // доступ
    virtual TKey GetKey() const override;
    virtual PTDatValue GetValuePtr() const override;
    virtual TKey GetKey(TDataPos mode) const;
    virtual PTDatValue GetValuePtr(TDataPos mode) const;
    // основные методы
    virtual PTDatValue FindRecord(TKey k) = 0; // найти запись
    virtual void InsRecord(TKey k, PTDatValue pVal) = 0; // вставить
    virtual void DelRecord(TKey k) = 0;        // удалить запись
    //навигация
    virtual int Reset() override;   // установить на первую запись
    virtual int IsTabEnded() const override; // таблица завершена?
    virtual int GoNext() override; // переход к следующей записи
    //(=1 после применения для последней записи таблицы)
    virtual int SetCurrentPos (int pos);// установить текущую запись
    int GetCurrentPos() const;     //получить номер текущей записи
    friend class TSortTable;
};

#endif // ARRAYTABLE_H_
