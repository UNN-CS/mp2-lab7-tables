#include "tbalancenode.h"

TDatValue* TBalanceNode::GetCopy() {
    TBalanceNode* tmp = new TBalanceNode(Key, pValue, nullptr, nullptr, BalOK);
    return tmp;
}
