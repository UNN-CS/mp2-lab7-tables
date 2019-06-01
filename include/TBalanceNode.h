#ifndef __T_BALANCE_NODE_H__
#define __T_BALANCE_NODE_H__

#include "TTreeNode.h"

#define BalOk 0
#define BalLeft -1
#define BalRight 1

class TBalanceNode : public TTreeNode {
protected:
	int Balance; // èíäåêñ áàëàíñèğîâêè âåğøèíû (-1,0,1)
public:
	TBalanceNode(TKey k = "", PTDatValue pVal = nullptr, PTTreeNode pL = nullptr,
		PTTreeNode pR = nullptr, int bal = BalOk) :
		TTreeNode(k, pVal, pL, pR), Balance(bal) {}; // êîíñòğóêòîğ
	virtual TDatValue *GetCopy();  // èçãîòîâèòü êîïèş
	int GetBalance() const;
	void SetBalance(int bal);
	friend class TBalanceTree;
};

typedef TBalanceNode *PTBalanceNode;

#endif //__T_BALANCE_NODE_H__