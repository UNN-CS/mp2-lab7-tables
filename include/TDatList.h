#ifndef __DATLIST_H__
#define __DATLIST_H__

#include "TDatValue.h"
#include "TDatLink.h"

typedef TDatList* PTDatList;

class TDatList 
{
	protected:
	PTDatLink pFirst;
	PTDatLink pLast;
	PTDatLink pCurrLink;
	PTDatLink pPrevLink;
	PTDatLink pStop;
	int CurrPos;
	int ListLen;
	
	PTDatLink GetLink(PTDatValue pVal = NULL, PTDatLink pLink = NULL);
	void DelLink(PTDatLink pLink);
	
	public:
	TDatList();
	~TDatList();
	
    PTDatValue GetDatValue(TLinkPos mode = CURRENT) const;
	virtual bool IsEmpty() const;
	int GetListLeght() const;
	
	void SetCurrentPos(int pos);
    int GetCurrentPos() const;
    virtual void Reset();
    virtual bool IsListEnded() const;
    void GoNext();
	
    virtual void InsFirst(PTDatValue pVal = NULL);
    virtual void InsLast(PTDatValue pVal = NULL); 
    virtual void InsCurrent(PTDatValue pVal= NULL);
	
    virtual void DelFirst();
    virtual void DelCurrent();
    virtual void DelList();
};

#endif