#ifndef __BALTREE_H
#define __BALTREE_H

#include "treetab.h"
#include "balnode.h"

#define HeighOK 0
#define HeighInc 1

class TBalanceTree : public TTreeTable {
protected:
    int InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal);
    int LeftTreeBalancing(PTBalanceNode &pNode); // баланс. левого поддерева
    int RightTreeBalancing(PTBalanceNode &pNode);// баланс. правого поддерева
public:
    TBalanceTree() :TTreeTable() {} // конструктор
    //основные методы
    virtual void InsRecord(TKey k, PTDatValue pVal); // вставить
};

#endif
