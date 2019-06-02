#ifndef __BALANCETREE_H__
#define __BALANCETREE_H__

#include "TTreeTable.h"
#include "TBalanceNode.h"

#define HeightOK 0
#define HeightInc 1

class  TBalanceTree : public TTreeTable {
protected:
	PTBalanceNode InsBalanceTree(PTBalanceNode pNode, TKey k, PTDatValue pVal);
	PTBalanceNode Balance(PTBalanceNode pNode);
	void FixHeight(PTBalanceNode pNode);
	int Height(PTBalanceNode pNode);
	int Bfactor(PTBalanceNode pNode);
	PTBalanceNode FindMin(PTBalanceNode pNode);
	PTBalanceNode DeleteMin(PTBalanceNode pNode);
	PTBalanceNode LeftTreeBalancing(PTBalanceNode pNode); // баланс. левого поддерева
	PTBalanceNode RightTreeBalancing(PTBalanceNode pNode);// баланс. правого поддерева
	PTBalanceNode Delete(PTBalanceNode pNode, TKey k);
public:
	TBalanceTree() :TTreeTable() {} // конструктор
	//основные методы
	virtual void InsRecord(TKey k, PTDatValue pVal = nullptr); // вставить
	virtual void DelRecord(TKey k);                   // удалить
	int GetBal();
	int GetBFct();
};

#endif