// ����, ���, ���� "������ ����������������-2", �++, ���
//
// ttreenode.h
//
// ������� ����� ��������-�������� ��� ���������������� ��������

#ifndef __TBALANCENODE_H
#define __TBALANCENODE_H

#include "TTreeNode.h"

class  TBalanceNode;
typedef  TBalanceNode *PTBalanceNode;

#define BalOk 0
#define BalLeft -1
#define BalRight 1
class  TBalanceNode: public TTreeNode {
  protected: 
    int Balance; // ������ ������������ ������� (-1,0,1)
  public:
    TBalanceNode (TKey k="", PTDatValue pVal=nullptr, PTTreeNode pL=nullptr,
      PTTreeNode pR=nullptr, int bal=BalOk) : TTreeNode(k,pVal,pL,pR), 
      Balance(bal) {}; // �����������
    virtual TDatValue * GetCopy();  // ���������� �����
    int GetBalance(void) const;
    void SetBalance(int bal);
   friend class TBalanceTree;
};

#endif