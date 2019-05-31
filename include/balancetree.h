#ifndef __baltree_h
#define __baltree_h

#include "treetab.h"
#include "balancenode.h"

#define HeightOK 0
#define HeightInc 1

class BalanceTree :public TreeTable {
 protected:
	int InsBalanceTree(PTreeNode& pNode, TKey k, PTDatValue pVal); // вставить запись с балансировкой 
	int LeftTreeBalancing(PTreeNode & pNode); // балансир левого поддерева
	int RightTreeBalancing(PTreeNode& pNode); // балансир правого поддерева
 public:
	BalanceTree() :TreeTable() {};
	// основные методы
	virtual void InsRecord(TKey k, PTDatValue pVal); // вставить запись
	virtual void DelRecord(TKey k); // удалить запись 
};
#endif