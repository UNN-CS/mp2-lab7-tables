#ifndef __DATVALUE_H
#define __DATVALUE_H
#include <iostream>

typedef TDatValue *PTDatValue;

class TDatValue
{
public:
	virtual TDatValue * GetCopy() = 0;
	~TDatValue() {}
};
#endif
