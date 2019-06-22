#include "TTreeNode.h"

TDatValue * TTreeNode::GetCopy() {
    TTreeNode * tmp = new TTreeNode(Key, pValue, NULL, NULL);
    return tmp;
}