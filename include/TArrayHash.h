#ifndef _ARRAHASH_H
#define _ARRAHASH_H

#include "THashTable.h"

#define TabMaxSize 40
#define TabHashStep 3

class  TArrayHash : public THashTable {
protected:
	PTTabRecord *pRecs; // ïàìÿòü äëÿ çàïèñåé òàáëèöû
	int TabSize;        // ìàêñ. âîçì. ê-âî çàïèñåé
	int HashStep;       // øàã âòîðè÷íîãî ïåðåìåøèâàíèÿ
	int FreePos;        // ïåðâàÿ ñâîáîäíàÿ ñòðîêà, îáíàðóæåííàÿ ïðè ïîèñêå
	int CurrPos;        // ñòðîêà ïàìÿòè ïðè çàâåðøåíèè ïîèñêà
	PTTabRecord pMark;  // ìàðêåð äëÿ èíäèêàöèè ñòðîê ñ óäàëåííûìè çàïèñÿìè
	int GetNextPos(int pos) { return (pos + HashStep) % TabSize; };// îòêð. ïåðåì.
public:
	TArrayHash(int Size = TabMaxSize, int Step = TabHashStep); // êîíñòðóêòîð
	~TArrayHash();

	// èíôîðìàöèîííûå ìåòîäû
	virtual int IsFull() const { return DataCount >= TabSize; } // çàïîëíåíà?	

	// äîñòóï
	virtual TKey GetKey(void) const;
	virtual PTDatValue GetValuePTR(void) const;

	// îñíîâíûå ìåòîäû
	virtual PTDatValue FindRecord(TKey k); // íàéòè çàïèñü
	virtual void InsRecord(TKey k, PTDatValue pVal); // âñòàâèòü
	virtual void DelRecord(TKey k);        // óäàëèòü çàïèñü

	// íàâèãàöèÿ
	virtual int Reset(void);   // óñòàíîâèòü íà ïåðâóþ çàïèñü
	virtual int IsTabEnded(void) const; // òàáëèöà çàâåðøåíà?
	virtual int GoNext(void); // ïåðåõîä ê ñëåäóþùåé çàïèñè
							  //(=1 ïîñëå ïðèìåíåíèÿ äëÿ ïîñëåäíåé çàïèñè òàáëèöû)
};
#endif 
