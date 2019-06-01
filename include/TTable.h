#ifndef __T_TABLE__
#define __T_TABLE__

#include <iostream>

#include "TTabRecord.h"
#define TabMaxSize 500

class TTable {
protected:
	int DataCount;  // êîëè÷åñòâî çàïèñåé â òàáëèöå
	int Efficiency; // ïîêàçàòåëü ýôôåêòèâíîñòè âûïîëíåíèÿ îïåðàöèè
public:
	TTable() { DataCount = 0; Efficiency = 0; } // êîíñòðóêòîð
	virtual ~TTable() {}; // äåñòðóêòîð
						  // èíôîðìàöèîííûå ìåòîäû
	int GetDataCount() const { return DataCount; }    // ê-âî çàïèñåé
	int GetEfficiency() const { return Efficiency; } // ýôôåêòèâíîñòü
	void ResetEfficiency() { Efficiency = 0; }
	int IsEmpty() const { return DataCount == 0; }   //ïóñòà?
	virtual int IsFull() const = 0;                 // çàïîëíåíà?
													// äîñòóï
	virtual TKey GetKey() const = 0;
	virtual PTDatValue GetValuePtr() const = 0;
	// îñíîâíûå ìåòîäû
	virtual PTDatValue FindRecord(TKey k) = 0; // íàéòè çàïèñü
	virtual void InsRecord(TKey k, PTDatValue pVal) = 0; // âñòàâèòü
	virtual void DelRecord(TKey k) = 0;        // óäàëèòü çàïèñü
											   // íàâèãàöèÿ
	virtual int Reset() = 0; // óñòàíîâèòü íà ïåðâóþ çàïèñü
	virtual int IsTabEnded() const = 0; // òàáëèöà çàâåðøåíà?
	virtual int GoNext() = 0; // ïåðåõîä ê ñëåäóþùåé çàïèñè
							  // (=1 ïîñëå ïðèìåíåíèÿ äëÿ ïîñëåäíåé çàïèñè òàáëèöû)
};

#endif //__T_TABLE__