#include "TBalanceTree.h"

PTBalanceNode TBalanceTree::InsBalanceTree(PTBalanceNode root, TKey k, PTDatValue pVal)
{
	Efficiency++;
	if (!root)
	{
		DataCount++;
		return new TBalanceNode(k, pVal);
	}
	if (k < root->GetKey())
		root->pLeft = InsBalanceTree((PTBalanceNode)root->pLeft, k, pVal);
	else if (k > root->GetKey())
		root->pRight = InsBalanceTree((PTBalanceNode)root->pRight, k, pVal);
	return Balance(root);
}

PTBalanceNode TBalanceTree::Balance(PTBalanceNode root)
{
	Efficiency++;
	FixHeight(root);
	if (Bfactor(root) == 2)
	{
		if (Bfactor((PTBalanceNode)root->pRight) < 0)
			root->pRight = RightTreeBalancing((PTBalanceNode)root->pRight);
		return LeftTreeBalancing(root);
	}

	if (Bfactor(root) == -2)
	{
		if (Bfactor((PTBalanceNode)root->pLeft) > 0)
			root->pLeft = LeftTreeBalancing((PTBalanceNode)root->pLeft);
		return RightTreeBalancing(root);
	}
	return root;
}

int TBalanceTree::Height(PTBalanceNode root)
{
	return root ? root->GetBalance() : 0;
}

void TBalanceTree::FixHeight(PTBalanceNode root)
{
	int hl = Height((PTBalanceNode)root->pLeft);
	int hr = Height((PTBalanceNode)root->pRight);
	root->Balance = ((hl > hr) ? hl : hr) + 1;
}

int TBalanceTree::Bfactor(PTBalanceNode root)
{
	return Height((PTBalanceNode)root->pRight) - Height((PTBalanceNode)root->pLeft);
}

PTBalanceNode TBalanceTree::FindMin(PTBalanceNode root)
{
	Efficiency++;
	return root->pLeft ? FindMin((PTBalanceNode)root->pLeft) : root;
}

PTBalanceNode TBalanceTree::DeleteMin(PTBalanceNode root)
{
	Efficiency++;
	if (!root->pLeft)
		return (PTBalanceNode)root->pRight;
	root->pLeft = DeleteMin((PTBalanceNode)root->pLeft);
	return Balance(root);
}


PTBalanceNode TBalanceTree::LeftTreeBalancing(PTBalanceNode q)
{
	PTBalanceNode p = (PTBalanceNode)q->pRight;
	q->pRight = p->pLeft;
	p->pLeft = q;
	FixHeight(q);
	FixHeight(p);
	return p;
}

PTBalanceNode TBalanceTree::RightTreeBalancing(PTBalanceNode p)
{
	PTBalanceNode q = (PTBalanceNode)p->pLeft;
	p->pLeft = q->pRight;
	q->pRight = p;
	FixHeight(p);
	FixHeight(q);
	return q;
}

PTBalanceNode TBalanceTree::Delete(PTBalanceNode root, TKey k)
{
	Efficiency++;
	if (!root)
		return nullptr;
	if (k < root->GetKey())
		root->pLeft = Delete((PTBalanceNode)root->pLeft, k);
	else if (k > root->GetKey())
		root->pRight = Delete((PTBalanceNode)root->pRight, k);
	else
	{
		PTBalanceNode q = (PTBalanceNode)root->pLeft;
		PTBalanceNode r = (PTBalanceNode)root->pRight;
		delete root;
		DataCount--;
		if (!r)
			return q;
		PTBalanceNode min = FindMin(r);
		min->pRight = DeleteMin(r);
		min->pLeft = q;
		return Balance(min);
	}
	return Balance(root);
}

void TBalanceTree::InsRecord(TKey k, PTDatValue pVal)
{
	pRoot = InsBalanceTree((PTBalanceNode)pRoot, k, pVal);
}

void TBalanceTree::DelRecord(TKey k)
{
	pRoot = Delete((PTBalanceNode)pRoot, k);
}

int TBalanceTree::GetBal()
{
	return Height((PTBalanceNode)pCurrent);
}

int TBalanceTree::GetBFct()
{
	return Bfactor((PTBalanceNode)pCurrent);
}