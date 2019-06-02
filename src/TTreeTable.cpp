#include "TTreeTable.h"

PTTreeNode TTreeTable::InsNode(PTTreeNode root, TKey k, PTDatValue pVal)
{
	Efficiency++;
	if (root == nullptr)
	{
		root = new TTreeNode(k, pVal);
		DataCount++;
	}
	else if (root->GetKey() > k)
		root->pLeft = InsNode(root->pLeft, k, pVal);
	else if (root->GetKey() < k)
		root->pRight = InsNode(root->pRight, k, pVal);
	return root;
}

PTDatValue TTreeTable::SearchNode(PTTreeNode root, TKey k)
{
	Efficiency++;
	if (root == nullptr)
		return nullptr;
	else if (root->GetKey() > k)
		return SearchNode(root->pLeft, k);
	else if (root->GetKey() < k)
		return SearchNode(root->pRight, k);
	else
		return root->GetValuePTR();
}

PTTreeNode TTreeTable::DeleteNode(PTTreeNode root, TKey k)
{
	Efficiency++;
	PTTreeNode p, v;
	if (root == nullptr)
		return nullptr;
	else if (root->GetKey() > k)
		root->pLeft = DeleteNode(root->pLeft, k);
	else if (root->GetKey() < k)
		root->pRight = DeleteNode(root->pRight, k);
	else
	{
		p = root;
		if (root->GetRight() == nullptr)
			root = root->GetLeft();
		else if (root->GetLeft() == nullptr)
			root = root->GetRight();
		else
		{
			v = root->GetLeft();
			if (v->GetRight())
			{
				while (v->GetRight()->GetRight())
				{
					v = v->GetRight();
					Efficiency++;
				}
				root->SetKey(v->GetKey());
				root->SetValuePtr(v->GetValuePTR());
				p = v->GetRight();
				v->pRight = v->pRight->pLeft;
			}
			else
			{
				root->SetKey(v->GetKey());
				root->SetValuePtr(v->GetValuePTR());
				p = v;
				root->pLeft = root->pLeft->pLeft;
			}
		}
		delete p;
		DataCount--;
	}
	return root;
}

void TTreeTable::DeleteTreeTab(PTTreeNode pNode)
{
	if (pNode)
	{
		DeleteTreeTab(pNode->pLeft);
		DeleteTreeTab(pNode->pRight);
		delete pNode;
	}
}

TTreeTable::TTreeTable() : TTable()
{
	CurrPos = 0;
	pRoot = pCurrent = nullptr;
	ppRef = nullptr;
}

TTreeTable::~TTreeTable()
{
	DeleteTreeTab(pRoot);
}

int TTreeTable::IsFull() const
{
	return 0;
}

PTDatValue TTreeTable::FindRecord(TKey k)
{
	return SearchNode(pRoot, k);
}

void TTreeTable::InsRecord(TKey k, PTDatValue pVal)
{
	pRoot = InsNode(pRoot, k, pVal);
}

void TTreeTable::DelRecord(TKey k)
{
	pRoot = DeleteNode(pRoot, k);
}

TKey TTreeTable::GetKey() const
{
	if (pCurrent != nullptr)
		return pCurrent->GetKey();
	else
		return "";
}

PTDatValue TTreeTable::GetValuePTR() const
{
	if (pCurrent != nullptr)
		return pCurrent->GetValuePTR();
	else
		return nullptr;
}

int TTreeTable::Reset()
{
	if (!IsEmpty())
	{
		PTTreeNode t = pCurrent = pRoot;
		while (!St.empty())
			St.pop();
		CurrPos = 0;
		while (t != nullptr)
		{
			St.push(t);
			pCurrent = t;
			t = t->GetLeft();
		}
		return 0;
	}
}

int TTreeTable::IsTabEnded() const
{
	return CurrPos >= DataCount;
}

int TTreeTable::GoNext()
{
	if (!IsEmpty())
	{
		PTTreeNode t;
		if (!IsTabEnded() && (pCurrent != nullptr)) {
			t = pCurrent = pCurrent->GetRight();
			St.pop(); // исключение из стека
			while (t != nullptr) {
				// переход к крайней левой вершине
				St.push(t); // добавить в стек
				pCurrent = t;
				t = t->GetLeft();
			}
			if ((pCurrent == nullptr) && !St.empty())
				pCurrent = St.top();
			CurrPos++;
		}
		return 0;
	}
}