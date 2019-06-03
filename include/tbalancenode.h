// Базовый класс объектов-значений для сбалансированных деревьев

#pragma once

#include "ttreenode.h"

#define BalOk 0
#define BalLeft -1
#define BalRight 1

class TBalanceNode;
typedef TBalanceNode *PTBalanceNode;

class  TBalanceNode: public TTreeNode {
  protected: 
    int balance;                                                         // индекс балансировки вершины (-1,0,1)

  public:
    TBalanceNode (TKey k="", PTDatValue pVal=NULL, PTTreeNode pL=NULL,
                  PTTreeNode pR=NULL, int bal=BalOk) :
                  TTreeNode(k, pVal, pL, pR), balance(bal) {};           // конструктор
    virtual TDatValue * GetCopy();                                       // изготовить копию
    int GetBalance() const;
    void SetBalance(int bal);

   friend class TBalanceTree;
};
