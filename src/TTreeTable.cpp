#include "TTreeTable.h"

void TTreeTable::DeleteTreeTab (PTTreeNode pNode)
{
    if (pNode)
    {
        DeleteTreeTab(pNode->GetLeft());
        DeleteTreeTab(pNode->GetRight());
        delete pNode;
    }
}

int TTreeTable::IsFull ( ) const
{
    return 0;
}

PTDatValue TTreeTable::FindRecord (TKey k)
{
    PTTreeNode p = pRoot;
    ppRef = &pRoot;
    while (p != nullptr)
    {
        ++Efficiency;
        if (p->GetKey() == k)
            return p;
        if (p->GetKey() > k)
        {
            ppRef = &p->pLeft;
            p = p->GetLeft();
        }
        else
        {
            ppRef = &p->pRight;
            p = p->GetRight();
        }
    }
    ++Efficiency;
    return nullptr;
}

void TTreeTable::InsRecord (TKey k, PTDatValue pVal )
{
    if (FindRecord(k) != nullptr)
        (*ppRef)->SetValuePtr(pVal);
    else
    {
        *ppRef = new TTreeNode(k, pVal);
        ++DataCount;
    }
}

void TTreeTable::DelRecord (TKey k)
{
    if (FindRecord(k) == nullptr)
        return;
    if ((*ppRef)->GetLeft() == nullptr)
    {
        PTTreeNode p = *ppRef;
        (*ppRef) = (*ppRef)->GetRight();
        delete p;
    }
    else if ((*ppRef)->GetRight() == nullptr)
    {
        PTTreeNode p = *ppRef;
        (*ppRef) = (*ppRef)->GetLeft();
        delete p;
    }
    else
    {
        PTTreeNode l = (*ppRef)->GetLeft();
        PTTreeNode r = (*ppRef)->GetRight();
        PTTreeNode old_l = l;
        PTTreeNode old_r = r;
        while(1)
        {
            ++Efficiency;
            if (l->GetRight() == nullptr)
            {
                old_l->pRight = l->GetLeft();
                l->pRight = (*ppRef)->GetRight();
                if (l != old_l)
                    l->pLeft = (*ppRef)->GetLeft();
                delete (*ppRef);
                (*ppRef) = l;
                break;
            }
            else if (r->GetLeft() == nullptr)
            {
                old_r->pLeft = r->GetRight();
                r->pLeft = (*ppRef)->GetLeft();
                if (r != old_r)
                    r->pRight = (*ppRef)->GetRight();
                delete (*ppRef);
                (*ppRef) = r;
                break;
            }
            old_l = l;
            old_r = r;
            l = l->GetRight();
            r = r->GetLeft();
        }
    }
    --DataCount;
}

TKey TTreeTable::GetKey (void) const
{
    if (IsEmpty())
        throw std::runtime_error("get when table is empty");
    return pCurrent->GetKey();
}

PTDatValue TTreeTable::GetValuePTR (void) const
{
    if (IsEmpty())
        throw std::runtime_error("get when table is empty");
    return pCurrent->GetValuePTR();
}

int TTreeTable::Reset (void)
{
    CurrPos = 0;
    while (St.size())
        St.pop();
    PTTreeNode p = pRoot;
    while (p)
    {
        St.push(p);
        p = p->GetLeft();
    }
    pCurrent = (St.size()) ? St.top() : nullptr;
    return IsTabEnded();
}

int TTreeTable::IsTabEnded (void) const
{
    return DataCount == CurrPos;
}

int TTreeTable::GoNext (void)
{
    St.pop();
    PTTreeNode p = pCurrent->GetRight();
    while (p)
    {
        St.push(p);
        p = p->GetLeft();
    }
    if (St.size())
        pCurrent = St.top();
    else
        pCurrent = nullptr;
    ++CurrPos;
    return IsTabEnded();
}
