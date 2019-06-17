#ifndef _BALTREE_H
#define _BALTREE_H

#include "TTreeTab.h"
#include"TBalanceNode.h"

#define HeightOK 0
#define HeightInc 1

class  TBalanceTree : public TTreeTable
{
protected:
	int InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal);
	int DelBalanceTree(PTBalanceNode &pNode, TKey k, PTBalanceNode &pParent);
	int LeftTreeBalancing(PTBalanceNode &pNode); // баланс. левого поддерева
	int RightTreeBalancing(PTBalanceNode &pNode);// баланс. правого поддерева 

public:
	TBalanceTree() :TTreeTable() {} // конструктор

	//основные методы
	virtual void InsRecord(TKey k, PTDatValue pVal); // вставить
	virtual void DelRecord(TKey k);                  // удалить
};
#endif
