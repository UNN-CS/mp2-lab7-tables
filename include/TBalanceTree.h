// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tbalancetree.h
//
// ����� ��� ���������������� ��������

#ifndef __TBALANCETREE_H
#define __TBALANCETREE_H

#include "TTreeTable.h"
#include "TBalanceNode.h"

class  TBalanceTree: public TTreeTable  {
    protected: 
int InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal);
int LeftTreeBalancing(PTBalanceNode &pNode); // ������. ������ ���������
int RightTreeBalancing(PTBalanceNode &pNode);// ������. ������� ���������
int DeleteBalTree(PTBalanceNode &pNode, TKey k);
int RightDelBalancing(PTBalanceNode& pNode);
int LeftDelBalancing(PTBalanceNode& pNode);
int DelNode(PTBalanceNode& pNode, PTBalanceNode& pParent);
  public:
    TBalanceTree():TTreeTable(){} // �����������
    //�������� ������
    virtual void InsRecord (TKey k, PTDatValue pVal ); // ��������
    virtual void DelRecord (TKey k);                   // �������
};

#endif