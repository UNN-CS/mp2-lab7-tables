#include "datlist.h"

#include "datlink.h"
#include "datvalue.h"

TDatList::TDatList() {
    pFirst = nullptr;
    pLast = nullptr;
    pCurrLink = nullptr;
    pPrevLink = nullptr;
    pStop = nullptr;
    currPos = 0;
    listLen = 0;
}

PTDatValue TDatList::GetDatValue(TLinkPos mode) const {
    switch (mode) {
      case TLinkPos::CURRENT:
        if (pCurrLink == nullptr) {
            return nullptr;
        }
        return pCurrLink->GetDatValue();
      case TLinkPos::FIRST:
        if (pFirst == nullptr) {
            return nullptr;
        }
        return pFirst->GetDatValue();
      case TLinkPos::LAST:
        if (pLast == nullptr) {
            return nullptr;
        }
        return pLast->GetDatValue();
      default:
        return nullptr;
    }
}

void TDatList::SetCurrentPos(int pos) {
    if (pos < 0 || pos > listLen) {
        return;
    }
    pCurrLink = pFirst;
    pPrevLink = pStop;
    currPos = 0;
    for (currPos = 0; currPos < pos; ++currPos) {
        pPrevLink = pCurrLink;
        pCurrLink = (PTDatLink)pCurrLink->pNext;
    }
}

int TDatList::GetCurrentPos() const {
    return currPos;
}

int TDatList::Reset() {
    pPrevLink = pStop;
    pCurrLink = pFirst;
    currPos = 0;
    return IsListEnded();
}

int TDatList::IsListEnded() const {
    return pCurrLink == pStop;
}

int TDatList::GoNext() {
    if (IsListEnded()) {
        return 0;
    }

    pPrevLink = pCurrLink;
    pCurrLink = (PTDatLink)pCurrLink->pNext;
    ++currPos;
    return 1;
}

void TDatList::InsFirst(PTDatValue pVal) {
    if (IsEmpty()) {
        pFirst = new TDatLink(pVal, pStop);
        pPrevLink = pStop;
        pLast = pCurrLink = pFirst;
        currPos = 0;
        ++listLen;
    } else {
        pFirst = new TDatLink(pVal, pFirst);
        ++listLen;
        ++currPos;
        if (currPos == 1) {
            pPrevLink = pFirst;
        }
    }
}

void TDatList::InsLast(PTDatValue pVal) {
    if (IsEmpty()) {
        pFirst = new TDatLink(pVal, pStop);
        pPrevLink = pStop;
        pLast = pCurrLink = pFirst;
        currPos = 0;
        ++listLen;
    } else {
        pLast->pNext = new TDatLink(pVal, pStop);
        pLast = (PTDatLink)pLast->pNext;
        ++listLen;
    }
}

void TDatList::InsCurrent(PTDatValue pVal) {
    if (IsEmpty()) {
        pFirst = new TDatLink(pVal, pStop);
        pPrevLink = pStop;
        pLast = pCurrLink = pFirst;
        currPos = 0;
        ++listLen;
    } else {
        pPrevLink->pNext = new TDatLink(pVal, pCurrLink);
        pPrevLink = (PTDatLink)pPrevLink->pNext;
        ++currPos;
        ++listLen;
    }
}

void TDatList::DelFirst() {
    if (IsEmpty()) {
        return;
    } else {
        PTDatLink p = (PTDatLink)pFirst->pNext;
        DelLink(pFirst);
        pFirst = p;
        --listLen;
        --currPos;
        if (currPos == 0) {
            pPrevLink = p;
        } else if (currPos == -1) {
            pPrevLink = p;
            pCurrLink = p;
            currPos = 0;
        }
    }
}

void TDatList::DelCurrent() {
    if (IsEmpty() || IsListEnded()) {
        return;
    } else if (currPos == 0) {
        DelFirst();
    } else {
        --listLen;
        PTDatLink p = (PTDatLink)pCurrLink->pNext;
        pPrevLink->pNext = p;
        DelLink(pCurrLink);
        pCurrLink = p;
    }
}

void TDatList::DelList() {
    PTDatLink p;
    while (pFirst != pStop) {
        p = pFirst;
        pFirst = (PTDatLink)pFirst->pNext;
        DelLink(p);
    }
    pCurrLink = pPrevLink = pLast = pStop;
    listLen = currPos = 0;
}

PTDatLink TDatList::GetLink (PTDatValue pVal, PTDatLink pLink) {
    return new TDatLink(pVal, pLink);
}

void TDatList::DelLink (PTDatLink pLink) {
    if (pLink->GetDatValue() != NULL) {
        delete pLink->GetDatValue();
    }
    delete pLink;
}



