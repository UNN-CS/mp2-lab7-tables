#ifndef __T_SCAN_TABLE_H__
#define __T_SCAN_TABLE_H__

#include "tarraytable.h"

class TScanTable : public TArrayTable {
public:
	TScanTable(int Size = TabMaxSize) : TArrayTable(Size) {};//êîíñòðóêòîð
															 // îñíîâíûå ìåòîäû
	virtual PTDatValue FindRecord(TKey k) override; //íàéòè çàïèñü
	virtual void InsRecord(TKey k, PTDatValue pVal) override; //âñòàâèòü
	virtual void DelRecord(TKey k) override; //óäàëèòü çàïèñü
};


#endif // __T_SCAN_TABLE_H__