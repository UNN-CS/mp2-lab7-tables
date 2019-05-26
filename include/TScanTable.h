#ifndef __TSCAN_TABLE_H__
#define __TSCAN_TABLE_H__

#include "TArrayTable.h"

class  TScanTable : public TArrayTable {
public:
	TScanTable(int Size = TabMaxSize) : TArrayTable(Size) {};
	virtual PTDatValue FindRecord(TKey k);
	virtual void InsRecord(TKey k, PTDatValue pVal);
	virtual void DelRecord(TKey k);

};

#endif // __TSCAN_TABLE_H__