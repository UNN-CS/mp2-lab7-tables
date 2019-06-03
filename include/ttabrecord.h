// Класс объектов-значений для записей таблицы

#pragma once

#include <string>
#include "datavalue.h"

typedef std::string TKey;

class TTabRecord;
typedef TTabRecord *PTTabRecord;

class TTabRecord : public TDatValue {
  protected:
    TKey key;
    PTDatValue pValue;                              // указатель на значение

  public:  
    // методы
    TTabRecord (TKey k="", PTDatValue pVal = NULL); // конструктор 
    void SetKey(TKey k);                            // установить значение ключа
    TKey GetKey();                                  // получить значение ключа
    void SetValuePtr(PTDatValue p);                 // установить указатель на данные
    PTDatValue GetValuePTR ();                      // получить указатель на данные
    virtual TDatValue * GetCopy();                  // изготовить копию
    TTabRecord & operator = (TTabRecord &tr);       // присваивание
    virtual bool operator == (const TTabRecord &tr); // сравнение =
    virtual bool operator < (const TTabRecord &tr);  // сравнение «<»
    virtual bool operator > (const TTabRecord &tr);  // сравнение «>»

  //дружественные классы для различных типов таблиц
  friend class TArrayTable;
  friend class TScanTable;
  friend class TSortTable;
  friend class TTreeNode;
  friend class TTreeTable;
  friend class TArrayHash;
  friend class TListHash;
};
