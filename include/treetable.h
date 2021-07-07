#pragma once

#include "defines.h"

#include "table.h"

#include <stack>

class TTreeTable : public TTable {
  public:
    TTreeTable();
    ~TTreeTable();

    virtual bool IsFull() const override;

    virtual PTDatValue FindRecord(TKey k) override;
    virtual void InsRecord(TKey k, PTDatValue pVal) override;
    virtual void DelRecord(TKey k) override;

    virtual TKey GetKey() const override;
    virtual PTDatValue GetValuePtr() const override;

    virtual bool Reset() override;
    virtual bool IsTabEnded() const override;
    virtual bool GoNext() override;

  protected:
    void DeleteTreeTab(PTTreeNode pNode);

    PTTreeNode pRoot;
    PTTreeNode *ppRef;
    PTTreeNode pCurrent;
    int currPos;
    std::stack<PTTreeNode> st;
};
