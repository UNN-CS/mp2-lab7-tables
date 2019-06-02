#ifndef __STUDENTRECORD_H__
#define __STUDENTRECORD_H__

#include "TDatValue.h"
#include <vector>

class TStudRec;

typedef TStudRec* PTStudRec;

class TStudRec : public TDatValue {
protected:
	static int marks_number;
	int* marks;
public:
	TStudRec();
	TStudRec(int* _marks);
	~TStudRec();
	TStudRec(const TStudRec& tsr);
	virtual TDatValue* GetCopy();
	void SetMarks(int* _marks);
	int* GetMarks();
};

#endif