#ifndef __T_HASH_ARRAY_H__
#define __T_HASH_ARRAY_H__

#include "THashTable.h"

#define TabHashStep 1

class  TArrayHash : public THashTable {
protected:
	PTTabRecord * pRecs; // ïàìÿòü äëÿ çàïèñåé òàáëèöû
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
	virtual int IsFull() const; // çàïîëíåíà?
								// äîñòóï
	virtual TKey GetKey() const;
	virtual PTDatValue GetValuePtr() const;
	// îñíîâíûå ìåòîäû
	virtual PTDatValue FindRecord(TKey k); // íàéòè çàïèñü
	virtual void InsRecord(TKey k, PTDatValue pVal); // âñòàâèòü
	virtual void DelRecord(TKey k);        // óäàëèòü çàïèñü
										   // íàâèãàöèÿ
	virtual int Reset();   // óñòàíîâèòü íà ïåðâóþ çàïèñü
	virtual int IsTabEnded() const; // òàáëèöà çàâåðøåíà?
	virtual int GoNext(); // ïåðåõîä ê ñëåäóþùåé çàïèñè
						  //(=1 ïîñëå ïðèìåíåíèÿ äëÿ ïîñëåäíåé çàïèñè òàáëèöû)
};

#endif //__T_HASH_ARRAY_H__
