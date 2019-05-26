#ifndef _ROOTLINK_H_
#define _ROOTLINK_H_
#include "datvalue.h"

class TRootLink;
typedef TRootLink *PTRootLink;

class TRootLink {
protected:
    PTRootLink pNext;  // ��������� �� ��������� �����
public:
    TRootLink(PTRootLink pN = nullptr) { pNext = pN; }
    PTRootLink  GetNextLink() { return  pNext; }
    void SetNextLink(PTRootLink pLink) { pNext = pLink; }
    void InsNextLink(PTRootLink pLink) {
        PTRootLink p = pNext;
        pNext = pLink;
        if (pLink)
            pLink->pNext = p;
    }
    virtual void SetDatValue(PTDatValue pVal) = 0;
    virtual PTDatValue GetDatValue() = 0;

    friend class TDatList;
};

#endif  // _ROOTLINK_H_
