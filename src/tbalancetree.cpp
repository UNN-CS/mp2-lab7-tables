#include "tbalancetree.h"
#include "tbalancenode.h"

void TBalanceTree::InsRecord(TKey k, PTDatValue pVal) {
    if(IsFull())
        throw TabFull;
    InsBalanceTree((PTBalanceNode)pRoot, k, pVal);
}

int TBalanceTree::InsBalanceTree(PTBalanceNode pNode, TKey k, PTDatValue pVal) { //???
    int HeighIndex = HeightOK;
    if(pNode == nullptr) {
        pNode = new TBalanceNode(k, pVal);
        HeighIndex = HeightInc;
        DataCount++;
    }
    else if(k < pNode->GetKey()) {
        if(InsBalanceTree(PTBalanceNode(pNode->pLeft), k, pVal) == HeightInc)
        HeighIndex = LeftTreeBalancing(pNode);
    }
    else if(k > pNode->GetKey()) {
        if(InsBalanceTree(PTBalanceNode(pNode->pRight), k, pVal) == HeightInc)
        HeighIndex = RightTreeBalancing(pNode);
    }
    else {
        HeighIndex = HeightOK;
        throw TabRecDbl;
    }
    return HeighIndex;
}

int TBalanceTree::LeftTreeBalancing(PTBalanceNode& pNode) {
    int HeighIndex = HeightOK;
    switch(pNode->GetBalance()) {
        case BalRight:
            pNode->SetBalance(BalOK);
            HeighIndex = HeightOK;
            break;
        case BalOK:
            pNode->SetBalance(BalLeft);
            HeighIndex = HeightInc;
            break;
        case BalLeft:
            PTBalanceNode p1, p2;
            p1 = PTBalanceNode(pNode->pLeft);
            if(p1->GetBalance() == BalLeft) {
                pNode->pLeft = p1->pRight;
                p1->pRight = pNode;
                pNode->SetBalance(BalOK);
                pNode = p1;
            }
            else {
                p2 = PTBalanceNode(p1->pRight);
                p1->pRight = p2->pLeft;
                p2->pLeft = p1;
                pNode->pLeft = p2->pRight;
                p2->pRight = pNode;
                if(p2->GetBalance() == BalLeft)
                    pNode->SetBalance(BalRight);
                else
                    pNode->SetBalance(BalOK);
                if(p2->GetBalance() == BalRight)
                    p1->SetBalance(BalLeft);
                else
                    p1->SetBalance(BalOK);
                pNode = p2;
            }
            pNode->SetBalance(BalOK);
            HeighIndex = HeightOK;
    }
    return HeighIndex;
}

int TBalanceTree::RightTreeBalancing(PTBalanceNode& pNode) {
    int HeighIndex = HeightOK;
    switch(pNode->GetBalance()) {
    case BalLeft:
        pNode->SetBalance(BalOK);
        HeighIndex = HeightOK;
        break;
    case BalOK:
        pNode->SetBalance(BalLeft);
        HeighIndex = HeightInc;
        break;
    case BalRight:
        PTBalanceNode p1, p2;
        p1 = PTBalanceNode(pNode->pRight);
        if(p1->GetBalance() != BalLeft) {
            pNode->pRight = p1->pLeft;
            p1->pLeft = pNode;
            PTBalanceNode(pNode)->SetBalance(BalOK);
            pNode = p1;
        }
        else {
            p2 = PTBalanceNode(p1->pLeft);
            p1->pLeft = p2->pRight;
            p2->pRight = p1;
            pNode->pRight = p2->pLeft;
            p2->pLeft = pNode;
            if(p2->Balance == BalLeft)
                p1->SetBalance(BalRight);
            else
                p1->SetBalance(BalOK);
            if(p2->Balance == BalRight)
                PTBalanceNode(pNode)->SetBalance(BalLeft);
            else
                PTBalanceNode(pNode)->SetBalance(BalOK);
            pNode = p2;
        }
        PTBalanceNode(pNode)->SetBalance(BalOK);
        HeighIndex = HeightOK;
        break;
    }
    return HeighIndex;
}

//delete???
