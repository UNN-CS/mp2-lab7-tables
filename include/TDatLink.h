#ifndef __DATLINK_H__
#define __DATLINK_H__

#include "TRootLink.h"

class TDatLink;

typedef TDatLink* PTDatLink;

enum TLinkPos{FIRST, CURRENT, LAST};

class TDatLink: public TRootLink
{
	protected:
	PTDatValue pValue;
	
public:
	TDatLink(PTDatValue pVal = NULL, PTRootLink pN = NULL);
	void SetDatValue(PTDatValue pVal);
	PTDatValue GetDatValue();
	PTDatLink GetNextDatLink();
	
	friend class TDatList;
};

#endif