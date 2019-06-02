#ifndef __ARRAYTAB_H
#define __ARRAYTAB_H

#include "TTable.h"

#define TabMaxSize 40
enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class  TArrayTable : public TTable {
protected:
	PTTabRecord *pRecs; // ïàìÿòü äëÿ çàïèñåé òàáëèöû
	int TabSize;        // ìàêñ. âîçì.êîëè÷åñòâî çàïèñåé â òàáëèöå
	int CurrPos;        // íîìåð òåêóùåé çàïèñè (íóìåðàöèÿ ñ 0)
public:
	TArrayTable(int Size = TabMaxSize)
	{
		if (Size <= 0)
			Size = TabMaxSize;
		pRecs = new PTTabRecord[Size];
		for (int i = 0; i<Size; i++)
			pRecs[i] = nullptr;
		TabSize = Size;
		DataCount = CurrPos = 0;

	}
	~TArrayTable()
	{
		for (int i = 0; i<DataCount; i++)
			delete pRecs[i];
		delete[] pRecs;
	}
	// èíôîðìàöèîííûå ìåòîäû
	virtual int IsFull() const { return DataCount >= TabSize; } // çàïîëíåíà?
	int GetTabSize() const { return TabSize; }      // ê-âî çàïèñåé

	// äîñòóï
	virtual TKey GetKey(void) const { return GetKey(CURRENT_POS); }
	virtual PTDatValue GetValuePTR(void) const { return GetValuePTR(CURRENT_POS); }
	virtual TKey GetKey(TDataPos mode) const;
	virtual PTDatValue GetValuePTR(TDataPos mode) const;

	// îñíîâíûå ìåòîäû
	virtual PTDatValue FindRecord(TKey k) = 0; // íàéòè çàïèñü
	virtual void InsRecord(TKey k, PTDatValue pVal) = 0; // âñòàâèòü
	virtual void DelRecord(TKey k) = 0;        // óäàëèòü çàïèñü

	//íàâèãàöèÿ
	virtual int Reset(void);   // óñòàíîâèòü íà ïåðâóþ çàïèñü
	virtual int IsTabEnded(void) const; // òàáëèöà çàâåðøåíà?
	virtual int GoNext(void); // ïåðåõîä ê ñëåäóþùåé çàïèñè
							  //(=1 ïîñëå ïðèìåíåíèÿ äëÿ ïîñëåäíåé çàïèñè òàáëèöû)

	virtual int SetCurrentPos(int pos);// óñòàíîâèòü òåêóùóþ çàïèñü
	int GetCurrentPos(void) const { return CurrPos; }     //ïîëó÷èòü íîìåð òåêóùåé çàïèñè
	friend TSortTable;
};
#endif 
