#include "TBalanceNode.h"

TBalanceNode::TBalanceNode(TKey k, PTDatValue pVal, PTTreeNode pL, PTTreeNode pR, int bal) : TTreeNode(k, pVal, pL, pR),
                           Balance(bal) {}

int TBalanceNode::GetBalance() const
{
	return Balance;
}

void TBalanceNode::SetBalance(int bal)
{
	Balance = bal;
}

PTDatValue TBalanceNode::GetCopy()
{
	PTBalanceNode t = new TBalanceNode(Key, pValue, pLeft, pRight);
	return (PTDatValue)t;
}