#ifndef __TBALANCETREE_H__
#define __TBALANCETREE_H__
#include "tbalancenode.h"
#include "ttreetable.h"

class TBalanceTree: public TTreeTable {
 protected:
    int InsBalanceTree(PTTreeNode &pNode_, TKey k, PTDatValue pVal);
    int LeftTreeBalancing(PTBalanceNode &pNode); // баланс. левого поддерева
    int RightTreeBalancing(PTBalanceNode &pNode);// баланс. правого поддерева
 public:
    TBalanceTree() : TTreeTable() {} // конструктор
    //основные методы
    virtual void InsRecord(TKey k, PTDatValue pVal) override; // вставить
};

#endif // __TBALANCETREE_H__
