#include "TBalanceNode.h"

TDatValue * TBalanceNode::GetCopy() {
    TBalanceNode* tmp = new TBalanceNode(Key, pValue, NULL, NULL, BalOK);
    return tmp;
}