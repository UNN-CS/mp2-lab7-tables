#include "ttreenode.h"

PTTreeNode TTreeNode::GetLeft() const {
    return pLeft;
}

PTTreeNode TTreeNode::GetRight() const {
    return pRight;
}

TDatValue* TTreeNode::GetCopy() {
    TTreeNode* tmp = new TTreeNode(Key, pValue, nullptr, nullptr);
    return tmp;
}
