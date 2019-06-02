// Абстрактный базовый класс содержит спецификации методов таблицы.

#pragma once

#include "ttabrecord.h"
#include "tdatacom.h"

#define TabOK          0  // ошибок нет
#define TabEmpty    -101  // таблица пуста
#define TabFull     -102  // таблица заполнена
#define TabNoRec    -103  // нет записи
#define TabRecDbl   -104  // дублирование записи
#define TabNoMem    -105  // нет памяти 

class  TTable : public TDataCom  {
  protected:
    int DataCount;                                         // количество записей в таблице
    int Efficiency;                                        // показатель эффективности выполнения операции

  public:
    TTable() { DataCount = 0; Efficiency = 0;}             // конструктор
    virtual ~TTable() {};                                  // деструктор

    // информационные методы
    int GetDataCount () const { return DataCount; }        // к-во записей
    int GetEfficiency () const { return Efficiency; }      // эффективность
    void ResetEfficiency() { Efficiency = 0; }
    bool IsEmpty () const { return DataCount == 0; }        // пуста?
    virtual bool IsFull () const = 0;                       // заполнена?

    // доступ
    virtual TKey GetKey () const = 0;
    virtual PTDatValue GetValuePTR () const = 0;

    // основные методы
    virtual PTDatValue FindRecord (TKey k) = 0;             // найти запись
    virtual void InsRecord (TKey k, PTDatValue pVal) = 0;   // вставить
    virtual void DelRecord (TKey k) = 0;                    // удалить запись

    // навигация
    virtual int Reset () = 0;                               // установить на первую запись
    virtual int IsTabEnded () const = 0;                    // таблица завершена?
    virtual int GoNext () = 0;                              // переход к следующей записи
    // (=1 после применения для последней записи таблицы)
};
