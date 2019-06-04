#include "ttreenode.h"

TDatValue *TTreeNode::GetCopy() {
    return new TTreeNode(Key, pValue, nullptr, nullptr);
}
