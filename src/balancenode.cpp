#include "balancenode.h"

TBalanceNode::TBalanceNode(TKey k, PTDatValue pVal,
        PTTreeNode pL, PTTreeNode pR, int bal)
        : TTreeNode(k, pVal, pL, pR) {
    balance = bal;
}

PTDatValue TBalanceNode::GetCopy() const {
    PTTreeNode pL = nullptr;
    PTTreeNode pR = nullptr;

    if (pLeft != nullptr) {
        pL = (PTBalanceNode)pLeft->GetCopy();
    }
    if (pRight != nullptr) {
        pR = (PTBalanceNode)pRight->GetCopy();
    }

    if (pValue == nullptr) {
        return new TBalanceNode(key, nullptr, pL, pR, balance);
    } else {
        return new TBalanceNode(key, pValue->GetCopy(),
                pL, pR, balance);
    }
}

int TBalanceNode::GetBalance() const {
    return balance;
}

void TBalanceNode::SetBalance(int bal) {
    balance = bal;
}
