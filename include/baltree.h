#ifndef __BALTREE_H
#define __BALTREE_H

#include "treetab.h"
#include "balnode.h"

#define HeighOK 0
#define HeighInc 1

class TBalanceTree : public TTreeTable {
protected:
    int InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal);
    int LeftTreeBalancing(PTBalanceNode &pNode); // ������. ������ ���������
    int RightTreeBalancing(PTBalanceNode &pNode);// ������. ������� ���������
public:
    TBalanceTree() :TTreeTable() {} // �����������
    //�������� ������
    virtual void InsRecord(TKey k, PTDatValue pVal); // ��������
};

#endif
