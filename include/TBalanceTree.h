//—балансированные деревь€ поиска (AVL)
#ifndef _BALTREE_H
#define _BALTREE_H

#include "TBalanceNode.h"
#include "TTreeTable.h"

#define HeightOK 0
#define HeighInc 1

class  TBalanceTree : public TTreeTable {
protected:
    int InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal);
    int LeftTreeBalancing(PTBalanceNode &pNode);
    int RightTreeBalancing(PTBalanceNode &pNode);
public:
    TBalanceTree() : TTreeTable() {}

    virtual void InsRecord(TKey k, PTDatValue pVal); 
};
#endif