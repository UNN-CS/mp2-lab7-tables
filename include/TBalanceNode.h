#ifndef __BALANCENODE_H__
#define __BALANCENODE_H__

#include "TTreeNode.h"

#define BalOk 0
#define BalLeft -1
#define BalRight 1

class  TBalanceNode : public TTreeNode {
protected:
	int Balance; // ������ ������������ ������� (-1,0,1)
public:
	TBalanceNode(TKey k = "", PTDatValue pVal = NULL, PTTreeNode pL = NULL,
		PTTreeNode pR = NULL, int bal = BalOk); // �����������
	virtual TDatValue * GetCopy();  // ���������� �����
	int GetBalance() const;
	void SetBalance(int bal);
	friend class TBalanceTree;
};

typedef  TBalanceNode* PTBalanceNode;

#endif