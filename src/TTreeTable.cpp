#include <iostream>
#include "TTreeTable.h"


int TTreeTable::IsFull() const {
	return 0;
}

PTDatValue TTreeTable::FindRecord(TKey k) {
	PTTreeNode pNode = pRoot;
	ppRef = &pRoot;
	Efficiency = 0;
	while (pNode) {
		Efficiency++;
		if (pNode->key == k)
			break;
		if (pNode->key < k)
			ppRef = &pNode->pRight;
		else
			ppRef = &pNode->pLeft;
		pNode = *ppRef;
	}
	return pNode ? pNode->pValue : nullptr;
}

void TTreeTable::InsRecord(TKey k, PTDatValue pVal) {
	if (IsFull())
		throw - 1;
	if (FindRecord(k))
		return;
	*ppRef = new TTreeNode(k, pVal);
	DataCount++;
}

void TTreeTable::DelRecord(TKey k) {
	Efficiency = 0;
	PTDatValue tmp = FindRecord(k);
	if (!tmp)
		return;
	PTTreeNode pNode = *ppRef;
	if (!pNode->pRight)
		*ppRef = pNode->pLeft;
	else if (!pNode->pLeft)
		*ppRef = pNode->pRight;
	else {
		PTTreeNode pN = pNode->pLeft, *ppR = &pNode->pLeft;
		while (pN->pRight) {
			++Efficiency;
			ppR = &pN->pRight;
			pN = *ppR;
		}
		pNode->pValue = pN->pValue;
		pNode->key = pN->key;
		pNode = pN;
		*ppR = pN->pLeft;
	}
	--DataCount;
	delete pNode;
}

TKey TTreeTable::GetKey() const {
	return pCurrent ? pCurrent->key : "";
}

PTDatValue TTreeTable::GetValuePTR() const {
	return pCurrent ? pCurrent->pValue : nullptr;
}

int TTreeTable::Reset() {
	PTTreeNode pNode = pCurrent = pRoot;
	while (St.size())
		St.pop();
	CurrPos = 0;
	while (pNode) {
		St.push(pNode);
		pCurrent = pNode;
		pNode = pNode->pLeft;
	}
	return IsTabEnded();
}

int TTreeTable::IsTabEnded() const {
	return CurrPos >= DataCount;
}

int TTreeTable::GoNext() {
	PTTreeNode pNode = pRoot;
	if (!IsTabEnded() && pCurrent) {
		pNode = pCurrent = pCurrent->pRight;
		St.pop();
		while (pNode) {
			St.push(pNode);
			pCurrent = pNode;
			pNode = pNode->pLeft;
		}
		if (!pCurrent && St.size())
			pCurrent = St.top();
		++CurrPos;
	}
	return IsTabEnded();
}

void TTreeTable::DeleteTreeTab(PTTreeNode pNode) {
	if (pNode) {
		DeleteTreeTab(pNode->pLeft);
		DeleteTreeTab(pNode->pRight);
		delete pNode;
	}
}
