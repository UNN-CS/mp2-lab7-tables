#ifndef __T_TREE_NODE_H__
#define __T_TREE_NODE_H__

class  TTreeNode;
typedef  TTreeNode *PTTreeNode;
class  TTreeNode: public TTabRecord {
  protected:
    PTTreeNode pLeft, pRight; // указатели на поддеревь€
  public:
    TTreeNode(TKey k=ФФ, PTDatValue pVal=NULL, PTTreeNode pL=NULL,
      PTTreeNode pR=NULL ): TTabRecord(k,pVal), pLeft(pL), pRight(pR) {};
    PTTreeNode GetLeft(void) const; // указатель на левое поддерево
   PTTreeNode GetRight(void) const; // указатель на правое поддерево
    virtual TDatValue * GetCopy();  // изготовить копию
  friend class TTreeTable;
  friend class TBalanceTree;
};

#endif // __T_TREE_NODE_H__
