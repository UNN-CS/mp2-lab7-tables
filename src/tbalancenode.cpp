#include "tbalancenode.h"

TDatValue* TBalanceNode::GetCopy() {
    TDatValue* tmp = new TBalanceNode(Key, pValue, nullptr, nullptr, 0);
    return tmp;
}

int TBalanceNode::GetBalance() const {
    return Balance;
}

void TBalanceNode::SetBalance(int bal) {
    Balance = bal;
}
