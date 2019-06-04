#ifndef DATVALUE_H_
#define DATVALUE_H_

class TDatValue {
public:
	virtual TDatValue *GetCopy() = 0;
};
typedef TDatValue *PTDatValue;

#endif  // DATVALUE_H_