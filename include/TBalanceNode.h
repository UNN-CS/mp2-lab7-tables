#ifndef __TBALANCE_NODE_H__
#define __TBALANCE_NODE_H__

#include "TTreeNode.h"

#define BalOk 0
#define BalLeft -1
#define BalRight 1
class TBalanceNode;
typedef TBalanceNode* PTBalanceNode;

class  TBalanceNode : public TTreeNode {
protected:
	int Balance; 
public:
	TBalanceNode(TKey k = "", PTDatValue pVal = NULL, PTTreeNode pL = NULL,
		PTTreeNode pR = NULL, int bal = BalOk) : TTreeNode(k, pVal, pL, pR),
		Balance(bal) {}; 
	virtual TDatValue* GetCopy();  
	int GetBalance(void) const;
	void SetBalance(int bal);
	friend class TBalanceTree;
};

#endif // __TBALANCE_NODE_H__