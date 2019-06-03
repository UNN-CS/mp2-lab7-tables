// Базовый класс для таблиц с вычислимым входом

#pragma once

#include "ttable.h"

class  THashTable : public TTable {
  protected:
    virtual unsigned long HashFunc(const TKey key);  // hash-функция

  public:
    THashTable() : TTable() {}                       //конструктор
};
