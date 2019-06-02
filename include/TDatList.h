#ifndef __DATLIST_H
#define __DATLIST_H
#include "TDatLink.h"
#include "tdatacom.h"

#define ListOK 0 // no mistakes
#define ListEmpty -101 // list is empty
#define ListNoMem -102// no memory
#define ListNoPos -103// mistake position  pCurrLink

class TDatList : public TDataCom
{
protected:
	PTDatLink pFirst;
	PTDatLink pLast;// ïîñëåäíèé ýëåìåíò
	PTDatLink pCurrLink;
	PTDatLink pPrevLink;
	PTDatLink pStop; // êîíåö ñïèñêà
	int CurrPos;
	int ListLen;
protected:
	PTDatLink GetLink(PTDatValue pVal = nullptr, PTDatLink pLink = nullptr);
	void DelLink(PTDatLink pLink);
public:
	TDatList();
	~TDatList() { DelList(); }
	// äîñòóï 
	PTDatValue GetDatValue() const;
	// çíà÷åíèå 
	virtual int IsEmpty() const { return pFirst == pStop; } // ñïèñîê ïóñò ? 
	int GetListLength() const { return ListLen; } // ê-âî çâåíüåâ 
												  // íàâèãàöèÿ 
	int SetCurrentPos(int pos); // óñòàíîâèòü òåêóùåå çâåíî 
	int GetCurrentPos(void) const;// ïîëó÷èòü íîìåð òåê. çâåíà 
	virtual int Reset(void); // óñòàíîâèòü íà íà÷àëî ñïèñêà 
	virtual int IsListEnded(void) const; // ñïèñîê çàâåðøåí ? 
	int GoNext(void); // ñäâèã âïðàâî òåêóùåãî çâåíà // (=1 ïîñëå ïðèìåíåíèÿ GoNext äëÿ ïîñëåäíåãî çâåíà ñïèñêà) // âñòàâêà çâåíüåâ 
	virtual void InsFirst(PTDatValue pVal = nullptr); // ïåðåä ïåðâûì 
	virtual void InsLast(PTDatValue pVal = nullptr); // âñòàâèòü ïîñëåäíèì 
	virtual void InsCurrent(PTDatValue pVal = nullptr); // ïåðåä òåêóùèì 
														// óäàëåíèå çâåíüåâ 
	virtual void DelFirst(void); // óäàëèòü ïåðâîå çâåíî 
	virtual void DelCurrent(void); // óäàëèòü òåêóùåå çâåíî 
	virtual void DelList(void); // óäàëèòü âåñü ñïèñîê

};
typedef TDatList *PTDatList;
#endif 
