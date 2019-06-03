#pragma once

#include <stack>

#include "ttable.hpp"
#include "ttreenode.hpp"

class TTreeTable : public TTable
{
protected:
    PTTreeNode pRoot;          // tree root pointer
    PTTreeNode *ppRef;         // FindRecord top-result pointer address
    PTTreeNode pCurrent;       // current node pointer
    int CurrPos;               // current node number
    std::stack<PTTreeNode> St; // iterator stack

    void DeleteTreeTab(PTTreeNode pNode);

public:
    TTreeTable() : TTable()
    {
        CurrPos = 0;
        pRoot = pCurrent = nullptr;
        ppRef = nullptr;
    }
    ~TTreeTable() { DeleteTreeTab(pRoot); }
    // misc methods
    virtual int IsFull() const override;
    // core methods
    virtual PTDatValue FindRecord(TKey k) override;
    virtual void InsRecord(TKey k, PTDatValue pVal) override;
    virtual void DelRecord(TKey k) override;
    void Print(PTTreeNode pNode, int depth = 0);
    void Print() { Print(pRoot); }
    // navigation
    virtual TKey GetKey() const;
    virtual PTDatValue GetValuePtr() const;
    virtual int Reset() override;
    virtual int IsTabEnded() const override;
    virtual int GoNext() override;
};
