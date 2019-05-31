#ifndef __arrhash_h
#define __arrhash_h

#include "hashtab.h"

#define TabMaxSize 25
#define TabHashStep 5
class ArrayHash :public HashTable {
protected:
	PTRecord * pRecs; // ������ ��� ������� �������
	int TabSize; // ����������� ��������� ���-�� ������� 
	int HashStep; // ��� ���������� �������������
	int FreePos; // ������ ��������� ������, ������������ ��� ������
	int CurrPos; // ������ ������ ��� ���������� ������
	PTRecord pMark; // ������ ��� ������������� ����� � ���������� ��������
	// ������� ��������� �������������
	int GetNextPos(int pos) { return (pos + HashStep) % TabSize; }
public:
	ArrayHash(int Size = TabMaxSize, int Step = TabHashStep);
	~ArrayHash();
	// �������������� ������
	virtual int IsFull() const { return DataCount >= TabSize; }
	//�������� ������ 
	virtual PTDatValue FindRecord(TKey key);
	virtual void InsRecord(TKey key, PTDatValue pVal);
	virtual void DelRecord(TKey k);
	// ��������� 
	virtual int Reset();
	virtual int IsTabEnded() const;
	virtual int GoNext();
	// ������ 
	virtual TKey GetKey() const;
	virtual PTDatValue GetValuePtr() const;
};
#endif