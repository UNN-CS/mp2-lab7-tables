#ifndef __DATVALUE_H
#define __DATVALUE_H
#define MemSize 20
#define TextLineLength 20
class TDatValue
{
public:
	virtual TDatValue * GetCopy() = 0;
	virtual void Print() = 0;
	~TDatValue() {}
};

typedef TDatValue *PTDatValue;

#endif // !__DATVALUE_H
