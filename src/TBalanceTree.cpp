#include "TBalanceTree.h"
#include <stack>
#include <queue>

int TBalanceTree::InsBalanceTree(PTBalanceNode& pNode, TKey& k, PTDatValue pVal)
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
		PTBalanceNode p = (PTBalanceNode)pNode->GetLeft();
		if (InsBalanceTree(p, k, pVal))
		{
			pNode->pLeft = p;
			return LeftTreeBalancing(pNode);
		}
		else
			pNode->pLeft = p;
	}
	else
	{
		PTBalanceNode p = (PTBalanceNode)pNode->GetRight();
		if (InsBalanceTree(p, k, pVal))
		{
			pNode->pRight = p;
			return RightTreeBalancing(pNode);
		}
		else
			pNode->pRight = p;
	}
	return 0;
}

int TBalanceTree::LeftTreeBalancing(PTBalanceNode& pNode)
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
		PTBalanceNode p = dynamic_cast<PTBalanceNode>(pNode->GetLeft());
		if (p->GetBalance() == BalLeft)
		{
			pNode->pLeft = p->pRight;
			p->pRight = pNode;
			pNode->SetBalance(BalOk);
			pNode = p;
			pNode->SetBalance(BalOk);
			return 0;
		}
		else if (p->GetBalance() == BalRight)
		{
			PTBalanceNode q = dynamic_cast<PTBalanceNode>(p->GetRight());
			pNode->pLeft = q->GetRight();
			p->pRight = q->GetLeft();
			q->pLeft = p;
			q->pRight = pNode;
			if (q->GetBalance() == BalLeft)
				pNode->SetBalance(BalRight);
			else
				pNode->SetBalance(BalOk);
			if (q->GetBalance() == BalRight)
				p->SetBalance(BalLeft);
			else
				p->SetBalance(BalOk);
			pNode = q;
			pNode->SetBalance(BalOk);
			return 0;
		}
		else
		{
			pNode->pLeft = p->pRight;
			p->pRight = pNode;
			pNode->SetBalance(BalLeft);
			pNode = p;
			pNode->SetBalance(BalRight);
			return 1;
		}
	}
	return 0;
}

int TBalanceTree::RightTreeBalancing(PTBalanceNode& pNode)
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
		PTBalanceNode p = dynamic_cast<PTBalanceNode>(pNode->GetRight());
		if (p->GetBalance() == BalRight)
		{
			pNode->pRight = p->pLeft;
			p->pLeft = pNode;
			pNode->SetBalance(BalOk);
			pNode = p;
			pNode->SetBalance(BalOk);
			return 0;
		}
		else if (p->GetBalance() == BalLeft)
		{
			PTBalanceNode q = dynamic_cast<PTBalanceNode>(p->GetLeft());
			pNode->pRight = q->GetLeft();
			p->pLeft = q->GetRight();
			q->pRight = p;
			q->pLeft = pNode;
			if (q->GetBalance() == BalRight)
				pNode->SetBalance(BalLeft);
			else
				pNode->SetBalance(BalOk);
			if (q->GetBalance() == BalLeft)
				p->SetBalance(BalRight);
			else
				p->SetBalance(BalOk);
			pNode = q;
			pNode->SetBalance(BalOk);
			return 0;
		}
		else
		{
			pNode->pRight = p->pLeft;
			p->pLeft = pNode;
			pNode->SetBalance(BalRight);
			pNode = p;
			pNode->SetBalance(BalLeft);
			return 1;
		}
	}
	return 0;
}

void TBalanceTree::InsRecord(TKey k, PTDatValue pVal)
{
	PTBalanceNode p = (PTBalanceNode)pRoot;
	InsBalanceTree(p, k, pVal);
	pRoot = p;
}

void TBalanceTree::DelRecord(TKey k)
{
	struct balance
	{
		PTBalanceNode* p;
		bool d;
	};

	bool flag = true;
	std::stack<balance> s;
	PTBalanceNode* p = (PTBalanceNode*)& pRoot;
	while ((*p) != nullptr)
	{
		if ((*p)->GetKey() > k)
		{
			s.push({ p, 0 });
			p = (PTBalanceNode*) & (*p)->pLeft;
		}
		else if ((*p)->GetKey() < k)
		{
			s.push({ p, 1 });
			p = (PTBalanceNode*) & (*p)->pRight;
		}
		else
		{
			--DataCount;
			flag = false;
			PTBalanceNode l = (PTBalanceNode)(*p)->pLeft;
			PTBalanceNode r = (PTBalanceNode)(*p)->pRight;
			int bal = (*p)->GetBalance();
			delete (*p);
			if (l == nullptr)
				* p = r;
			else if (r == nullptr)
				* p = l;
			else if (r->pLeft == nullptr)
			{
				r->pLeft = l;
				*p = r;
				r->SetBalance(bal);
				s.push({ p, 1 });
			}
			else
			{
				PTBalanceNode* q = (PTBalanceNode*)& r->pLeft;
				std::queue<PTBalanceNode*> qu;
				while ((*q)->pLeft != nullptr)
				{
					qu.push(q);
					q = (PTBalanceNode*) & (*q)->pLeft;
				}
				*p = *q;
				*q = (PTBalanceNode)(*q)->pRight;
				(*p)->pRight = r;
				(*p)->pLeft = l;
				(*p)->SetBalance(bal);
				s.push({ p, 1 });
				s.push({ (PTBalanceNode*) & (*p)->pRight, 0 });
				while (qu.size())
				{
					s.push({ qu.front(), 0 });
					qu.pop();
				}
			}
			break;
		}
	}
	Efficiency += s.size() + 1;
	while (s.size() && (!flag))
	{
		balance b = s.top();
		s.pop();
		if (b.d)
			flag = LeftTreeBalancing(*b.p);
		else
			flag = RightTreeBalancing(*b.p);
	}
}