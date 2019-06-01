#ifndef __T_BALANCE_TREE_H__
#define __T_BALANCE_TREE_H__

#include "tbalancenode.h"
#include "ttreetable.h"

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