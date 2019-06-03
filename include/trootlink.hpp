#pragma once

#include "tdatvalue.hpp"

class TRootLink;
typedef TRootLink *PTRootLink;

class TRootLink
{
protected:
    PTRootLink pNext; // next link pointer
public:
    TRootLink(PTRootLink pN = nullptr) { pNext = pN; }
    // misc methods
    PTRootLink GetNextLink() { return pNext; }
    void SetNextLink(PTRootLink pLink) { pNext = pLink; }
    void InsNextLink(PTRootLink pLink)
    {
        PTRootLink p = pNext;
        pNext = pLink;
        if (pLink)
            pLink->pNext = p;
    }
    virtual void SetDatValue(PTDatValue pVal) = 0;
    virtual PTDatValue GetDatValue() = 0;

    friend class TDatList;
};