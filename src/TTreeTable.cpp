#include "TTreeTable.h"

void TTreeTable::DeleteTreeTab(PTTreeNode pNode) 
{
	if (pNode != nullptr) 
	{
		DeleteTreeTab(pNode->pLeft);
		DeleteTreeTab(pNode->pRight);
		delete pNode;
	}
}

int TTreeTable::IsFull() const 
{
	return 0;
}

PTDatValue TTreeTable::FindRecord(TKey k) 
{
	PTTreeNode pNode = pRoot;
	ppRef = &pRoot;
	Efficiency = 0;
	while (pNode != nullptr) {
		Efficiency++;
		if (pNode->Key == k)
			return pNode;
		if (pNode->Key < k) {
			ppRef = &pNode->pRight;
			pNode = pNode->GetRight();
		}
		else {
			ppRef = &pNode->pLeft;
			pNode = pNode->GetLeft();
		}
	}
	return nullptr;
}

void TTreeTable::InsRecord(TKey k, PTDatValue pVal) 
{
	if (IsFull())
		throw ("Table is full");
	if (FindRecord(k) != nullptr)
		throw ("Record already exists");
	*ppRef = new TTreeNode(k, pVal);
	if (DataCount == 0)
		pRoot = pCurrent = *ppRef;
	DataCount++;
}

void TTreeTable::DelRecord(TKey k) 
{
	if (IsEmpty())
		throw ("Table is empty");
	if (FindRecord(k) == nullptr)
		throw ("No record");
	PTTreeNode pNode = *ppRef;
	if (pNode->pRight == nullptr)
		*ppRef = pNode->pLeft;
	else if (pNode->pLeft == nullptr)
		*ppRef = pNode->pRight;
	else
	{
		PTTreeNode pN = pNode->pLeft, *ppR = &pNode->pLeft;
		while (pN->pRight != nullptr) 
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
}

TKey TTreeTable::GetKey() const 
{
	return (pCurrent == nullptr) ? std::string("") : pCurrent->Key;
}

PTDatValue TTreeTable::GetValuePTR() const 
{
	return (pCurrent == nullptr) ? nullptr : pCurrent->pValue;
}

int TTreeTable::Reset() 
{
	PTTreeNode pNode = pCurrent = pRoot;
	while (!St.empty())
		St.pop();
	CurrPos = 0;
	while (pNode != nullptr) {
		St.push(pNode);
		pCurrent = pNode;
		pNode = pNode->GetLeft();
	}
	return IsTabEnded();
}

int TTreeTable::IsTabEnded() const 
{
	return (CurrPos >= DataCount);
}

int TTreeTable::GoNext() {
	if (!IsTabEnded() && (pCurrent != nullptr)) 
	{
		PTTreeNode pNode = pCurrent = pCurrent->GetRight();
		St.pop();
		while (pNode != nullptr) 
		{
			St.push(pNode);
			pCurrent = pNode;
			pNode = pNode->GetLeft();
		}
		if (pCurrent == nullptr && !St.empty())
			pCurrent = St.top();
		CurrPos++;
	}
	return 0;
}

