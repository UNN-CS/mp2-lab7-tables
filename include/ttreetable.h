#ifndef __TREETABLE_H__
#define __TREETABLE_H__

#include <stack>

#include "ttable.h"
#include "ttreenode.h"

class TTreeTable: public TTable {
protected:
    PTTreeNode pRoot;
    PTTreeNode* ppRef;
    PTTreeNode pCurrent;
    int CurrPos;
    std::stack<PTTreeNode> St;
    void DeleteTreeTab(PTTreeNode pNode);
public:
    TTreeTable(): TTable() {
        CurrPos = 0;
        pRoot = pCurrent = nullptr;
        ppRef = nullptr;
    }
    ~TTreeTable() { DeleteTreeTab(pRoot); }
    virtual int IsFull() const;
    virtual PTDatValue FindRecord(TKey k);
    virtual void InsRecord(TKey k, PTDatValue pVal);
    virtual void DelRecord(TKey k);
    virtual TKey GetKey() const;
    virtual PTDatValue GetValuePtr() const;
    virtual int Reset();
    virtual int IsTabEnded() const;
    virtual int GoNext();
};

#endif
