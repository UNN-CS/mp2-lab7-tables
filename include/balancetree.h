#pragma once

#include "defines.h"

#include "treetable.h"

class TBalanceTree : public TTreeTable {
  public:
    TBalanceTree();

    virtual void InsRecord(TKey k, PTDatValue pVal) override;
    virtual void DelRecord(TKey k) override;

  protected:
    int InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal);
    int LeftTreeBalancing(PTBalanceNode &pNode);
    int RightTreeBalancing(PTBalanceNode &pNode);
};
