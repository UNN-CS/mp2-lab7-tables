#include "tbalancenode.hpp"

TDatValue *TBalanceNode::GetCopy()
{
    return new TBalanceNode(Key, pValue, nullptr, nullptr, 0);
}

int TBalanceNode::GetBalance() const
{
    return Balance;
}

void TBalanceNode::SetBalance(int bal)
{
    Balance = bal;
}
