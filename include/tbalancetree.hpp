#pragma once

#include "tbalancenode.hpp"
#include "ttreetable.hpp"

class TBalanceTree : public TTreeTable
{
protected:
    int InsBalanceTree(PTTreeNode &pNode_, TKey k, PTDatValue pVal);
    int LeftTreeBalancing(PTBalanceNode &pNode);
    int RightTreeBalancing(PTBalanceNode &pNode);

public:
    TBalanceTree() : TTreeTable() {}
    virtual void InsRecord(TKey k, PTDatValue pVal) override;
};
