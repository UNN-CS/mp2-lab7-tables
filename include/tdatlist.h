#ifndef __DATLIST_H__
#define __DATLIST_H__

#include "tdatlink.h"

enum TLinkPos { FIRST, CURRENT, LAST };

#define ListOK       0
#define ListEmpty -101
#define ListNoMem -102
#define ListNoPos -103

class TDatList {
protected:
    PTDatLink pFirst;
    PTDatLink pLast;
    PTDatLink pCurrLink;
    PTDatLink pPrevLink;
    PTDatLink pStop;
    int CurrPos;
    int ListLen;
protected:
    PTDatLink GetLink(PTDatValue pVal = nullptr, PTDatLink pLink = nullptr);
    void DelLink(PTDatLink pLink);
public:
    TDatList();
    ~TDatList() { DelList(); }
    PTDatValue GetDatValue(TLinkPos mode = CURRENT) const;
    virtual int IsEmpty() const { return pFirst == pStop; }
    int GetListLength() const { return ListLen; }
    int SetCurrentPos(int pos);
    int GetCurrentPos() const;
    virtual int Reset();
    virtual int IsListEnded() const;
    int GoNext();
    virtual void InsFirst(PTDatValue pVal = nullptr);
    virtual void InsLast(PTDatValue pVal = nullptr);
    virtual void InsCurrent(PTDatValue pVal = nullptr);
    virtual void DelFirst();
    virtual void DelCurrent();
    virtual void DelList();
};

typedef TDatList* PTDatList;

#endif
