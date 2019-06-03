#include "tbalancenode.h"

TDatValue* TBalanceNode::GetCopy() {
    return new TBalanceNode(key, pValue, pLeft, pRight, balance);
}       /*================================================*/

int TBalanceNode::GetBalance() const {
    return balance;
}       /*================================================*/

void TBalanceNode::SetBalance(int bal) {
    balance = bal;
}
