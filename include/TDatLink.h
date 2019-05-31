#ifndef __TDatLink_H
#define __TDatLink_H

#include "TRootLink.h"
class TDatLink;
typedef TDatLink* PTDatLink;

class TDatLink:public TRootLink
{
protected:
	PTDatValue pValue;
public:
	TDatLink(PTDatValue pDat = nullptr,PTRootLink pLink=nullptr):TRootLink(pLink) { pValue = pDat; }
	void SetDatValue(PTDatValue pDat);
	PTDatValue GetDatValue();
	PTDatLink GetNextDatLink();
	friend class TDatList;
};
#endif 
