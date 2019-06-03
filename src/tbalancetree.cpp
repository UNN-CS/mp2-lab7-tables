#include "tbalancetree.h"
#define HeightOk 0
#define HeightInc 1

void TBalanceTree::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull()) throw "Error: is full";
    InsBalanceTree((PTBalanceNode&)pRoot, k, pVal);
}

int TBalanceTree::InsBalanceTree(PTBalanceNode& pNode, TKey k, PTDatValue pVal)
{
    ++Efficiency;
    int HeightIndex = HeightOk;
    if (pNode == nullptr)
    {
        pNode = new TBalanceNode(k, pVal);
        HeightIndex = HeightInc;
        DataCount++;
    }
    else if (k < pNode->GetKey())
    {
        if (InsBalanceTree((PTBalanceNode&)pNode->pLeft, k, pVal) == HeightInc)
            HeightIndex = LeftTreeBalancing(pNode);
    }
    else if (k > pNode->GetKey())
    {
        if (InsBalanceTree((PTBalanceNode&)pNode->pRight, k, pVal) == HeightInc)
            HeightIndex = RightTreeBalancing(pNode);
    }
    else
    {
        HeightIndex = HeightOk;
    }
    return HeightIndex;
}

int TBalanceTree::LeftTreeBalancing(PTBalanceNode& pNode) {
    int HeightIndex = HeightOk;
    switch (pNode->GetBalance()) {
    case BalRight:
        pNode->SetBalance(BalOk);
        HeightIndex = HeightOk;
        break;
    case BalOk:
        pNode->SetBalance(BalLeft);
        HeightIndex = HeightInc;
        break;
    case BalLeft:
        PTBalanceNode p1, p2;
        p1 = PTBalanceNode(pNode->pLeft);
        if (p1->GetBalance() == BalLeft) {
            pNode->pLeft = p1->pRight;
            p1->pRight = pNode;
            pNode->SetBalance(BalOk);
            pNode = p1;
        }
        else if (p1->GetBalance() == BalRight) {
            p2 = PTBalanceNode(p1->pRight);
            p1->pRight = p2->pLeft;
            p2->pLeft = p1;
            pNode->pLeft = p2->pRight;
            p2->pRight = pNode;
            if (p2->GetBalance() == BalLeft)
                pNode->SetBalance(BalRight);
            else
                pNode->SetBalance(BalOk);
            if (p2->GetBalance() == BalRight)
                p1->SetBalance(BalLeft);
            else
                p1->SetBalance(BalOk);
            pNode = p2;
        }
        else {
            pNode->pLeft = p1->pRight;
            p1->pRight = pNode;
            pNode->SetBalance(BalLeft);
            pNode = p1;
            pNode->SetBalance(BalRight);
            return HeightInc;
        }
        pNode->SetBalance(BalOk);
        HeightIndex = 0;
    }
    return HeightIndex;
}

int TBalanceTree::RightTreeBalancing(PTBalanceNode & pNode) {
    int HeightIndex = HeightOk;
    switch (pNode->GetBalance()) {
    case BalLeft:
        pNode->SetBalance(BalOk);
        HeightIndex = HeightOk;
        break;
    case BalOk:
        pNode->SetBalance(BalRight);
        HeightIndex = HeightInc;
        break;
    case BalRight:
        PTBalanceNode p1, p2;
        p1 = PTBalanceNode(pNode->pRight);
        if (p1->GetBalance() == BalRight) {
            pNode->pRight = p1->pLeft;
            p1->pLeft = pNode;
            pNode->SetBalance(BalOk);
            pNode = p1;
        }
        else if (p1->GetBalance() == BalLeft) {
            p2 = PTBalanceNode(p1->pLeft);
            pNode->pRight = p2->pLeft;
            p1->pLeft = p2->pRight;
            p2->pRight = p1;
            p2->pLeft = pNode;
            if (p2->GetBalance() == BalRight)
                pNode->SetBalance(BalLeft);
            else
                pNode->SetBalance(BalOk);
            if (p2->GetBalance() == BalLeft)
                pNode->SetBalance(BalRight);
            else
                pNode->SetBalance(BalOk);
            pNode = p2;
        }
        else {
            pNode->pRight = p1->pLeft;
            p1->pLeft = pNode;
            pNode->SetBalance(BalRight);
            pNode = p1;
            pNode->SetBalance(BalLeft);
            return HeightInc;
        }
        pNode->SetBalance(BalOk);
        HeightIndex = 0;
    }
    return HeightIndex;
}
