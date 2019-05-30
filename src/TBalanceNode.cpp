#include "TBalanceNode.h"

TDatValue *TBalanceNode::GetCopy() {
	return new TBalanceNode(key, pValue, nullptr, nullptr, 0);
}

int TBalanceNode::GetBalance() const {
	return Balance;
}

void TBalanceNode::SetBalance(int bal) {
	Balance = bal;
}