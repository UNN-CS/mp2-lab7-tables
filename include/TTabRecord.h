#ifndef __TRECORD_H
#define __TRECORD_H
#include <iostream>
#include "TDatValue.h"
#include <string>
using namespace std;

typedef string TKey;

class TRecord : public TDatValue
{
protected:
	TKey Key; // ключ записи
	PTDatValue pValue;// указатель на значение
public:

	TRecord(TKey k = "", PTDatValue pVal = NULL) :Key(k), pValue(pVal) {}
	void SetKey(TKey k) { Key = k; }
	TKey GetKey() { return Key; }
	void SetValuePtr(PTDatValue p) { pValue = p; }
	PTDatValue GetValuePtr() { return pValue; }
	virtual TDatValue* GetCopy(); // изготовить копию
	TRecord& operator= (TRecord& r)
	{
		Key = r.Key;
		pValue = r.pValue;
		return *this;
	}
	virtual int operator== (const TRecord& r) { return (Key == r.Key); }
	virtual int operator< (const TRecord& r) { return Key > r.Key; }
	virtual int operator> (const TRecord& r) { return Key < r.Key; }
	virtual void Print() {
		pValue->Print();
	}
	friend ostream& operator<<(ostream& ost,const TRecord& r)
	{
		ost << r.Key ;
		return ost;
	}
	friend class TArrayTable;
	friend class TScanTable;
	friend class TSortTable;
	friend class TTreeNode;
	friend class TTreeTable;
	friend class TArrayHash;
	friend class TListHash;
};
typedef TRecord* PTRecord;
#endif