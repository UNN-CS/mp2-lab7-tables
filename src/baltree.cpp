#include "baltree.h"

int TBalanceTree::LeftTreeBalancing(PTBalanceNode &pNode)
{
    int HeighIndex = HeighOK;

    switch (pNode->GetBalance())
    {
    case BalRight:
        pNode->SetBalance(BalOK);
        HeighIndex = HeighOK;
        break;
    case BalOK:
        pNode->SetBalance(BalLeft);
        HeighIndex = HeighInc;
        break;
    case BalLeft:
        PTBalanceNode p1, p2;
        p1 = PTBalanceNode(pNode->pLeft);

        if (p1->GetBalance() == BalLeft)
        {
            pNode->pLeft = p1->pRight;
            p1->pRight = pNode;
            pNode->SetBalance(BalOK);
            pNode = p1;
        }
        else
        {
            p2 = PTBalanceNode(p1->pRight);
            p1->pRight = p2->pLeft;
            p2->pLeft = p1;
            pNode->pLeft = p2->pRight;
            p2->pRight = pNode;
            if (p2->GetBalance() == BalLeft)
                pNode->SetBalance(BalRight);
            else
                pNode->SetBalance(BalOK);
            if (p2->GetBalance() == BalRight)
                p1->SetBalance(BalLeft);
            else
                p1->SetBalance(BalOK);
            pNode = p2;
        }
        pNode->SetBalance(BalOK);
        HeighIndex = HeighOK;
    }
    return HeighIndex;
}

int TBalanceTree::RightTreeBalancing(PTBalanceNode &pNode) {
    int hIndex = HeighOK;
    switch (pNode->GetBalance()) {
    case BalLeft:
        pNode->SetBalance(BalOK);
        hIndex = HeighOK;
        break;
    case BalOK:
        pNode->SetBalance(BalRight);
        hIndex = HeighInc;
        break;
    case BalRight:
        PTBalanceNode p1, p2;
        p1 = PTBalanceNode(pNode->pRight);
        if (p1->GetBalance() == BalRight) {
            pNode->pRight = p1->pLeft;
            p1->pLeft = pNode;
            pNode->SetBalance(BalOK);
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
                pNode->SetBalance(BalOK);
            if (p2->GetBalance() == BalLeft)
                pNode->SetBalance(BalRight);
            else
                pNode->SetBalance(BalOK);
            pNode = p2;
        }
        else {
            pNode->pRight = p1->pLeft;
            p1->pLeft = pNode;
            pNode->SetBalance(BalRight);
            pNode = p1;
            pNode->SetBalance(BalLeft);
            return HeighInc;
        }
        pNode->SetBalance(BalOK);
        hIndex = 0;
    }
    return hIndex;
}

int TBalanceTree::InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal)
{
    Efficiency++;

    int HeighIndex = HeighOK;

    if (pNode == nullptr)
    {
        SetRetCode(TabOK);
        pNode = new TBalanceNode(k, pVal);
        HeighIndex = HeighInc;
        DataCount++;
    }
    else if (k < pNode->GetKey())
    {
        if (InsBalanceTree((PTBalanceNode&)pNode->pLeft, k, pVal) == HeighInc)
            HeighIndex = LeftTreeBalancing(pNode);
    }
    else if (k > pNode->GetKey())
    {
        if (InsBalanceTree((PTBalanceNode&)pNode->pRight, k, pVal) == HeighInc)
            HeighIndex = RightTreeBalancing(pNode);
    }
    else
    {
        SetRetCode(TabRecDbl);
        HeighIndex = HeighOK;
    }
    return HeighIndex;
}

void TBalanceTree::InsRecord(TKey k, PTDatValue pVal)
{
    if (IsFull())
        SetRetCode(TabFull);
    else
        InsBalanceTree((PTBalanceNode&)pRoot, k, pVal);
}

