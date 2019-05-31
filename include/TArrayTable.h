#ifndef __ARRAYTABLE_H
#define __ARRAYTABLE_H

#include "TTable.h"
#define TabMaxSize 25
enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class  TArrayTable : public TTable {
protected:
	PTRecord * pRecs; // ������ ��� ������� �������
	int TabSize;        // ����. ����.���������� ������� � �������
	int CurrPos;        // ����� ������� ������ (��������� � 0)
public:
	TArrayTable(int Size = TabMaxSize); // �����������
	~TArrayTable() ;                // ����������
	 // �������������� ������
	virtual int IsFull() const; // ���������?
	int GetTabSize() const;      // �-�� �������
	// ������
	virtual TKey GetKey(void) const { return GetKey(CURRENT_POS); }
    virtual PTDatValue GetValuePtr() const { return (GetValuePTR(CURRENT_POS)); }
	virtual TKey GetKey(TDataPos mode) const;
	virtual PTDatValue GetValuePTR(TDataPos mode) const;
	// �������� ������
	virtual PTDatValue FindRecord(TKey k) = 0; // ����� ������
	virtual void InsRecord(TKey k, PTDatValue pVal) = 0; // ��������
	virtual void DelRecord(TKey k) = 0;        // ������� ������
	//���������
	virtual int Reset(void) { CurrPos = 0; return IsTabEnded(); };   // ���������� �� ������ ������
	virtual int IsTabEnded(void) const { return CurrPos >= DataCount; }; // ������� ���������?
	virtual int GoNext(void) { if (!IsTabEnded()) CurrPos++; else CurrPos = 0; cout << "tu"; return IsTabEnded(); }; // ������� � ��������� ������
							  //(=1 ����� ���������� ��� ��������� ������ �������)
	virtual int SetCurrentPos(int pos) { CurrPos = ((pos > -1) && (pos < DataCount)) ? pos : 0; return IsTabEnded(); };// ���������� ������� ������
	int GetCurrentPos(void) const { return CurrPos; };     //�������� ����� ������� ������
	friend class SortTable;
};

#endif // !