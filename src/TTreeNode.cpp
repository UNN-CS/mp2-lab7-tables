#include "TTreeNode.h"

TTreeNode::TTreeNode(TKey k, PTDatValue pVal, PTTreeNode pL, PTTreeNode pR)  : TTabRecord(k, pVal), pLeft(pL), pRight(pR) {}

PTTreeNode TTreeNode::GetLeft() const
{
	return pLeft;
}

PTTreeNode TTreeNode::GetRight() const
{
	return pRight;
}

TDatValue* TTreeNode::GetCopy()
{
	return new TTreeNode(Key, pValue, pLeft, pRight);
}