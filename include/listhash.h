#ifndef __listhash_h
#define __listhash_h

#include "TDatList.h"
#include "hashtab.h"

#define TabMaxSize 25

class ListHash : public HashTable {
protected:
	PTDatList * pList;
	int TabSize;
	int CurrList;
public:
	ListHash(int Size = TabMaxSize);
	~ListHash();
	// �������������� ������
	virtual int IsFull() const;
	// �������� ������
	virtual PTDatValue FindRecord(TKey k);
	virtual void InsRecord(TKey k, PTDatValue pVal);
	virtual void DelRecord(TKey k);
	// ���������
	virtual int Reset();
	virtual int GoNext();
	virtual int IsTabEnded() const;
	// ������
	virtual TKey GetKey()const;
	virtual PTDatValue GetValuePtr()const;
};
#endif
