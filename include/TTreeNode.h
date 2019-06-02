// TTreeNode.h
#ifndef _TREENODE_H
#define _TREENODE_H
#include "TTabRecord.h"
class  TTreeNode;
typedef  TTreeNode *PTTreeNode;
class  TTreeNode : public TTabRecord {
protected:
    PTTreeNode pLeft, pRight; // указатели на поддеревья
public:
    TTreeNode(TKey k = "", PTDatValue pVal = nullptr, PTTreeNode pL = nullptr,
        PTTreeNode pR = nullptr) : TTabRecord(k, pVal), pLeft(pL), pRight(pR) {};
    PTTreeNode GetLeft(void) const { return pLeft; } // указатель на левое поддерево
    PTTreeNode GetRight(void) const { return pRight; } // указатель на правое поддерево
    virtual TDatValue * GetCopy();  // изготовить копию
    friend class TTreeTable;
    friend class TBalanceTree;
};

#endif