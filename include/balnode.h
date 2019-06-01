#ifndef __BALNODE_H
#define __BALNODE_H

#include "treenode.h"

#define BalOK 0
#define BalLeft -1
#define BalRight 1

class  TBalanceNode : public TTreeNode {
protected:
    int Balance; // индекс балансировки вершины (-1,0,1)
public:
    TBalanceNode(TKey k = "", PTDatValue pVal = NULL, PTTreeNode pL = NULL,
        PTTreeNode pR = NULL, int bal = BalOK) : TTreeNode(k, pVal, pL, pR),
        Balance(bal) {}; // конструктор
    virtual TDatValue * GetCopy()  // изготовить копию
    {
        TBalanceNode* tmp = new TBalanceNode(Key, pValue, nullptr, nullptr, BalOK);
        return tmp;
    }
    int GetBalance(void) const { return Balance; }
    void SetBalance(int bal) { Balance = bal; }
    friend class TBalanceTree;
};

typedef TBalanceNode* PTBalanceNode;

#endif
