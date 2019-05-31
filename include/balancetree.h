#ifndef __baltree_h
#define __baltree_h

#include "treetab.h"
#include "balancenode.h"

#define HeightOK 0
#define HeightInc 1

class BalanceTree :public TreeTable {
 protected:
	int InsBalanceTree(PTreeNode& pNode, TKey k, PTDatValue pVal); // �������� ������ � ������������� 
	int LeftTreeBalancing(PTreeNode & pNode); // �������� ������ ���������
	int RightTreeBalancing(PTreeNode& pNode); // �������� ������� ���������
 public:
	BalanceTree() :TreeTable() {};
	// �������� ������
	virtual void InsRecord(TKey k, PTDatValue pVal); // �������� ������
	virtual void DelRecord(TKey k); // ������� ������ 
};
#endif