#pragma once

#include "ttabrecord.hpp"

class TTreeNode;
typedef TTreeNode *PTTreeNode;

class TTreeNode : public TTabRecord
{
protected:
    PTTreeNode pLeft, pRight; // tree pointers
public:
    TTreeNode(TKey k = "", PTDatValue pVal = nullptr, PTTreeNode pL = nullptr,
              PTTreeNode pR = nullptr) : TTabRecord(k, pVal), pLeft(pL), pRight(pR){};
    // misc methods
    PTTreeNode GetLeft() const;  // left sub-tree pointer
    PTTreeNode GetRight() const; // right sub-tree pointer
    virtual TDatValue *GetCopy(){return new TTreeNode(Key, pValue, nullptr, nullptr)};
    //friend classes
    friend class TTreeTable;
    friend class TBalanceTree;
};
