#ifndef __T_TAB_RECORD__
#define __T_TAB_RECORD__

#include "tdatvalue.h"
#include <iostream>

typedef std::string TKey;  // тип ключа записи
// Класс объектов-значений для записей таблицыclass


class TTabRecord {
  protected:    // поля    TKey Key;   // ключ записи
    PTDatValue pValue;   // указатель на значение
	TKey key;
  public:  // методы
	TTabRecord(TKey k = "", PTDatValue pVal = NULL);// конструктор
    void SetKey(TKey k);// установить значение ключа
    TKey GetKey(void);  // получить значение ключа
    void SetValuePtr(PTDatValue p);// установить указатель на данные
    PTDatValue GetValuePTR (void); // получить указатель на данные
    virtual TDatValue * GetCopy(); // изготовить копию
    TTabRecord & operator = (TTabRecord &tr);// присваивание
    virtual int operator == (const TTabRecord &tr); // сравнение =
    virtual int operator < (const TTabRecord &tr);  // сравнение «<»
    virtual int operator > (const TTabRecord &tr);  // сравнение «>»
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

#endif //__T_TAB_RECORD__