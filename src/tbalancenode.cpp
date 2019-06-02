#include "tbalancenode.h"

TDatValue* TBalanceNode::GetCopy() {
    TBalanceNode* tmp = new TBalanceNode(Key, pValue, nullptr, nullptr, BalOK);
    return tmp;
}

int TBalanceNode::GetBalance() const {
    return Balance;
}

void TBalanceNode::SetBalance(int bal) {
    Balance = bal;
}
