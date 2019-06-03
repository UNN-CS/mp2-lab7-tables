// TTreeNode.cpp
#include "TTreeNode.h"

TDatValue * TTreeNode::GetCopy() {
    TTreeNode * t = new TTreeNode(Key, pValue, nullptr, nullptr);
    return t;
}