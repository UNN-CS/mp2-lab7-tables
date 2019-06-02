// TBalanceTree.cpp
#include <math.h>
#include <conio.h>
#include <queue>
#include "TBalanceTree.h"

void TBalanceTree::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull())
        throw "insert in full table";
    PTBalanceNode p = (PTBalanceNode)pRoot;
    InsBalanceTree(p, k, pVal);
    pRoot = p;
}

int TBalanceTree::InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal) {
    int HeighIndex = HeightOK;
    Efficiency++;
    if (pNode == nullptr) {
        pNode = new TBalanceNode(k, pVal);
        HeighIndex = HeighInc;
        ++DataCount;
    }
    if (pNode->GetKey() == k) {
        pNode->SetValuePtr(pVal);
        HeighIndex = HeightOK;
    }
    else if (pNode->GetKey() < k) {
        PTBalanceNode p = (PTBalanceNode)pNode->GetRight();
        if (InsBalanceTree(p, k, pVal))
        {
            pNode->pRight = p;
            HeighIndex = RightTreeBalancing(pNode);
        }
        else
            pNode->pRight = p;
    }
    else {
        PTBalanceNode p = (PTBalanceNode)pNode->GetLeft();
        if (InsBalanceTree(p, k, pVal))
        {
            pNode->pLeft = p;
            HeighIndex = LeftTreeBalancing(pNode);
        }
        else
            pNode->pLeft = p;
    }
    return HeighIndex;
}

int TBalanceTree::LeftTreeBalancing(PTBalanceNode &pNode) {
    int HeighIndex = HeightOK;
    switch (pNode->GetBalance()) {
    case BalRight:
        pNode->SetBalance(BalOk);
        HeighIndex = HeightOK;
        break;
    case BalOk:
        pNode->SetBalance(BalLeft);
        HeighIndex = HeighInc;
        break;
    case BalLeft:
        PTBalanceNode p1, p2;
        p1 = PTBalanceNode(pNode->pLeft);
        if (p1->GetBalance() == BalLeft) { // 1 x LL
            pNode->pLeft = p1->pRight;
            p1->pRight = pNode;
            pNode->SetBalance(BalOk);
            pNode = p1;
        }
        else if (p1->GetBalance() == BalRight) { // 2 x LR
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
            return HeighInc;
        }
        pNode->SetBalance(BalOk);
        HeighIndex = 0;
    }
    return HeighIndex;
}

int TBalanceTree::RightTreeBalancing(PTBalanceNode &pNode) {
    int HeighIndex = HeightOK;
    switch (pNode->GetBalance()) {
    case BalLeft:
        pNode->SetBalance(BalOk);
        HeighIndex = HeightOK;
        break;
    case BalOk:
        pNode->SetBalance(BalRight);
        HeighIndex = HeighInc;
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
            return HeighInc;
        }
        pNode->SetBalance(BalOk);
        HeighIndex = 0;
    }
    return HeighIndex;
}

void TBalanceTree::DelRecord(TKey k)
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
            s.push({ p, 0 });
            p = (PTBalanceNode*)&(*p)->pLeft;
        }
        else if ((*p)->GetKey() < k)
        {
            s.push({ p, 1 });
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
                s.push({ p, 1 });
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
                s.push({ p, 1 });
                s.push({ (PTBalanceNode*)&(*p)->pRight, 0 });
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