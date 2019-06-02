#ifndef __SCANTAB_H
#define __SCANTAB_H

#include "TArrayTable.h"

class  TScanTable : public TArrayTable {
public:
	TScanTable(int Size = TabMaxSize) : TArrayTable(Size) {};//êîíñòðóêòîð

	// îñíîâíûå ìåòîäû
	virtual PTDatValue FindRecord(TKey k);//íàéòè çàïèñü
	virtual void InsRecord(TKey k, PTDatValue pVal = nullptr);//âñòàâèòü
	virtual void DelRecord(TKey k);//óäàëèòü çàïèñü
};
#endif 
