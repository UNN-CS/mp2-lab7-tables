#ifndef __SCANTAB_H
#define __SCANTAB_H

#include "TArrayTable.h"    

class TScanTable : public TArrayTable {
 public:
 TScanTable (int size = TabMaxSize) : TArrayTable(size) {}
 // основные методы
 virtual PTDatValue FindRecord (TKey k); // найти запись и вернуть указатель на значение
 virtual void InsRecord (TKey k, PTDatValue val); // вставить 
 virtual void DelRecord (TKey k); // удалить запись
};
#endif                                                                                                                                                                                                                                                                                                                                                               