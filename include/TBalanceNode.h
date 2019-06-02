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
	virtual TDatValue* GetCopy() { return new TBalanceNode(Key, pValue, pLeft, pRight, Balance); }
	int GetBalance(void) const { return Balance; }
	void SetBalance(int bal) { Balance = bal; }
	friend class TBalanceTree;
};

#endif // end of balnode.h