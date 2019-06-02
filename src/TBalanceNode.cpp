#include "TBalanceNode.h"

TDatValue * TBalanceNode::GetCopy()
{
    TBalanceNode* tmp = new TBalanceNode(Key, pValue, nullptr, nullptr, BalOk);
    return tmp;
}

int TBalanceNode::GetBalance(void) const
{
    return Balance;
}

void TBalanceNode::SetBalance(int bal)
{
    Balance = bal;
}