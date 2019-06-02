#ifndef __LISTHASH_H__
#define __LISTHASH_H__

#include "TDatList.h"
#include "THashTable.h"

#define TabMaxSize 1000

class  TListHash : public THashTable {
protected:
	PTDatList *pList; // ������ ��� ������� ���������� �� ������ ������� 
	int TabSize;      // ������ ������� ����������
	int CurrList;     // ������, � ������� ���������� �����
public:
	TListHash(int Size = TabMaxSize); // �����������
	~TListHash();
	// �������������� ������
	virtual int IsFull() const; // ���������?
	// ������
	virtual TKey GetKey() const;
	virtual PTDatValue GetValuePTR() const;
	// �������� ������
	virtual PTDatValue FindRecord(TKey k); // ����� ������
	virtual void InsRecord(TKey k, PTDatValue pVal = nullptr); // ��������
	virtual void DelRecord(TKey k);        // ������� ������
	// ���������
	virtual int Reset();   // ���������� �� ������ ������
	virtual int IsTabEnded() const; // ������� ���������?
	virtual int GoNext(); // ������� � ��������� ������
	//(=1 ����� ���������� ��� ��������� ������ �������)
};

#endif