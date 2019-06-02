// базовый (абстрактный) класс объектов-значений
#ifndef _TTREENODE_H
#define _TTREENODE_H
#include "TTabRecord.h"
class  TTreeNode;
typedef  TTreeNode *PTTreeNode;
class  TTreeNode : public TTabRecord {
protected:
    PTTreeNode pLeft, pRight; // указатели на поддеревья
public:
    TTreeNode(TKey k = "", PTDatValue pVal = nullptr, PTTreeNode pL = nullptr,
        PTTreeNode pR = nullptr) : TTabRecord(k, pVal), pLeft(pL), pRight(pR) {};
    PTTreeNode GetLeft(void) const { return pLeft; } 
    PTTreeNode GetRight(void) const { return pRight; } 
    virtual TDatValue * GetCopy();  
    friend class TTreeTable;
    friend class TBalanceTree;
};

#endif //_TTREENODE_H