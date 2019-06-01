#ifndef __TBALANCE_TREE_H__
#define __TBALANCE_TREE_H__

#include "TTreeTable.h"
#include "TBalanceNode.h"

class  TBalanceTree : public TTreeTable {
protected:
	int InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal);
	int LeftTreeBalancing(PTBalanceNode &pNode); // баланс. левого поддерева
	int RightTreeBalancing(PTBalanceNode &pNode);// баланс. правого поддерева
public:
	TBalanceTree() :TTreeTable() {} // конструктор
									//основные методы
	virtual void InsRecord(TKey k, PTDatValue pVal); // вставить
	virtual void DelRecord(TKey k);                   // удалить
};

#endif // __TBALANCE_TREE_H__