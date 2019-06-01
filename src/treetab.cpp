#include "treetab.h"

PTDatValue TTreeTable::FindRecord(TKey k)
{
    PTTreeNode pNode = pRoot;
    ppRef = &pRoot;
    Efficiency = 0;
    while (pNode != nullptr)
    {
        Efficiency++;
        if (pNode->Key == k)
            break;
        if (pNode->Key < k)
            ppRef = &pNode->pRight;
        else
            ppRef = &pNode->pLeft;
        pNode = *ppRef;
    }

    SetRetCode(TabOK);
    return (pNode == nullptr) ? nullptr : pNode->pValue;
}

void TTreeTable::InsRecord(TKey k, PTDatValue pVal)
{
    if (IsFull())
        SetRetCode(TabFull);
    else if (FindRecord(k) != nullptr)
        SetRetCode(TabRecDbl);
    else
    {
        SetRetCode(TabOK);
        *ppRef = new TTreeNode(k, pVal);
        DataCount++;
    }
}

void TTreeTable::DelRecord(TKey k)
{
    if (FindRecord(k) == nullptr)
        SetRetCode(TabNoRec);
    else
    {
        PTTreeNode pNode = *ppRef;

        if (pNode->pRight == nullptr)
            *ppRef = pNode->pLeft;
        else if (pNode->pLeft == nullptr)
            *ppRef = pNode->pRight;
        else
        {
            PTTreeNode pN = pNode->pLeft, *ppN = &pNode->pLeft;

            while (pN->pRight != nullptr)
            {
                Efficiency++;
                ppN = &pN->pRight;
                pN = *ppN;
            }

            pNode->Key = pN->Key;
            pNode->pValue = pN->pValue;

            *ppN = pN->pLeft;

            pNode = pN;
        }

        DataCount--;
        delete pNode;
    }
}

void TTreeTable::DeleteTreeTab(PTTreeNode pNode)
{
    if (pNode == nullptr)
    {
        DeleteTreeTab(pNode->pLeft);
        DeleteTreeTab(pNode->pRight);
        delete pNode;
    }
}

int TTreeTable::IsFull() const
{
    PTTreeNode pNode = new TTreeNode();
    int tmp = pNode == nullptr;
    delete pNode;
    return tmp;
}

TKey TTreeTable::GetKey(void) const
{
    return (pCurrent == nullptr) ? string("") : pCurrent->Key;
}

PTDatValue TTreeTable::GetValuePtr(void) const
{
    return (pCurrent == nullptr) ? nullptr : pCurrent->pValue;
}

int TTreeTable::Reset(void)
{
    PTTreeNode pNode = pCurrent = pRoot;
    while (!St.empty())
        St.pop();
    CurrPos = 0;
    while (pNode != nullptr)
    {
        St.push(pNode);
        pCurrent = pNode;
        pNode = pNode->GetLeft();
    }
    SetRetCode(TabOK);
    return IsTabEnded();
}

int TTreeTable::IsTabEnded(void) const
{
    return CurrPos >= DataCount;
}

int TTreeTable::GoNext(void)
{
    if (!IsTabEnded())
    {
        PTTreeNode pNode = pCurrent = pCurrent->pRight;
        St.pop();
        while (pNode != nullptr) {
            St.push(pNode);
            pCurrent = pNode;
            pNode = pNode->GetLeft();
        }
        if (pCurrent == nullptr && !St.empty())
            pCurrent = St.top();
        CurrPos++;
        return TabOK;
    }
    else
        return 0;
}