#ifndef __T_BALANCE_NODE_H__
#define __T_BALANCE_NODE_H__

#include "ttreenode.h"

#define BalOK 0
#define BalLeft -1
#define BalRight 1

class TBalanceNode: public TTreeNode {
  protected:
    int Balance; // ������ ������������ ������� (-1,0,1)
  public:
    TBalanceNode (TKey k="", PTDatValue pVal=nullptr, PTTreeNode pL=nullptr,
      PTTreeNode pR=nullptr, int bal=BalOK): TTreeNode(k,pVal,pL,pR),
      Balance(bal) {}; // �����������
    virtual TDatValue * GetCopy();  // ���������� �����
    int GetBalance() const;
    void SetBalance(int bal);
   friend class TBalanceTree;
};

typedef TBalanceNode* PTBalanceNode;

#endif // __T_BALANCE_NODE_H__

