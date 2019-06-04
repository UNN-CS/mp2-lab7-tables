#include "TTreeNode.h"

PTTreeNode TTreeNode::GetLeft() const {
	return pLeft;
}

PTTreeNode TTreeNode::GetRight() const {
	return pRight;
}

TDatValue* TTreeNode::GetCopy() {
	TTreeNode* t = new TTreeNode(Key, pValue, nullptr, nullptr);
	return t;
}