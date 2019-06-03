#include "ttreenode.h"

TDatValue* TTreeNode::GetCopy() {
    TDatValue* tmp = new TTreeNode(Key, pValue, nullptr, nullptr);
    return tmp;
}

PTTreeNode TTreeNode::GetLeft() const {
    return pLeft;
}

PTTreeNode TTreeNode::GetRight() const {
    return pRight;
}
