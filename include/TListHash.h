#ifndef __T_LIST_HASH_H_
#define __T_LIST_HASH_H_

#include "THashTable.h"
#include "TDatList.h"

class TListHash : public THashTable {
protected:
	PTDatList * pList; // ïàìÿòü äëÿ ìàññèâà óêàçàòåëåé íà ñïèñêè çàïèñåé
	int TabSize;      // ðàçìåð ìàññèâà óêàçàòåëåé
	int CurrList;     // ñïèñîê, â êîòîðîì âûïîëíÿëñÿ ïîèñê
public:
	TListHash(int Size = TabMaxSize); // êîíñòðóêòîð
	~TListHash();
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
#endif //__T_LIST_HASH_H_
