// Абстрактный базовый класс объектов-значений для деревьев

#pragma once

#include "ttabrecord.h"

class  TTreeNode;
typedef  TTreeNode *PTTreeNode;

class  TTreeNode: public TTabRecord {
  protected: 
    PTTreeNode pLeft, pRight;                                                       // указатели на поддеревья

  public:
    TTreeNode(TKey k="", PTDatValue pVal=NULL, PTTreeNode pL=NULL, 
              PTTreeNode pR=NULL ): TTabRecord(k, pVal), pLeft(pL), pRight(pR) {};
    PTTreeNode GetLeft() const;                                                     // указатель на левое поддерево
    PTTreeNode GetRight() const;                                                    // указатель на правое поддерево
    virtual TDatValue * GetCopy();                                                  // изготовить копию

  friend class TTreeTable;
  friend class TBalanceTree;
};
