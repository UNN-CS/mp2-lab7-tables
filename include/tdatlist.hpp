#pragma once

#include "tdatlink.hpp"

enum TLinkPos
{
    FIRST,
    CURRENT,
    LAST
};

#define LISTOK 0
#define LISTEMPTY -101
#define LISTNOMEM -102
#define LISTNOPOS -103

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

protected:
    PTDatLink GetLink(PTDatValue pVal = nullptr, PTDatLink pLink = nullptr);
    void DelLink(PTDatLink pLink);

public:
    TDatList();
    ~TDatList() { DelList(); }
    // access
    PTDatValue GetDatValue(TLinkPos mode = CURRENT) const;
    virtual int IsEmpty() const { return pFirst == pStop; }
    int GetListLength() const { return ListLen; }
    // navigation
    int SetCurrentPos(int pos);
    int GetCurrentPos() const;
    virtual int Reset();
    virtual int IsListEnded() const;
    int GoNext();
    // link insertion
    virtual void InsFirst(PTDatValue pVal = nullptr);
    virtual void InsLast(PTDatValue pVal = nullptr);
    virtual void InsCurrent(PTDatValue pVal = nullptr);
    // link deletion
    virtual void DelFirst();
    virtual void DelCurrent();
    virtual void DelList();
};

typedef TDatList *PTDatList;
