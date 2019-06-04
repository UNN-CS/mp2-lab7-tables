#include "TBalanceNode.h"

TDatValue * TBalanceNode::GetCopy()
{
	return new TBalanceNode(Key, pValue, pLeft, pRight, Balance);
}

int TBalanceNode::GetBalance() const
{
	return Balance;
}

void TBalanceNode::SetBalance(int bal)
{
	Balance = bal;
}