#include "balancetree.h"

#include "balancenode.h"

TBalanceTree::TBalanceTree() : TTreeTable() {}

int TBalanceTree::InsBalanceTree(PTBalanceNode &pNode,
        TKey k, PTDatValue pVal) {
    ++efficiency;
    if (pNode == nullptr) {
        pNode = new TBalanceNode(k, pVal);
        ++dataCount;
        return 1;
    }
    if (pNode->GetKey() == k) {
        delete pNode->GetValuePtr();
        pNode->SetValuePtr(pVal);
        return 0;
    }
    if (pNode->GetKey() > k) {
        PTBalanceNode p = (PTBalanceNode)pNode->GetLeft();
        if (InsBalanceTree(p, k, pVal)) {
            pNode->pLeft = p;
            return LeftTreeBalancing(pNode);
        } else {
            pNode->pLeft = p;
        }
    } else {
        PTBalanceNode p = (PTBalanceNode)pNode->GetRight();
        if (InsBalanceTree(p, k, pVal)) {
            pNode->pRight = p;
            return RightTreeBalancing(pNode);
        } else {
            pNode->pRight = p;
        }
    }
    return 0;
}

int TBalanceTree::LeftTreeBalancing(PTBalanceNode &pNode) {
    switch (pNode->GetBalance()) {
      case BalRight:
        pNode->SetBalance(BalOk);
        return 0;
      case BalOk:
        pNode->SetBalance(BalLeft);
        return 1;
      case BalLeft:
        PTBalanceNode p = dynamic_cast<PTBalanceNode>(pNode->GetLeft());
        if (p->GetBalance() == BalLeft) {
            pNode->pLeft = p->pRight;
            p->pRight = pNode;
            pNode->SetBalance(BalOk);
            pNode = p;
            pNode->SetBalance(BalOk);
            return 0;
        } else if (p->GetBalance() == BalRight) {
            PTBalanceNode q = dynamic_cast<PTBalanceNode>(p->GetRight());
            pNode->pLeft = q->GetRight();
            p->pRight = q->GetLeft();
            q->pLeft = p;
            q->pRight = pNode;
            if (q->GetBalance() == BalLeft) {
                pNode->SetBalance(BalRight);
            } else {
                pNode->SetBalance(BalOk);
            }
            if (q->GetBalance() == BalRight) {
                p->SetBalance(BalLeft);
            } else {
                p->SetBalance(BalOk);
            }
            pNode = q;
            pNode->SetBalance(BalOk);
            return 0;
        } else {
            pNode->pLeft = p->pRight;
            p->pRight = pNode;
            pNode->SetBalance(BalLeft);
            pNode = p;
            pNode->SetBalance(BalRight);
            return 1;
        }
    }
    return 0;
}

int TBalanceTree::RightTreeBalancing(PTBalanceNode &pNode) {
    switch (pNode->GetBalance()) {
      case BalLeft:
        pNode->SetBalance(BalOk);
        return 0;
      case BalOk:
        pNode->SetBalance(BalRight);
        return 1;
      case BalRight:
        PTBalanceNode p = dynamic_cast<PTBalanceNode>(pNode->GetRight());
        if (p->GetBalance() == BalRight) {
            pNode->pRight = p->pLeft;
            p->pLeft = pNode;
            pNode->SetBalance(BalOk);
            pNode = p;
            pNode->SetBalance(BalOk);
            return 0;
        } else if (p->GetBalance() == BalLeft) {
            PTBalanceNode q = dynamic_cast<PTBalanceNode>(p->GetLeft());
            pNode->pRight = q->GetLeft();
            p->pLeft = q->GetRight();
            q->pRight = p;
            q->pLeft = pNode;
            if (q->GetBalance() == BalRight) {
                pNode->SetBalance(BalLeft);
            } else {
                pNode->SetBalance(BalOk);
            }
            if (q->GetBalance() == BalLeft) {
                p->SetBalance(BalRight);
            } else {
                p->SetBalance(BalOk);
            }
            pNode = q;
            pNode->SetBalance(BalOk);
            return 0;
        } else {
            pNode->pRight = p->pLeft;
            p->pLeft = pNode;
            pNode->SetBalance(BalRight);
            pNode = p;
            pNode->SetBalance(BalLeft);
            return 1;
        }
    }
    return 0;
}

void TBalanceTree::InsRecord(TKey k, PTDatValue pVal) {
    PTBalanceNode p = (PTBalanceNode)pRoot;
    InsBalanceTree(p, k, pVal);
    pRoot = p;
}

void TBalanceTree::DelRecord(TKey k) {
    if (FindRecord(k) == nullptr) {
        return;
    }
    PTTreeNode p, v, root = pCurrent;
    p = root;
    ++efficiency;
    if (root->pRight == nullptr) {
        root = root->pLeft;
    } else if (root->pLeft == nullptr) {
        root = root->pRight;
    } else {
        ++efficiency;
        v = root->pLeft;
        if (v->pRight != nullptr) {
            while (v->pRight->pRight) {
                ++efficiency;
                v = v->pRight;
            }
            delete root->pValue;
            root->pValue = v->pRight->pValue;
            p = v->pRight;
            v->pRight = v->pRight->pLeft;
        } else {
            delete root->pValue;
            root->pValue = v->pValue;
            p = v;
            root->pLeft = root->pLeft->pLeft;
        }
    }
    delete p;
    Reset();
}
