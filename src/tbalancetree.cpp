#include <stack>
#include <queue>

#include "tbalancetree.hpp"

int TBalanceTree::InsBalanceTree(PTBalanceNode &pNode, TKey& k, PTDatValue pVal)
{
    ++Efficiency;

    if (pNode == nullptr)
    {
        pNode = new TBalanceNode(k, pVal);
        ++DataCount;

        return 1;
    }

    if (pNode->GetKey() == k)
    {
        pNode->SetValuePtr(pVal);
        return 0;
    }

    if (pNode->GetKey() > k)
    {
        PTBalanceNode p = (PTBalanceNode)pNode->GetLeft();

        if (InsBalanceTree(p, k, pVal))
        {
            pNode->pLeft = p;
            return LeftTreeBalancing(pNode);
        }
        else
            pNode->pLeft = p;
    }
    else
    {
        PTBalanceNode p = (PTBalanceNode)pNode->GetRight();

        if (InsBalanceTree(p, k, pVal))
        {
            pNode->pRight = p;
            return RightTreeBalancing(pNode);
        }
        else
            pNode->pRight = p;
    }

    return 0;
}

int TBalanceTree::LeftTreeBalancing(PTBalanceNode &pNode)
{
    switch (pNode->GetBalance())
    {
    case BALRIGHT:
        pNode->SetBalance(BALOK);
        return 0;

    case BALOK:
        pNode->SetBalance(BALLEFT);
        return 1;

    case BALLEFT:
        PTBalanceNode p = dynamic_cast<PTBalanceNode>(pNode->GetLeft());

        if (p->GetBalance() == BALLEFT)
        {
            pNode->pLeft = p->pRight;

            p->pRight = pNode;
            pNode->SetBalance(BALOK);

            pNode = p;
            pNode->SetBalance(BALOK);

            return 0;
        }
        else if (p->GetBalance() == BALRIGHT)
        {
            PTBalanceNode q = dynamic_cast<PTBalanceNode>(p->GetRight());

            pNode->pLeft = q->GetRight();
            p->pRight = q->GetLeft();

            q->pLeft = p;
            q->pRight = pNode;

            if (q->GetBalance() == BALLEFT)
                pNode->SetBalance(BALRIGHT);
            else
                pNode->SetBalance(BALOK);

            if (q->GetBalance() == BALRIGHT)
                p->SetBalance(BALLEFT);
            else
                p->SetBalance(BALOK);

            pNode = q;
            pNode->SetBalance(BALOK);

            return 0;
        }
        else
        {
            pNode->pLeft = p->pRight;
            p->pRight = pNode;
            pNode->SetBalance(BALLEFT);
            pNode = p;
            pNode->SetBalance(BALRIGHT);
            return 1;
        }
    }
    return 0;
}

int TBalanceTree::RightTreeBalancing(PTBalanceNode &pNode)
{
    switch (pNode->GetBalance())
    {
    case BALLEFT:
        pNode->SetBalance(BALOK);
        return 0;
    case BALOK:
        pNode->SetBalance(BALRIGHT);
        return 1;
    case BALRIGHT:
        PTBalanceNode p = dynamic_cast<PTBalanceNode>(pNode->GetRight());

        if (p->GetBalance() == BALRIGHT)
        {
            pNode->pRight = p->pLeft;

            p->pLeft = pNode;
            pNode->SetBalance(BALOK);

            pNode = p;
            pNode->SetBalance(BALOK);

            return 0;
        }
        else if (p->GetBalance() == BALLEFT)
        {
            PTBalanceNode q = dynamic_cast<PTBalanceNode>(p->GetLeft());

            pNode->pRight = q->GetLeft();
            p->pLeft = q->GetRight();

            q->pRight = p;
            q->pLeft = pNode;

            if (q->GetBalance() == BALRIGHT)
                pNode->SetBalance(BALLEFT);
            else
                pNode->SetBalance(BALOK);

            if (q->GetBalance() == BALLEFT)
                p->SetBalance(BALRIGHT);
            else
                p->SetBalance(BALOK);

            pNode = q;
            pNode->SetBalance(BALOK);

            return 0;
        }
        else
        {
            pNode->pRight = p->pLeft;

            p->pLeft = pNode;
            pNode->SetBalance(BALRIGHT);

            pNode = p;
            pNode->SetBalance(BALLEFT);

            return 1;
        }
    }
    return 0;
}

void TBalanceTree::InsRecord (TKey k, PTDatValue pVal )
{
    PTBalanceNode p = (PTBalanceNode)pRoot;
    InsBalanceTree(p, k, pVal);

    pRoot = p;
}

void TBalanceTree::DelRecord (TKey k)
{
    struct balance
    {
        PTBalanceNode* p;
        bool d;
    };

    bool flag = true;
    std::stack<balance> s;
    PTBalanceNode* p = (PTBalanceNode*)&pRoot;

    while ((*p) != nullptr)
    {
        if ((*p)->GetKey() > k)
        {
            s.push({p, 0});
            p = (PTBalanceNode*)&(*p)->pLeft;
        }
        else if ((*p)->GetKey() < k)
        {
            s.push({p, 1});
            p = (PTBalanceNode*)&(*p)->pRight;
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
                s.push({p, 1});
            }
            else
            {
                PTBalanceNode* q = (PTBalanceNode*)&r->pLeft;
                std::queue<PTBalanceNode*> qu;

                while ((*q)->pLeft != nullptr)
                {
                    qu.push(q);
                    q = (PTBalanceNode*)&(*q)->pLeft;
                }

                *p = *q;
                *q = (PTBalanceNode)(*q)->pRight;

                (*p)->pRight = r;
                (*p)->pLeft = l;
                (*p)->SetBalance(bal);

                s.push({p, 1});
                s.push({(PTBalanceNode*)&(*p)->pRight, 0});

                while (qu.size())
                {
                    s.push({qu.front(), 0});
                    qu.pop();
                }
            }
            break;
        }
    }

    Efficiency += s.size() + 1;

    while (s.size()&&(!flag))
    {
        balance b = s.top();
        s.pop();
        
        if (b.d)
            flag = LeftTreeBalancing(*b.p);
        else
            flag = RightTreeBalancing(*b.p);
    }
}
