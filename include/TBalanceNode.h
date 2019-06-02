// базовый класс для сбалансированных деревьев
#ifndef _BALNODE_H
#define _BALNODE_H

#include "TTreeNode.h"

#define BalOk 0
#define BalLeft -1
#define BalRight 1
class  TBalanceNode : public TTreeNode {
protected:
    int Balance; // индекс балансировки вершины
public:
    TBalanceNode(TKey k = "", PTDatValue pVal = nullptr, PTTreeNode pL = nullptr,
        PTTreeNode pR = nullptr, int bal = BalOk) : TTreeNode(k, pVal, pL, pR),
        Balance(bal) {}; 
    virtual TDatValue * GetCopy();  
    int GetBalance(void) const { return Balance; }
    void SetBalance(int bal) { Balance = bal; }
    friend class TBalanceTree;
};
typedef TBalanceNode *PTBalanceNode;
#endif //_BALNODE_H