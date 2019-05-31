#ifndef __balnode_h
#define __balnode_h

#include <iostream>
#include "treenode.h"

#define BalOK 0
#define BalLeft -1
#define BalRight 1

class BalanceNode :public TreeNode {
 protected:
	int Balance; // индекс балансировки вершины (-1,0,1)
 public:
	BalanceNode(TKey k = "", PTDatValue pVal = NULL, PTreeNode pl = NULL, PTreeNode pr = NULL, int bal = BalOK) :
		TreeNode(k, pVal, pl, pr), Balance(bal) {};
	virtual TDatValue* GetCopy();
	int GetBalance() const { return Balance; }
	void SetBalance(int bal) { Balance = bal; }
protected:
	virtual void Print() {
		TreeNode::Print();
		cout << " " << Balance;
	}
	friend class BalanceTree;
};
typedef BalanceNode* PTBalanceNode;
#endif // !__balnode_h
