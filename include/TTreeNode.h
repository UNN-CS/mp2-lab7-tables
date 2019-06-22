#pragma once
#include "TTabRecord.h"
#include <iostream>
using namespace std;

class  TTreeNode;
typedef  TTreeNode *PTTreeNode;
class  TTreeNode: public TTabRecord {
  protected: 
    PTTreeNode pLeft, pRight; // указатели на поддеревья
  public:
    TTreeNode(TKey k="", PTDatValue pVal=NULL, PTTreeNode pL=NULL, 
      PTTreeNode pR=NULL ): TTabRecord(k,pVal), pLeft(pL), pRight(pR) {};
    PTTreeNode GetLeft(void) const {
        return pLeft;
    }; // указатель на левое поддерево
    PTTreeNode GetRight(void) const {
        return pRight;
    }; // указатель на правое поддерево
    virtual TDatValue * GetCopy();  // изготовить копию
  friend class TTreeTable;
  friend class TBalanceTree;
};