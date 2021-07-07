#pragma once

#include "defines.h"

class TDatList {
  public:
    TDatList();
    ~TDatList() { DelList(); }

    PTDatValue GetDatValue ( TLinkPos mode = CURRENT ) const;
    virtual int IsEmpty() const { return pFirst==pStop; }
    int GetListLength() const { return listLen; }

    void SetCurrentPos(int pos);
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
  protected:
    PTDatLink GetLink (PTDatValue pVal = nullptr,
            PTDatLink pLink = nullptr);
    void DelLink (PTDatLink pLink);

    PTDatLink pFirst;
    PTDatLink pLast;
    PTDatLink pCurrLink;
    PTDatLink pPrevLink;
    PTDatLink pStop;
    int listLen;
    int currPos;
};
