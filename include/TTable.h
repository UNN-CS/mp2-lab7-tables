#pragma once
#include "tdatacom.h"
#include "TTabRecord.h"

#define TabOK 0
#define TabEmpty -101
#define TabFull -102
#define TabNoRec -103
#define TabRecDbl -104 // double rec
#define TabNoMem -105

class  TTable : public TDataCom  {
  protected:
    int DataCount;  // количество записей в таблице
    int Efficiency; // показатель эффективности выполнения операции
  public:
    TTable() { DataCount=0; Efficiency=0;} // конструктор
    virtual ~TTable( ) {}; // деструктор
    // информационные методы
    int GetDataCount ( ) const {return DataCount;}    // к-во записей
    int GetEfficiency ( ) const {return Efficiency;} // эффективность
    int IsEmpty ( ) const {return DataCount == 0;}   //пуста?
    virtual int IsFull ( ) const =0;                 // заполнена?
    // доступ
    virtual TKey GetKey (void) const=0;
    virtual PTDatValue GetValuePTR (void) const =0;
    // основные методы
    virtual PTDatValue FindRecord (TKey k) =0; // найти запись
    virtual void InsRecord (TKey k, PTDatValue pVal ) =0; // вставить
    virtual void DelRecord (TKey k) =0;        // удалить запись
    // навигация
    virtual int Reset (void) =0; // установить на первую запись
    virtual int IsTabEnded (void) const=0; // таблица завершена?
    virtual int GoNext (void) =0; // переход к следующей записи
    // (=1 после применения для последней записи таблицы)
    // printing table
    friend ostream& operator<<(ostream& os, TTable& tab) {
        cout << "Table printing" << endl;
        for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext()) {
            os << "Key: " << tab.GetKey() << " Val: " << *tab.GetValuePTR() << endl;
        }
        return os;
    }
};