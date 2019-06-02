// TBalanceTree.h
#ifndef _BALTREE_H
#define _BALTREE_H
#include "TBalanceNode.h"
#include "TTreeTable.h"
#define HeightOK 0
#define HeighInc 1

class  TBalanceTree : public TTreeTable {
protected:
    int InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal);
    int LeftTreeBalancing(PTBalanceNode &pNode); // баланс. левого поддерева
    int RightTreeBalancing(PTBalanceNode &pNode);// баланс. правого поддерева
public:
    TBalanceTree() : TTreeTable() {} // конструктор
    //основные методы
    virtual void InsRecord(TKey k, PTDatValue pVal); // вставить
    virtual void DelRecord(TKey k);                   // удалить
};
#endif
