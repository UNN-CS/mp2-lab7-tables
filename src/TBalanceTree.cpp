#include "TBalanceTree.h"
#include <stack>
#include <queue>

int TBalanceTree::InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal)
{
    int HeightIndex = HeightOK;
    if (pNode == nullptr)
    {
        SetRetCode(TabOK);
        pNode = new TBalanceNode(k, pVal);
        HeightIndex = HeightInc;
        DataCount++;
    }
    else if (k < pNode->GetKey())
    {
        if (InsBalanceTree((PTBalanceNode &)(pNode->pLeft), k, pVal) == HeightInc)
            HeightIndex = LeftTreeBalancing(pNode);
    }
    else if (k > pNode->GetKey())
    {
        if (InsBalanceTree((PTBalanceNode &)(pNode->pRight), k, pVal) == HeightInc)
            HeightIndex = RightTreeBalancing(pNode);
    }
    else
    {
        SetRetCode(TabRecDbl);
        HeightIndex = HeightOK;
    }
    return HeightIndex;
}

int TBalanceTree::LeftTreeBalancing(PTBalanceNode &pNode)
{
    switch (pNode->GetBalance())
    {
    case BalRight:
        pNode->SetBalance(BalOk);
        return HeightOK;
    case BalOk:
        pNode->SetBalance(BalLeft);
        return HeightInc;
    case BalLeft:
        PTBalanceNode p1 = PTBalanceNode(pNode->GetLeft());
        if (p1->GetBalance() == BalLeft)
        {
            pNode->pLeft = p1->pRight;
            p1->pRight = pNode;
            pNode->SetBalance(BalOk);
            pNode = p1;
            pNode->SetBalance(BalOk);
            return HeightOK;
        }
        else if (p1->GetBalance() == BalRight)
        {
            PTBalanceNode p2 = PTBalanceNode(p1->GetRight());
            pNode->pLeft = p2->GetRight();
            p1->pRight = p2->GetLeft();
            p2->pLeft = p1;
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
            pNode->SetBalance(BalOk);
            return HeightOK;
        }
        else
        {
            pNode->pLeft = p1->pRight;
            p1->pRight = pNode;
            pNode->SetBalance(BalLeft);
            pNode = p1;
            pNode->SetBalance(BalRight);
            return HeightInc;
        }
    }
    return HeightOK;
}

int TBalanceTree::RightTreeBalancing(PTBalanceNode &pNode)
{
    int HeightIndex = HeightOK;
    switch (pNode->GetBalance())
    {
    case BalLeft:
        pNode->SetBalance(BalOk);
        HeightIndex = HeightOK;
        break;
    case BalOk:
        pNode->SetBalance(BalRight);
        HeightIndex = HeightInc;
        break;
    case BalRight:
        PTBalanceNode p1, p2;
        p1 = PTBalanceNode(pNode->GetRight());
        if (p1->GetBalance() == BalRight)
        {
            pNode->pRight = p1->pLeft;
            p1->pLeft = pNode;
            pNode->SetBalance(BalOk);
            pNode = p1;
        }
        else
        {
            p2 = PTBalanceNode(p1->GetLeft());
            p1->pLeft = p2->pRight;
            p2->pRight = p1;
            pNode->pRight = p2->pLeft;
            p2->pLeft = pNode;

            if (p2->GetBalance() == BalRight)
            {
                pNode->SetBalance(BalLeft);
            }
            else
            {
                pNode->SetBalance(BalOk);
            }
            if (p2->GetBalance() == BalLeft)
            {
                p1->SetBalance(BalRight);
            }
            else
            {
                p1->SetBalance(BalOk);
            }
            pNode = p2;
        }
        pNode->SetBalance(BalOk);
        HeightIndex = HeightOK;
    }
    return HeightIndex;
}

void TBalanceTree::InsRecord(TKey k, PTDatValue pVal)
{
    if (IsFull())
        SetRetCode(TabFull);
    else
    {
        InsBalanceTree((PTBalanceNode &)pRoot, k, pVal);
    }
}

void TBalanceTree::DelRecord(TKey k)
{
    struct balance
    {
        PTBalanceNode *p;
        bool d;
    };

    bool flag = true;
    std::stack<balance> s;
    PTBalanceNode *p = (PTBalanceNode *)&pRoot;
    while ((*p) != nullptr)
    {
        if ((*p)->GetKey() > k)
        {
            s.push({ p, 0 });
            p = (PTBalanceNode *)&(*p)->pLeft;
        }
        else if ((*p)->GetKey() < k)
        {
            s.push({ p, 1 });
            p = (PTBalanceNode *)&(*p)->pRight;
        }
        else
        {
            --DataCount;
            flag = false;
            PTBalanceNode l = (PTBalanceNode)(*p)->pLeft;
            PTBalanceNode r = (PTBalanceNode)(*p)->pRight;
            int bal = (*p)->GetBalance();
            delete (*p);
            if (l == nullptr)
                *p = r;
            else if (r == nullptr)
                *p = l;
            else if (r->pLeft == nullptr)
            {
                r->pLeft = l;
                *p = r;
                r->SetBalance(bal);
                s.push({ p, 1 });
            }
            else
            {
                PTBalanceNode *q = (PTBalanceNode *)&r->pLeft;
                std::queue<PTBalanceNode *> qu;
                while ((*q)->pLeft != nullptr)
                {
                    qu.push(q);
                    q = (PTBalanceNode *)&(*q)->pLeft;
                }
                *p = *q;
                *q = (PTBalanceNode)(*q)->pRight;
                (*p)->pRight = r;
                (*p)->pLeft = l;
                (*p)->SetBalance(bal);
                s.push({ p, 1 });
                s.push({ (PTBalanceNode *)&(*p)->pRight, 0 });
                while (qu.size())
                {
                    s.push({ qu.front(), 0 });
                    qu.pop();
                }
            }
            break;
        }
    }
    Efficiency += s.size() + 1;
    while (s.size() && (!flag))
    {
        balance b = s.top();
        s.pop();
        if (b.d)
            flag = LeftTreeBalancing(*b.p);
        else
            flag = RightTreeBalancing(*b.p);
    }
}