#include "TBalanceTree.h"

#define HeightOk 0
#define HeightInc 1

void TBalanceTree::InsRecord(TKey k, PTDatValue pVal) {
	if (IsFull())
		throw - 1;
	InsBalanceTree(pRoot, k, pVal);
}

int TBalanceTree::InsBalanceTree(PTTreeNode &pNode_, TKey k, PTDatValue pVal) {
	++Efficiency;
	PTBalanceNode pNode = (PTBalanceNode)pNode_;
	int hIndex = HeightOk;
	if (!pNode) {
		pNode = new TBalanceNode(k, pVal);
		pNode_ = pNode;
		hIndex = HeightInc;
		++DataCount;
	}
	else if (k < pNode->GetKey()) {
		if (InsBalanceTree(pNode->pLeft, k, pVal) == HeightInc) {
			hIndex = LeftTreeBalancing(pNode);
			pNode_ = pNode;
		}
	}
	else if (k > pNode->GetKey()) {
		if (InsBalanceTree(pNode->pRight, k, pVal) == HeightInc) {
			hIndex = RightTreeBalancing(pNode);
			pNode_ = pNode;
		}
	}
	else {
		hIndex = HeightOk;
	}
	pNode_ = pNode;
	return hIndex;
}

int TBalanceTree::LeftTreeBalancing(PTBalanceNode &pNode) {
	int hIndex = HeightOk;
	switch (pNode->GetBalance()) {
	case BalRight:
		pNode->SetBalance(BalOk);
		hIndex = HeightOk;
		break;
	case BalOk:
		pNode->SetBalance(BalLeft);
		hIndex = HeightInc;
		break;
	case BalLeft:
		PTBalanceNode p1, p2;
		p1 = PTBalanceNode(pNode->pLeft);
		if (p1->GetBalance() == BalLeft) { // 1 x LL
			pNode->pLeft = p1->pRight;
			p1->pRight = pNode;
			pNode->SetBalance(BalOk);
			pNode = p1;
		}
		else if (p1->GetBalance() == BalRight) { // 2 x LR
			p2 = PTBalanceNode(p1->pRight);
			p1->pRight = p2->pLeft;
			p2->pLeft = p1;
			pNode->pLeft = p2->pRight;
			p2->pRight = pNode;
			if (p2->GetBalance() == BalLeft)
				pNode->SetBalance(BalRight);
			else
				pNode->SetBalance(BalOk);
			if (p2->GetBalance() == BalRight)
				p1->SetBalance(BalLeft);
			else
				p1->SetBalance(BalOk);
			pNode = p2;
		}
		else {
			pNode->pLeft = p1->pRight;
			p1->pRight = pNode;
			pNode->SetBalance(BalLeft);
			pNode = p1;
			pNode->SetBalance(BalRight);
			return HeightInc;
		}
		pNode->SetBalance(BalOk);
		hIndex = 0;
	}
	return hIndex;
}

int TBalanceTree::RightTreeBalancing(PTBalanceNode &pNode) {
	int hIndex = HeightOk;
	switch (pNode->GetBalance()) {
	case BalLeft:
		pNode->SetBalance(BalOk);
		hIndex = HeightOk;
		break;
	case BalOk:
		pNode->SetBalance(BalRight);
		hIndex = HeightInc;
		break;
	case BalRight:
		PTBalanceNode p1, p2;
		p1 = PTBalanceNode(pNode->pRight);
		if (p1->GetBalance() == BalRight) {
			pNode->pRight = p1->pLeft;
			p1->pLeft = pNode;
			pNode->SetBalance(BalOk);
			pNode = p1;
		}
		else if (p1->GetBalance() == BalLeft) {
			p2 = PTBalanceNode(p1->pLeft);
			pNode->pRight = p2->pLeft;
			p1->pLeft = p2->pRight;
			p2->pRight = p1;
			p2->pLeft = pNode;
			if (p2->GetBalance() == BalRight)
				pNode->SetBalance(BalLeft);
			else
				pNode->SetBalance(BalOk);
			if (p2->GetBalance() == BalLeft)
				pNode->SetBalance(BalRight);
			else
				pNode->SetBalance(BalOk);
			pNode = p2;
		}
		else {
			pNode->pRight = p1->pLeft;
			p1->pLeft = pNode;
			pNode->SetBalance(BalRight);
			pNode = p1;
			pNode->SetBalance(BalLeft);
			return HeightInc;
		}
		pNode->SetBalance(BalOk);
		hIndex = 0;
	}
	return hIndex;
}