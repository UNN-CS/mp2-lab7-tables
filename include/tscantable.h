#ifndef __TSCANTABLE_H__
#define __TSCANTABLE_H__
#include "tarraytable.h"

class TScanTable : public TArrayTable {
 public:
    TScanTable(int Size = TabMaxSize): TArrayTable(Size) {};//конструктор
    // основные методы
    virtual PTDatValue FindRecord(TKey k) override; //найти запись
    virtual void InsRecord(TKey k, PTDatValue pVal) override; //вставить
    virtual void DelRecord(TKey k) override; //удалить запись
};

#endif // __TSCANTABLE_H__
