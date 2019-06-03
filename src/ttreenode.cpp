#include "ttreenode.h"


TDatValue *TTreeNode::GetCopy() {
    return new TTreeNode(key, pValue, nullptr, nullptr);
}       /*================================================*/
