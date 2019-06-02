#ifndef __ARRAYTABLE_H__
#define __ARRAYTABLE_H__

#include "TTable.h"

#define TabMaxSize 1000

enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class  TArrayTable : public TTable {
protected:
	PTTabRecord *pRecs; // ������ ��� ������� �������
	int TabSize;        // ����. ����.���������� ������� � �������
	int CurrPos;        // ����� ������� ������ (��������� � 0)
public:
	TArrayTable(int Size = TabMaxSize); // �����������
	~TArrayTable();                // ����������
	// �������������� ������
	virtual int IsFull() const; // ���������?
	int GetTabSize() const;      // �-�� �������
	// ������
	virtual TKey GetKey() const;
	virtual PTDatValue GetValuePTR() const;
	virtual TKey GetKey(TDataPos mode) const;
	virtual PTDatValue GetValuePTR(TDataPos mode) const;
	// �������� ������
	virtual PTDatValue FindRecord(TKey k) = 0; // ����� ������
	virtual void InsRecord(TKey k, PTDatValue pVal) = 0; // ��������
	virtual void DelRecord(TKey k) = 0;        // ������� ������
	//���������
	virtual int Reset();   // ���������� �� ������ ������
	virtual int IsTabEnded() const; // ������� ���������?
	virtual int GoNext(); // ������� � ��������� ������
	//(=1 ����� ���������� ��� ��������� ������ �������)
	virtual int SetCurrentPos(int pos);// ���������� ������� ������
	int GetCurrentPos() const;     //�������� ����� ������� ������
	friend TSortTable;
};

#endif