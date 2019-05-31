#ifndef __T_BALANCE_TREE_H__
#define __T_BALANCE_TREE_H__

//#include "TTreeTable.h"
//#include "TBalanceNode.h"
//#include "TTable.h"
//
//class  TBalanceTree: public TTreeTable  {
//    protected: 
//int InsBalanceTree(PTTreeNode &pNode_, TKey k, PTDatValue pVal);
//int LeftTreeBalancing(PTBalanceNode &pNode); // баланс. левого поддерева
//int RightTreeBalancing(PTBalanceNode &pNode);// баланс. правого поддерева
//  public:
//    TBalanceTree():TTreeTable(){} // конструктор
//    //основные методы
//    virtual void InsRecord (TKey k, PTDatValue pVal ); // вставить
//    virtual void DelRecord (TKey k);                   // удалить
//};


#include "TBalanceNode.h"
#include "TTreeTable.h"

class TBalanceTree : public TTreeTable {
protected:
	int InsBalanceTree(PTTreeNode &pNode_, TKey k, PTDatValue pVal);
	int LeftTreeBalancing(PTBalanceNode &pNode); // áàëàíñ. ëåâîãî ïîääåğåâà
	int RightTreeBalancing(PTBalanceNode &pNode);// áàëàíñ. ïğàâîãî ïîääåğåâà
public:
	TBalanceTree() : TTreeTable() {} // êîíñòğóêòîğ
	//îñíîâíûå ìåòîäû
	virtual void InsRecord(TKey k, PTDatValue pVal) override; // âñòàâèòü
};


#endif //__T_BALANCE_TREE_H__