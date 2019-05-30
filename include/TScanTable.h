#ifndef __T_SCAN_TABLE_H__
#define __T_SCAN_TABLE_H__

#include "tarraytable.h"

class  TScanTable : public TArrayTable {
public:
	TScanTable(int Size = TabMaxSize) : TArrayTable(Size) {};//êîíñòðóêòîð
															 // îñíîâíûå ìåòîäû
	virtual PTDatValue FindRecord(TKey k);//íàéòè çàïèñü
	virtual void InsRecord(TKey k, PTDatValue pVal);//âñòàâèòü
	virtual void DelRecord(TKey k);//óäàëèòü çàïèñü

};

#endif // __T_SCAN_TABLE_H__