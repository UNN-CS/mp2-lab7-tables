// Класс для таблиц с вычислимым входом, использующий для разрешения коллизий открытое перемешивание

#pragma once

#include "thashtable.h"
#include "ttable.h"

#define TabMaxSize 25
#define TabHashStep 5


class  TArrayHash : public THashTable {
  protected:
    PTTabRecord *pRecs;                                             // память для записей таблицы
    int tabSize;                                                    // макс. возм. к-во записей
    int hashStep;                                                   // шаг вторичного перемешивания
    int freePos;                                                    // первая свободная строка, обнаруженная при поиске
    int currPos;                                                    // строка памяти при завершении поиска
    PTTabRecord pMark;                                              // маркер для индикации строк с удаленными записями
    int GetNextPos(int pos){ return (pos + hashStep) % tabSize; }   // откр. перем.

  public:
    TArrayHash(int size = TabMaxSize, int step = TabHashStep);      // конструктор
    ~TArrayHash();

    // информационные методы
    virtual bool IsFull () const;                                    // заполнена?

    // доступ
    virtual TKey GetKey () const;
    virtual PTDatValue GetValuePTR () const;

    // основные методы
    virtual PTDatValue FindRecord (TKey k);                         // найти запись
    virtual void InsRecord (TKey k, PTDatValue pVal);               // вставить
    virtual void DelRecord (TKey k);                                // удалить запись

    // навигация
    virtual int Reset ();                                           // установить на первую запись
    virtual int IsTabEnded () const;                                // таблица завершена?
    virtual int GoNext ();                                          // переход к следующей записи
    //(=1 после применения для последней записи таблицы)
};
