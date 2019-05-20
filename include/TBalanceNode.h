#define BalOk 0
#define BalLeft -1
#define BalRight 1
class  TBalanceNode: public TTreeNode {
  protected: 
    int Balance; // индекс балансировки вершины (-1,0,1)
  public:
    TBalanceNode (TKey k=ФФ, PTDatValue pVal=NULL, PTTreeNode pL=NULL,
      PTTreeNode pR=NULL, int bal=BalOk) ): TTreeNode(k,pVal,pL,pR), 
      Balance(bal) {}; // конструктор
    virtual TDatValue * GetCopy();  // изготовить копию
    int GetBalance(void) const;
    void SetBalance(int bal);
   friend class TBalanceTree;
};
