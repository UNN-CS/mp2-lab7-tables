#pragma once

#include "TArrayTable.h"

class TScanTable : public TArrayTable
{
public:
  TScanTable(int size = TabMaxSize) : TArrayTable(size) {}; //конструктор
  // основные методы
  virtual PTDatValue FindRecord(TKey k);           //найти запись
  virtual void InsRecord(TKey k, PTDatValue pVal); //вставить
  virtual void DelRecord(TKey k);                  //удалить запись
};