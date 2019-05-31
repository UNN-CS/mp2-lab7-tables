#include "tbalancetree.hpp"

#define HEIGHTOK 0
#define HEIGHTINC 1

void TBalanceTree::InsRecord(TKey k, PTDatValue pVal)
{
    if (IsFull())
        throw - 1;

    InsBalanceTree(pRoot, k, pVal);
}

int TBalanceTree::InsBalanceTree(PTTreeNode &pNode_, TKey k, PTDatValue pVal)
{
    ++Efficiency;
    PTBalanceNode pNode = (PTBalanceNode)pNode_;

    int hIndex = HEIGHTOK;

    if (!pNode)
    {
        pNode = new TBalanceNode(k, pVal);
        pNode_ = pNode;
        hIndex = HEIGHTINC;
        ++DataCount;
    }
    else if (k < pNode->GetKey())
    {
        if (InsBalanceTree(pNode->pLeft, k, pVal) == HEIGHTINC)
        {
            hIndex = LeftTreeBalancing(pNode);
            pNode_ = pNode;
        }
    }
    else if (k > pNode->GetKey())
    {
        if (InsBalanceTree(pNode->pRight, k, pVal) == HEIGHTINC)
        {
            hIndex = RightTreeBalancing(pNode);
            pNode_ = pNode;
        }
    }
    else
    {
        hIndex = HEIGHTOK;
    }

    pNode_ = pNode;

    return hIndex;
}

int TBalanceTree::LeftTreeBalancing(PTBalanceNode &pNode)
{
    int hIndex = HEIGHTOK;

    switch (pNode->GetBalance())
    {
    case BALRIGHT:
        pNode->SetBalance(BALOK);
        hIndex = HEIGHTOK;
        break;
    case BALOK:
        pNode->SetBalance(BALLEFT);
        hIndex = HEIGHTINC;
        break;
    case BALLEFT:
        PTBalanceNode p1, p2;

        p1 = PTBalanceNode(pNode->pLeft);
        if (p1->GetBalance() == BALLEFT)
        {
            pNode->pLeft = p1->pRight;
            p1->pRight = pNode;
            pNode->SetBalance(BALOK);
            pNode = p1;
        }
        else if (p1->GetBalance() == BALRIGHT)
        {
            p2 = PTBalanceNode(p1->pRight);
            p1->pRight = p2->pLeft;
            p2->pLeft = p1;
            pNode->pLeft = p2->pRight;
            p2->pRight = pNode;
            if (p2->GetBalance() == BALLEFT)
                pNode->SetBalance(BALRIGHT);
            else
                pNode->SetBalance(BALOK);
            if (p2->GetBalance() == BALRIGHT)
                p1->SetBalance(BALLEFT);
            else
                p1->SetBalance(BALOK);
            pNode = p2;
        }
        else
        {
            pNode->pLeft = p1->pRight;
            p1->pRight = pNode;
            pNode->SetBalance(BALLEFT);
            pNode = p1;
            pNode->SetBalance(BALRIGHT);
            return HEIGHTINC;
        }

        pNode->SetBalance(BALOK);
        hIndex = 0;
    }
    return hIndex;
}

int TBalanceTree::RightTreeBalancing(PTBalanceNode &pNode)
{
    int hIndex = HEIGHTOK;
    switch (pNode->GetBalance())
    {
    case BALLEFT:
        pNode->SetBalance(BALOK);
        hIndex = HEIGHTOK;
        break;
    case BALOK:
        pNode->SetBalance(BALRIGHT);
        hIndex = HEIGHTINC;
        break;
    case BALRIGHT:
        PTBalanceNode p1, p2;

        p1 = PTBalanceNode(pNode->pRight);
        if (p1->GetBalance() == BALRIGHT)
        {
            pNode->pRight = p1->pLeft;
            p1->pLeft = pNode;
            pNode->SetBalance(BALOK);
            pNode = p1;
        }
        else if (p1->GetBalance() == BALLEFT)
        {
            p2 = PTBalanceNode(p1->pLeft);
            pNode->pRight = p2->pLeft;
            p1->pLeft = p2->pRight;
            p2->pRight = p1;
            p2->pLeft = pNode;
            if (p2->GetBalance() == BALRIGHT)
                pNode->SetBalance(BALLEFT);
            else
                pNode->SetBalance(BALOK);
            if (p2->GetBalance() == BALLEFT)
                pNode->SetBalance(BALRIGHT);
            else
                pNode->SetBalance(BALOK);
            pNode = p2;
        }
        else
        {
            pNode->pRight = p1->pLeft;
            p1->pLeft = pNode;
            pNode->SetBalance(BALRIGHT);
            pNode = p1;
            pNode->SetBalance(BALLEFT);
            return HEIGHTINC;
        }

        pNode->SetBalance(BALOK);
        hIndex = 0;
    }
    return hIndex;
}