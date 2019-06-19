#ifndef _DATLINK_H_
#define _DATLINK_H_
#include "rootlink.h"

class TDatLink;
typedef TDatLink *PTDatLink;

class TDatLink : public TRootLink {
protected:
    PTDatValue pValue;  // указатель на объект значения
public:
    TDatLink (PTDatValue pVal = nullptr, PTRootLink pN = nullptr) :
        TRootLink(pN) {
        pValue = pVal;
    }
    void SetDatValue(PTDatValue pVal) { pValue = pVal; }
    PTDatValue GetDatValue() { return  pValue; }
    PTDatLink GetNextDatLink() { return  (PTDatLink)pNext; }
    friend class TDatList;
};

#endif  // _DATLINK_H_
