#pragma once

#include "ttreenode.hpp"

#define BALOK 0
#define BALLEFT -1
#define BALRIGHT 1

class TBalanceNode : public TTreeNode
{
protected:
    int Balance;

public:
    TBalanceNode(TKey k = "", PTDatValue pVal = nullptr, PTTreeNode pL = nullptr,
                 PTTreeNode pR = nullptr, int bal = BALOK) : TTreeNode(k, pVal, pL, pR), Balance(bal){};
    virtual TDatValue *GetCopy() override;

    int GetBalance() const;
    void SetBalance(int bal);

    friend class TBalanceTree;
};

typedef TBalanceNode *PTBalanceNode;
