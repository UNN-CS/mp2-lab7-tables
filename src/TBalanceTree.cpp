#include "TBalanceTree.h"
#include <math.h>
// #include <conio.h>

using namespace std;

void TBalanceTree::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull()) SetRetCode(TabFull);
    else
        InsBalanceTree(pRoot, k, pVal);
}

int TBalanceTree::InsBalanceTree(PTTreeNode& pNode, TKey k, PTDatValue pVal) {
    int HeightIndex = HeightOK;
    if (pNode == NULL) {
        SetRetCode(TabOK);
        pNode = new TBalanceNode(k, pVal);
        HeightIndex = HeightInc;
        DataCount++;
    }
    else if (k < pNode->GetKey()) {
        if (InsBalanceTree((pNode->pLeft), k, pVal) == HeightInc)
        {
            HeightIndex = LeftTreeBalancing(pNode);
        }
    }
    else if (k > pNode->GetKey())
    {
        if (InsBalanceTree((pNode->pRight), k, pVal) == HeightInc)
            HeightIndex = RightTreeBalancing(pNode);
    }
    else {
        SetRetCode(TabRecDbl);
        HeightIndex = HeightOK;
    }
    return HeightIndex;
}

int TBalanceTree::LeftTreeBalancing(PTTreeNode &pNode) {
    int HeightIndex = HeightOK;
    switch (PTBalanceNode(pNode)->Balance) {
    case BalRight:
        PTBalanceNode(pNode)->SetBalance(BalOK);
        HeightIndex = HeightOK;
        break;
    case BalOK:
        PTBalanceNode(pNode)->SetBalance(BalLeft);
        HeightIndex = HeightInc;
        break;
    case BalLeft:
        //std::cout << "lt" << " ";
        PTBalanceNode p1, p2;
        p1 = PTBalanceNode(pNode->pLeft);
        if (p1->Balance != BalRight)
        {
            pNode->pLeft = p1->pRight;
            p1->pRight = pNode;
            PTBalanceNode(pNode)->SetBalance(BalOK);
            pNode = p1;
        }
        else {
            p2 = PTBalanceNode(p1->pRight);
            p1->pRight = p2->pLeft;
            p2->pLeft = p1;
            pNode->pLeft = p2->pRight;
            p2->pRight = pNode;
            if (p2->GetBalance() == BalLeft) PTBalanceNode(pNode)->SetBalance(BalRight);
            else PTBalanceNode(pNode)->SetBalance(BalOK);
            if (p2->GetBalance() == BalRight) p1->SetBalance(BalLeft);
            else p1->SetBalance(BalOK);
            pNode = p2;
        }
        PTBalanceNode(pNode)->SetBalance(BalOK);
        HeightIndex = HeightOK;
    }
    return HeightIndex;
}

int TBalanceTree::RightTreeBalancing(PTTreeNode & pNode) {
    int HeightIndex = HeightOK;
    switch (PTBalanceNode(pNode)->Balance) {
    case BalLeft:
        PTBalanceNode(pNode)->SetBalance(BalOK);
        HeightIndex = HeightOK;
        break;
    case BalOK:
        PTBalanceNode(pNode)->SetBalance(BalRight);
        HeightIndex = HeightInc;
        break;
    case BalRight:
        PTBalanceNode p1, p2;
        //std::cout << "rt" << " ";
        p1 = PTBalanceNode(pNode->pRight);
        if (p1->Balance != BalLeft) { // RR
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
            if (p2->Balance == BalLeft) p1->SetBalance(BalRight);
            else p1->SetBalance(BalOK);
            if (p2->Balance == BalRight) PTBalanceNode(pNode)->SetBalance(BalLeft);
            else PTBalanceNode(pNode)->SetBalance(BalOK);
            pNode = p2;
        }
        PTBalanceNode(pNode)->SetBalance(BalOK);
        HeightIndex = HeightOK;
    }
    return HeightIndex;
}