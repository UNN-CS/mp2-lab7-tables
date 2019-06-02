// TTabRecord.h 
#ifndef TTAB_RECORD_H
#define TTAB_RECORD_H
#include <string>
#include "TDatValue.h"

typedef std::string TKey;     // тип ключа записи

// Класс объектов-значений для записей таблицыclass TTabRecord : public TDatValue {  protected:    // поля    TKey Key;   // ключ записи
class TTabRecord : public TDatValue {
protected:
    TKey Key;
    PTDatValue pValue;   // указатель на значение
public:  // методы
    TTabRecord(TKey k = "", PTDatValue pVal = nullptr) { // конструктор
        Key = k; pValue = pVal;
    }
    void SetKey(TKey k) { Key = k; }// установить значение ключа
    TKey GetKey() { return Key; }  // получить значение ключа
    void SetValuePtr(PTDatValue p) { pValue = p; }// установить указатель на данные
    PTDatValue GetValuePTR() { return pValue; } // получить указатель на данные
    virtual TDatValue * GetCopy(); // изготовить копию
    TTabRecord & operator = (TTabRecord &tr) { // присваивание
        Key = tr.Key; pValue = tr.pValue;
        return *this;
    }
    virtual int operator == (const TTabRecord &tr) { // сравнение =
        return Key == tr.Key;
    }
    virtual int operator < (const TTabRecord &tr) {  // сравнение «<»
        return Key < tr.Key;
    }
    virtual int operator > (const TTabRecord &tr) {  // сравнение «>»
        return Key > tr.Key;
    }

//дружественные классы для различных типов таблиц, см. далее
    friend class TArrayTable;
    friend class TScanTable;
    friend class TSortTable;
    friend class TTreeNode;
    friend class TTreeTable;
    friend class TArrayHash;
    friend class TListHash;
};
typedef TTabRecord *PTTabRecord;
#endif
