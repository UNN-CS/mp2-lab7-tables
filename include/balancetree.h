#ifndef BALANCETREE_H_
#define BALANCETREE_H_
#include "balancenode.h"
#include "treetable.h"

class TBalanceTree: public TTreeTable {
 protected:
    int InsBalanceTree(PTTreeNode &pNode_, TKey k, PTDatValue pVal);
    int LeftTreeBalancing(PTBalanceNode &pNode); // ������. ������ ���������
    int RightTreeBalancing(PTBalanceNode &pNode);// ������. ������� ���������
 public:
    TBalanceTree() : TTreeTable() {} // �����������
    //�������� ������
    virtual void InsRecord(TKey k, PTDatValue pVal) override; // ��������
};

#endif // BALANCETREE_H_
