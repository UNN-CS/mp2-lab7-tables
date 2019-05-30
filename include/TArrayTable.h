#ifndef __T_ARRAY_TABLE_H__
#define __T_ARRAY_TABLE_H__

#include "ttable.h"

#define TabMaxSize 25
enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class TArrayTable : public TTable {
protected:
	PTTabRecord * pRecs; // ïàìÿòü äëÿ çàïèñåé òàáëèöû
	int TabSize;        // ìàêñ. âîçì.êîëè÷åñòâî çàïèñåé â òàáëèöå
	int CurrPos;        // íîìåð òåêóùåé çàïèñè (íóìåðàöèÿ ñ 0)
public:
	TArrayTable(int Size = TabMaxSize); // êîíñòðóêòîð
	~TArrayTable();                // äåñòðóêòîð
								   // èíôîðìàöèîííûå ìåòîäû
	virtual int IsFull() const; // çàïîëíåíà?
	int GetTabSize() const;      // ê-âî çàïèñåé
								 // äîñòóï
	virtual TKey GetKey() const;
	virtual PTDatValue GetValuePtr() const;
	virtual TKey GetKey(TDataPos mode) const;
	virtual PTDatValue GetValuePtr(TDataPos mode) const;
	// îñíîâíûå ìåòîäû
	virtual PTDatValue FindRecord(TKey k) = 0; // íàéòè çàïèñü
	virtual void InsRecord(TKey k, PTDatValue pVal) = 0; // âñòàâèòü
	virtual void DelRecord(TKey k) = 0;        // óäàëèòü çàïèñü
											   //íàâèãàöèÿ
	virtual int Reset();   // óñòàíîâèòü íà ïåðâóþ çàïèñü
	virtual int IsTabEnded() const; // òàáëèöà çàâåðøåíà?
	virtual int GoNext(); // ïåðåõîä ê ñëåäóþùåé çàïèñè
						  //(=1 ïîñëå ïðèìåíåíèÿ äëÿ ïîñëåäíåé çàïèñè òàáëèöû)
	virtual int SetCurrentPos(int pos);// óñòàíîâèòü òåêóùóþ çàïèñü
	int GetCurrentPos() const;     //ïîëó÷èòü íîìåð òåêóùåé çàïèñè
	friend class TSortTable;
};

#endif // __T_ARRAY_TABLE_H__
