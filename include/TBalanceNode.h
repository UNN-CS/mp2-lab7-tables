#ifndef __TBALANCE_NODE_H__
#define __TBALANCE_NODE_H__

#include "TTreeNode.h"

#define BalOk 0
#define BalLeft -1
#define BalRight 1
class  TBalanceNode : public TTreeNode {
protected:
	int Balance; // индекс балансировки вершины (-1,0,1)
public:
	TBalanceNode(TKey k = "", PTDatValue pVal = NULL, PTTreeNode pL = NULL,
		PTTreeNode pR = NULL, int bal = BalOk): TTreeNode(k, pVal, pL, pR),
		Balance(bal) {}; // конструктор
	virtual TDatValue * GetCopy();  // изготовить копию
	int GetBalance(void) const;
	void SetBalance(int bal);
	friend class TBalanceTree;
};

typedef TBalanceNode* PTBalanceNode;

#endif // __TBALANCE_NODE_H__
