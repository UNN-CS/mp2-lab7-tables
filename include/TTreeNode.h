#ifndef __T_TREE_NODE_H__
#define __T_TREE_NODE_H__

#include "TTabRecord.h"

class  TTreeNode;
typedef  TTreeNode *PTTreeNode;
class  TTreeNode : public TTabRecord {
protected:
	PTTreeNode pLeft, pRight; // óêàçàòåëè íà ïîääåðåâüÿ
public:
	TTreeNode(TKey k = "", PTDatValue pVal = nullptr, PTTreeNode pL = nullptr,
		PTTreeNode pR = nullptr) : TTabRecord(k, pVal), pLeft(pL), pRight(pR) {};
	PTTreeNode GetLeft() const; // óêàçàòåëü íà ëåâîå ïîääåðåâî
	PTTreeNode GetRight() const; // óêàçàòåëü íà ïðàâîå ïîääåðåâî
	virtual TDatValue * GetCopy();  // èçãîòîâèòü êîïèþ
	friend class TTreeTable;
	friend class TBalanceTree;
};


#endif //__T_TREE_NODE_H__