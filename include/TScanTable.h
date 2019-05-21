#include "TTable.h"
#include "TTabRecord.h"
#include "TArrayTable.h"

class TScanTable : public TArrayTable
{
public:
    TScanTable(int Size = TabMaxSize) : TArrayTable(Size){}; //конструктор
    // основные методы
    virtual PTDatValue FindRecord(TKey k);           //найти запись
    virtual void InsRecord(TKey k, PTDatValue pVal); //вставить
    virtual void DelRecord(TKey k);                  //удалить запись
};