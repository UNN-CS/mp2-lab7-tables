#include "TRootLink.h"

void TRootLink::InsNextLink(PTRootLink pLink)
{
	PTRootLink p = pNext;
	pNext = pLink;
	if (pLink != nullptr) pLink->pNext = p;
}