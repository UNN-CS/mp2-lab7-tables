#ifndef __TRootLink_H
#define __TRootLink_H

#include "TDatValue.h"

class TRootLink;
typedef TRootLink * PTRootLink;
class TRootLink
{
protected:
	PTRootLink pNext;
public:
	TRootLink(PTRootLink p = nullptr) { pNext = p; }
	PTRootLink GetNextLink() { return pNext; }
	void SetNextLink(PTRootLink p = 0) { pNext = p; }
	void InsNextLink(PTRootLink pLink);
	virtual void SetDatValue(PTDatValue) = 0;
	virtual PTDatValue GetDatValue() = 0;
	friend class TDatList;
};
#endif 
