#ifndef __T_DATLIST_H__
#define __T_DATLIST_H__

#include "TDatLink.h"

enum TLinkPos { FIRST, CURRENT, LAST };

#define ListOK       0
#define ListEmpty -101
#define ListNoMem -102
#define ListNoPos -103

class TDatList {
protected:
	PTDatLink pFirst;    // ïåðâîå çâåíî
	PTDatLink pLast;     // ïîñëåäíåå çâåíî
	PTDatLink pCurrLink; // òåêóùåå çâåíî
	PTDatLink pPrevLink; // çâåíî ïåðåä òåêóùèì
	PTDatLink pStop;     // çíà÷åíèå óêàçàòåëÿ, îçíà÷àþùåãî êîíåö ñïèñêà
	int CurrPos;         // íîìåð òåêóùåãî çâåíà (íóìåðàöèÿ îò 0)
	int ListLen;         // êîëè÷åñòâî çâåíüåâ â ñïèñêå
protected:  // ìåòîäû
	PTDatLink GetLink(PTDatValue pVal = nullptr, PTDatLink pLink = nullptr);
	void DelLink(PTDatLink pLink);   // óäàëåíèå çâåíà
public:
	TDatList();
	~TDatList() { DelList(); }
	// äîñòóï
	PTDatValue GetDatValue(TLinkPos mode = CURRENT) const; // çíà÷åíèå
	virtual int IsEmpty() const { return pFirst == pStop; } // ñïèñîê ïóñò ?
	int GetListLength() const { return ListLen; }       // ê-âî çâåíüåâ
	// íàâèãàöèÿ
	int SetCurrentPos(int pos);          // óñòàíîâèòü òåêóùåå çâåíî
	int GetCurrentPos() const;       // ïîëó÷èòü íîìåð òåê. çâåíà
	virtual int Reset();             // óñòàíîâèòü íà íà÷àëî ñïèñêà
	virtual int IsListEnded() const; // ñïèñîê çàâåðøåí ?
	int GoNext();                    // ñäâèã âïðàâî òåêóùåãî çâåíà
				// (=1 ïîñëå ïðèìåíåíèÿ GoNext äëÿ ïîñëåäíåãî çâåíà ñïèñêà)
	// âñòàâêà çâåíüåâ
	virtual void InsFirst(PTDatValue pVal = nullptr); // ïåðåä ïåðâûì
	virtual void InsLast(PTDatValue pVal = nullptr); // âñòàâèòü ïîñëåäíèì
	virtual void InsCurrent(PTDatValue pVal = nullptr); // ïåðåä òåêóùèì
	// óäàëåíèå çâåíüåâ
	virtual void DelFirst();    // óäàëèòü ïåðâîå çâåíî
	virtual void DelCurrent();    // óäàëèòü òåêóùåå çâåíî
	virtual void DelList();    // óäàëèòü âåñü ñïèñîê
};
typedef TDatList *PTDatList;

#endif  // __T_DATLIST_H__