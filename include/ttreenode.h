#ifndef __TREENODE_H__
#define __TREENODE_H__

#include "ttabrecord.h"

class TTreeNode;
typedef TTreeNode* PTTreeNode;

class TTreeNode: public TTabRecord {
protected:
    PTTreeNode pLeft, pRight;
public:
    TTreeNode(TKey k = "", PTDatValue pVal = nullptr, PTTreeNode pL = nullptr,
        PTTreeNode pR = nullptr): TTabRecord(k, pVal), pLeft(pL), pRight(pR) {};
    PTTreeNode GetLeft() const;
    PTTreeNode GetRight() const;
    virtual TDatValue* GetCopy();
    friend class TTreeTable;
    friend class TBalanceTree;
};

#endif
