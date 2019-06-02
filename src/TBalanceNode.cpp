// TBalanceNode.cpp
#include "TBalanceNode.h"

TDatValue * TBalanceNode::GetCopy() {
    TBalanceNode * t = new TBalanceNode(Key, pValue, nullptr, nullptr, BalOk);
    return t;
}