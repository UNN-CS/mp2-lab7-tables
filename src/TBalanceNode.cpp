#include "TBalanceNode.h"

TDatValue *TBalanceNode::GetCopy() {
	return new TBalanceNode(Key, pValue, nullptr, nullptr, BalOk);
}

int TBalanceNode::GetBalance() const {
	return Balance;
}

void TBalanceNode::SetBalance(int bal) {
	Balance = bal;
}