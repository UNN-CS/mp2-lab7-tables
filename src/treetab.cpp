#include "treetab.h"

int TreeTable::IsFull() const {
	PTreeNode tmp = new TreeNode();
	int ans = (tmp == NULL);
	delete tmp;
	return ans;
}

PTDatValue TreeTable::FindRecord(TKey k) {
	PTreeNode pNode = pRoot;
	ppRef = &pRoot;
	Efficiency = 0;
	while (pNode != NULL)
	{
		Efficiency++;
		if (pNode->Key == k) break;
		if (pNode->Key < k) ppRef = &pNode->pRight;
		else ppRef = &pNode->pLeft;
		pNode = *ppRef;
	}
	SetRetCode(TabOK);
	return (pNode == NULL) ? NULL : pNode->pValue;
}

void TreeTable::InsRecord(TKey k, PTDatValue pVal) {
	if (IsFull()) SetRetCode(TabFull);
	else if (FindRecord(k) != NULL) SetRetCode(TabRecDbl);
	else {
		SetRetCode(TabOK);
		*ppRef = new TreeNode(k, pVal);
		DataCount++;
	}
}

void TreeTable::DelRecord(TKey k) {
	PTDatValue tmp = FindRecord(k);
	if (tmp == NULL) SetRetCode(TabNoRec);
	else
	{
		SetRetCode(TabOK);
		PTreeNode pNode = *ppRef;
		if (pNode->pRight == NULL)
			*ppRef = pNode->pLeft;
		else if (pNode->pLeft == NULL)
			*ppRef = pNode->pRight;
		else
		{
			PTreeNode pN = pNode->pLeft, *ppR = &pNode->pLeft;
			while (pN->pRight != NULL)
			{
				ppR = &pN->pRight;
				pN = *ppR;
			}
			pNode->pValue = pN->pValue;
			pNode->Key = pN->Key;
			pNode = pN;
			*ppR = pN->pLeft;
		}
		delete pNode;
		DataCount--;
	}
}

TKey TreeTable::GetKey() const {
	return (pCurrent == NULL) ? string("") : pCurrent->Key;
}

PTDatValue TreeTable::GetValuePtr() const {
	return (pCurrent == NULL) ? NULL : pCurrent->pValue;
}

int TreeTable::Reset() {
	PTreeNode pNode = pCurrent = pRoot;
	while (!St.empty()) St.pop();
	CurrPos = 0;
	while (pNode != NULL)
	{
		St.push(pNode);
		pCurrent = pNode;
		pNode = pNode->pLeft;
	}
	SetRetCode(TabOK);
	return IsTabEnded();
}

int TreeTable::IsTabEnded() const {
	return CurrPos >= DataCount;
}

int TreeTable::GoNext() {
	if (!IsTabEnded() && (pCurrent != NULL))
	{
		PTreeNode pNode = pCurrent = pCurrent->pRight;
		St.pop();
		while (pNode != NULL)
		{
			St.push(pNode);
			pCurrent = pNode;
			pNode=pNode->pLeft;
		}
		if (pCurrent == NULL && (!St.empty()))
			pCurrent = St.top();
		CurrPos++;
	}
	return IsTabEnded();
}

ostream& operator<<(ostream& os, TreeTable&tab) {
	cout << "Table printing " << endl;
	tab.PrintTreeTab(os, tab.pRoot);
	return os;
}

void TreeTable::PrintTreeTab(ostream& os, PTreeNode pNode) {
	if (pNode != NULL) {
		PrintTreeTab(os, pNode->pLeft);
		pNode->Print(); os << endl;
		PrintTreeTab(os, pNode->pRight);
	}
}

void TreeTable::Draw() {
	cout << "Table printing " << endl;
	DrawTreeTab(pRoot, 0);
}

void TreeTable::DrawTreeTab(PTreeNode pNode, int level) {
	if (pNode != NULL) {
		DrawTreeTab(pNode->pRight, level + 1);
		for (int i = 0; i < 2 * level; ++i) cout << " ";
		pNode->Print(); cout << endl;
		DrawTreeTab(pNode->pLeft, level + 1);
	}
}

void TreeTable::DeleteTreeTab(PTreeNode pNode)
{
	if (pNode != NULL)
	{
		DeleteTreeTab(pNode->pLeft);
		DeleteTreeTab(pNode->pRight);
		delete pNode;
	}
}

// запись ключей в массив в порядке возрастания с запоминанием номеров ярусов
void TreeTable::PutValues(PTreeNode pNode, int level) {
	if ((pNode != NULL) && (pos < 20)) {
		PutValues(pNode->pLeft, level + 1);
		tk[pos] = pNode->Key;
		tl[pos] = level;
		pos++;
		PutValues(pNode->pRight, level + 1);
	}
}

void TreeTable::Show() {
	int maxl = 0, i, j, k, pn;
	pos = 0;
	PutValues(pRoot, 0);
	for (i = 0; i < pos; i++) if (maxl < tl[i]) maxl = tl[i];
	cout << "Table visualization " << endl;
	for (i = 0; i <= maxl; ++i)
	{
		pn = 0;
		for (j = 0; j < pos; ++j)
		{
			if (tl[j] == i) {
				for (k = 0; k < 2 * (j - pn); ++k) cout << " ";
				cout << tk[j];
				pn = j + 1;
			}
		}
		cout << endl;
	}
}
