#pragma once

#include "trootlink.hpp"

class TDatLink;
typedef TDatLink *PTDatLink;

class TDatLink : public TRootLink
{
protected:
    PTDatValue pValue; // value pointer
public:
    TDatLink(PTDatValue pVal = nullptr, PTRootLink pN = nullptr) : TRootLink(pN)
    {
        pValue = pVal;
    }
    // misc methods
    void SetDatValue(PTDatValue pVal) { pValue = pVal; }
    PTDatValue GetDatValue() { return pValue; }
    PTDatLink GetNextDatLink() { return (PTDatLink)pNext; }

    friend class TDatList;
};
