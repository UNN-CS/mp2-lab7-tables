#ifndef _BALNODE_H
#define BALNODE_H

#include<iostream>
#include "TTreeNode.h"

#define BalOK 0
#define BalLeft -1
#define BalRight 1 

class  TBalanceNode: public TTreeNode {
  protected: 
    int Balance; // индекс балансировки вершины (-1,0,1)
  public:
    TBalanceNode (TKey k="", PTDatValue pVal= nullptr , PTTreeNode pL=nullptr,
      PTTreeNode pR=nullptr, int bal=BalOK): TTreeNode(k,pVal,pL,pR), 
      Balance(bal) {}; // конструктор
    virtual TDatValue * GetCopy();  // изготовить копию
	int GetBalance(void) const {return Balance;}
	void SetBalance(int bal){Balance = bal;}
protected:
	friend class TBalanceTree;
};
typedef TBalanceNode *PTBalanceNode;
#endif