#ifndef __treenode_h
#define __treenode_h

#include <iostream>
#include "TTabRecord.h"

class TreeNode;
typedef TreeNode* PTreeNode;

class TreeNode : public TRecord {
 protected:
	 PTreeNode pLeft, pRight; // указатели на поддеревья
 public:
	TreeNode(TKey k = "", PTDatValue pVal = NULL, PTreeNode pl = NULL, PTreeNode pr = NULL) :TRecord(k, pVal), pLeft(pl), pRight(pr) {};
	PTreeNode GetLeft() const { return pLeft; }
	PTreeNode GetRight() const { return pRight; }
	virtual TDatValue* GetCopy(); // изготовить копию
	virtual void Print(); // напечатать звено
	friend class TreeTable;
	friend class BalanceTree;
};
#endif 