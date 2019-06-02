#ifndef _LISTHASH_H
#define _LISTHASH_H

#include <string>
#include "TDatList.h"
#include "THashTable.h"

#define TabMaxSize 40
class  TListHash : public THashTable
{
protected:
	PTDatList *pList; // ïàìÿòü äëÿ ìàññèâà óêàçàòåëåé íà ñïèñêè çàïèñåé 
	int TabSize;      // ðàçìåð ìàññèâà óêàçàòåëåé
	int CurrList;     // ñïèñîê, â êîòîðîì âûïîëíÿëñÿ ïîèñê
public:
	TListHash(int Size = TabMaxSize); // êîíñòðóêòîð
	~TListHash();
	// èíôîðìàöèîííûå ìåòîäû
	virtual int IsFull() const; // çàïîëíåíà?
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
