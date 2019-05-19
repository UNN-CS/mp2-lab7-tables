#ifndef __T_SCAN_TABLE_H__
#define __T_SCAN_TABLE_H__

#include "tarraytable.h"

class  TScanTable: public TArrayTable {
  public:
    TScanTable(int Size=TabMaxSize): TArrayTable(Size){};//конструктор
    // основные методы
    virtual PTDatValue FindRecord (TKey k) ;//найти запись
    virtual void InsRecord (TKey k, PTDatValue pVal ) ;//вставить
    virtual void DelRecord (TKey k) ;//удалить запись

};

#endif // __T_SCAN_TABLE_H__
