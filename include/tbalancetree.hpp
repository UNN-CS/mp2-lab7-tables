#pragma once

#include "tbalancenode.hpp"
#include "ttreetable.hpp"

class TBalanceTree : public TTreeTable
{
protected:
    int InsBalanceTree(PTBalanceNode &pNode, TKey& k, PTDatValue pVal);
    int LeftTreeBalancing(PTBalanceNode &pNode);
    int RightTreeBalancing(PTBalanceNode &pNode);

public:
    TBalanceTree() : TTreeTable() {}

    virtual void InsRecord(TKey k, PTDatValue pVal) override;
    virtual void DelRecord(TKey k) override;
};
