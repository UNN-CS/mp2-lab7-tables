#pragma once

#include "defines.h"

#include "treenode.h"

class TBalanceNode : public TTreeNode {
  public:
    TBalanceNode (TKey k = "",
            PTDatValue pVal = nullptr,
            PTTreeNode pL = nullptr,
            PTTreeNode pR = nullptr,
            int bal = BalOk);

    virtual PTDatValue GetCopy() const override;

    int GetBalance() const;
    void SetBalance(int bal);

  protected:
    int balance;

    friend class TBalanceTree;
};
