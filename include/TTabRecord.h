#pragma once
#include "DatValue.h"
#include <iostream>
#include <string>
using namespace std;

typedef string TKey;     // тип ключа записи
// Класс объектов-значений для записей таблицы
class TTabRecord : public TDatValue {  protected:    // поля    
    TKey Key;   // ключ записи
    PTDatValue pValue;   // указатель на значение
  public:  // методы
    TTabRecord(TKey k = "", PTDatValue pVal = NULL); // конструктор 
    void SetKey(TKey k) {
        Key = k;
    }; // установить значение ключа
    TKey GetKey(void) {
        return Key;
    };  // получить значение ключа
    void SetValuePtr(PTDatValue p) { 
        pValue = p;
    }; // установить указатель на данные
    PTDatValue GetValuePTR(void) {
        return pValue;
    }; // получить указатель на данные
    virtual TDatValue * GetCopy(); // изготовить копию
    TTabRecord & operator= (TTabRecord &tr); // присваивание
    virtual int operator== (const TTabRecord &tr); // сравнение =
    virtual int operator< (const TTabRecord &tr);  // сравнение «<»
    virtual int operator> (const TTabRecord &tr);  // сравнение «>»
protected:
    virtual void Print(ostream& os);
  //дружественные классы для различных типов таблиц, см. далее
  friend class TArrayTable;
  friend class TScanTable;
  friend class TSortTable;
  friend class TTreeNode;
  friend class TTreeTable;
  friend class TArrayHash;
  friend class TListHash;
};

typedef TTabRecord * PTTabRecord;