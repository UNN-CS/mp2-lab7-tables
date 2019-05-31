#ifndef __T_DAT_LINK_H__
#define __T_DAT_LINK_H__

#include "TRootLink.h"

class TDatLink;
typedef TDatLink *PTDatLink;

class TDatLink : public TRootLink {
protected:
	PTDatValue pValue;  // óêàçàòåëü íà îáúåêò çíà÷åíèÿ
public:
	TDatLink(PTDatValue pVal = nullptr, PTRootLink pN = nullptr) :
		TRootLink(pN) {
		pValue = pVal;
	}
	void SetDatValue(PTDatValue pVal) { pValue = pVal; }
	PTDatValue GetDatValue() { return  pValue; }
	PTDatLink GetNextDatLink() { return  (PTDatLink)pNext; }
	friend class TDatList;
};

#endif //__T_DAT_LINK_H__
