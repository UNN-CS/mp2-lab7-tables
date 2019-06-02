// TTreeTable.cpp
#include "TTreeTable.h"

int TTreeTable::IsFull() const {
    return 0;
}

PTDatValue TTreeTable::FindRecord(TKey k) {
    PTTreeNode pNode = pRoot;
    ppRef = &pRoot;
    while (pNode != nullptr) {
        Efficiency++;
        if (pNode->Key == k)
            return pNode;
        if (pNode->Key < k) {
            ppRef = &pNode->pRight;
            pNode = pNode->GetRight();
        }
        else {
            ppRef = &pNode->pLeft;
            pNode = pNode->GetLeft();
        }
    }
    return nullptr;
}

void TTreeTable::InsRecord(TKey k, PTDatValue pVal) {
    if (FindRecord(k) != nullptr)
        (*ppRef)->SetValuePtr(pVal);
    else {
        *ppRef = new TTreeNode(k, pVal);
        DataCount++;
    }
}

void TTreeTable::DelRecord(TKey k) {
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
        while (1)
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

TKey TTreeTable::GetKey() const {
    return (pCurrent == nullptr) ? std::string("") : pCurrent->Key;
}

PTDatValue TTreeTable::GetValuePTR() const {
    return (pCurrent == nullptr) ? nullptr : pCurrent->pValue;
}

int TTreeTable::Reset() {
    PTTreeNode pNode = pCurrent = pRoot;
    while (!St.empty()) St.pop();
    CurrPos = 0;
    while (pNode != nullptr) {
        St.push(pNode);
        pCurrent = pNode;
        pNode = pNode->GetLeft();
    }
    return IsTabEnded();
}

int TTreeTable::IsTabEnded() const {
    return CurrPos >= DataCount;
}

int TTreeTable::GoNext() {
    St.pop();

    PTTreeNode pNode = pCurrent->GetRight();
    while (pNode && !IsTabEnded()) {
        St.push(pNode);
        pNode = pNode->GetLeft();
    }
    if (St.size() != 0)
        pCurrent = St.top();
    else
        pCurrent = nullptr;

    CurrPos++;
    return IsTabEnded();
}

void TTreeTable::DeleteTreeTab(PTTreeNode pNode)
{
    if (pNode)
    {
        DeleteTreeTab(pNode->GetLeft());
        DeleteTreeTab(pNode->GetRight());
        delete pNode;
    }
}