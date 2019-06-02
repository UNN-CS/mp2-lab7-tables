#include "TBalanceTree.h"
#include <stack>
#include <queue>

int TBalanceTree::InsBalanceTree(PTBalanceNode &pNode, TKey& k, PTDatValue pVal)
{
	++Efficiency;
	if (pNode == nullptr)
	{
		pNode = new TBalanceNode(k, pVal);
		++DataCount;
		return 1;
	}
	if (pNode->GetKey() == k)
	{
		pNode->SetValuePtr(pVal);
		return 0;
	}
	if (pNode->GetKey() > k)
	{
		PTBalanceNode b = (PTBalanceNode)pNode->GetLeft();
		if (InsBalanceTree(b, k, pVal))
		{
			pNode->pLeft = b;
			return LeftTreeBalancing(pNode);
		}
		else
			pNode->pLeft = b;
	}
	else
	{
		PTBalanceNode b = (PTBalanceNode)pNode->GetRight();
		if (InsBalanceTree(b, k, pVal))
		{
			pNode->pRight = b;
			return RightTreeBalancing(pNode);
		}
		else
			pNode->pRight = b;
	}
	return 0;
}

int TBalanceTree::LeftTreeBalancing(PTBalanceNode &pNode)
{
	switch (pNode->GetBalance())
	{
	case BalRight:
		pNode->SetBalance(BalOk);
		return 0;
	case BalOk:
		pNode->SetBalance(BalLeft);
		return 1;
	case BalLeft:
		PTBalanceNode n1 = (PTBalanceNode)(pNode->GetLeft());
		if (n1->GetBalance() == BalLeft)
		{
			pNode->pLeft = n1->pRight;
			n1->pRight = pNode;
			pNode->SetBalance(BalOk);
			pNode = n1;
			pNode->SetBalance(BalOk);
			return 0;
		}
		else if (n1->GetBalance() == BalRight)
		{
			PTBalanceNode n2 = (PTBalanceNode)(n1->GetRight());
			pNode->pLeft = n2->GetRight();
			n1->pRight = n2->GetLeft();
			n2->pLeft = n1;
			n2->pRight = pNode;
			if (n2->GetBalance() == BalLeft)
				pNode->SetBalance(BalRight);
			else
				pNode->SetBalance(BalOk);
			if (n2->GetBalance() == BalRight)
				n1->SetBalance(BalLeft);
			else
				n1->SetBalance(BalOk);
			pNode = n2;
			pNode->SetBalance(BalOk);
			return 0;
		}
		else
		{
			pNode->pLeft = n1->pRight;
			n1->pRight = pNode;
			pNode->SetBalance(BalLeft);
			pNode = n1;
			pNode->SetBalance(BalRight);
			return 1;
		}
	}
	return 0;
}

int TBalanceTree::RightTreeBalancing(PTBalanceNode &pNode)
{
	switch (pNode->GetBalance())
	{
	case BalLeft:
		pNode->SetBalance(BalOk);
		return 0;
	case BalOk:
		pNode->SetBalance(BalRight);
		return 1;
	case BalRight:
		PTBalanceNode n1 = (PTBalanceNode)(pNode->GetRight());
		if (n1->GetBalance() == BalRight)
		{
			pNode->pRight = n1->pLeft;
			n1->pLeft = pNode;
			pNode->SetBalance(BalOk);
			pNode = n1;
			pNode->SetBalance(BalOk);
			return 0;
		}
		else if (n1->GetBalance() == BalLeft)
		{
			PTBalanceNode n2 = (PTBalanceNode)(n1->GetLeft());
			pNode->pRight = n2->GetLeft();
			n1->pLeft = n2->GetRight();
			n2->pRight = n1;
			n2->pLeft = pNode;
			if (n2->GetBalance() == BalRight)
				pNode->SetBalance(BalLeft);
			else
				pNode->SetBalance(BalOk);
			if (n2->GetBalance() == BalLeft)
				n1->SetBalance(BalRight);
			else
				n1->SetBalance(BalOk);
			pNode = n2;
			pNode->SetBalance(BalOk);
			return 0;
		}
		else
		{
			pNode->pRight = n1->pLeft;
			n1->pLeft = pNode;
			pNode->SetBalance(BalRight);
			pNode = n1;
			pNode->SetBalance(BalLeft);
			return 1;
		}
	}
	return 0;
}

void TBalanceTree::InsRecord(TKey k, PTDatValue pVal)
{
	PTBalanceNode n = (PTBalanceNode)pRoot;
	InsBalanceTree(n, k, pVal);
	pRoot = n;
}
