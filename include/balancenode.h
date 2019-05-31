#ifndef BALANCENODE_H_
#define BALANCENODE_H_
#include "treenode.h"
#define BalOk 0
#define BalLeft -1
#define BalRight 1

class TBalanceNode: public TTreeNode {
 protected:
    int Balance; // индекс балансировки вершины (-1,0,1)
 public:
    TBalanceNode (TKey k = "", PTDatValue pVal = nullptr, PTTreeNode pL = nullptr,
                    PTTreeNode pR = nullptr, int bal = BalOk):
                    TTreeNode(k, pVal, pL, pR), Balance(bal) {}; // конструктор
    virtual TDatValue *GetCopy();  // изготовить копию
    int GetBalance() const;
    void SetBalance(int bal);
    friend class TBalanceTree;
};

typedef TBalanceNode *PTBalanceNode;

#endif // BALANCENODE_H_
