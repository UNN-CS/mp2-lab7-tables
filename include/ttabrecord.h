#ifndef __TTABRECORD_H
#define __TTABRECORD_H

#include "datvalue.h"

using namespace std;

typedef string TKey; // тип ключа записи

// Класс объектов-значений для записей таблицы
class TTabRecord : public TDatValue {  
 protected:    // поля    
    TKey Key;   // ключ записи
    PTDatValue pValue;   // указатель на значение
 public:  // методы
     TTabRecord(TKey k = "", PTDatValue pVal = nullptr) : Key(k), pValue(pVal) {} // конструктор
     void SetKey(TKey k) { Key = k; } // установить значение ключа
     TKey GetKey(void) { return Key; }  // получить значение ключа
     void SetValuePtr(PTDatValue p) { pValue = p; } // установить указатель на данные
     PTDatValue GetValuePtr(void) { return pValue; } // получить указатель на данные
     virtual TDatValue * GetCopy(); // изготовить копию
     TTabRecord & operator = (TTabRecord &tr);// присваивание
     virtual int operator == (const TTabRecord &tr) { return Key == tr.Key; } // сравнение =
     virtual int operator < (const TTabRecord &tr) { return Key > tr.Key; }  // сравнение «<»
     virtual int operator > (const TTabRecord &tr) { return Key < tr.Key; }  // сравнение «>»
  //дружественные классы для различных типов таблиц, см. далее
     friend class TArrayTable;
     friend class TScanTable;
     friend class TSortTable;
     friend class TTreeNode;
     friend class TTreeTable;
     friend class TArrayHash;
     friend class TListHash;
};

typedef TTabRecord* PTTabRecord;

#endif 

