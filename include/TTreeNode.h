#ifndef __TTREE_NODE_H__
#define __TTREE_NODE_H__

#include "TTabRecord.h"

class  TTreeNode;
typedef  TTreeNode* PTTreeNode;
class  TTreeNode : public TTabRecord {
protected:
	PTTreeNode pLeft, pRight; 
public:
	TTreeNode(TKey k = "", PTDatValue pVal = NULL, PTTreeNode pL = NULL,
		PTTreeNode pR = NULL) : TTabRecord(k, pVal), pLeft(pL), pRight(pR) {};
	PTTreeNode GetLeft(void) const; 
	PTTreeNode GetRight(void) const; 
	virtual TDatValue* GetCopy();  
	friend class TTreeTable;
	friend class TBalanceTree;
};

#endif // __TTREE_NODE_H__