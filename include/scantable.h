#ifndef SCANTABLE_H_
#define SCANTABLE_H_
#include "arraytable.h"

class TScanTable : public TArrayTable {
 public:
    TScanTable(int Size = TabMaxSize): TArrayTable(Size) {};//конструктор
    // основные методы
    virtual PTDatValue FindRecord(TKey k) override; //найти запись
    virtual void InsRecord(TKey k, PTDatValue pVal) override; //вставить
    virtual void DelRecord(TKey k) override; //удалить запись
};

#endif // SCANTABLE_H_
