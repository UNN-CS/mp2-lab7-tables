#include "TTreeTable.h"

void TTreeTable::DeleteTreeTab(PTTreeNode pNode)
{
    if (pNode != nullptr)
    {
        DeleteTreeTab(pNode->GetLeft());
        DeleteTreeTab(pNode->GetRight());
        delete pNode;
    }
}

int TTreeTable::IsFull() const
{
    return 0;
}

PTDatValue TTreeTable::FindRecord(TKey k)
{
    PTTreeNode tmp = pRoot;
    ppRef = &pRoot;
    while (tmp != nullptr)
    {
        if (tmp->GetKey() == k)
            break;
        if (tmp->GetKey() < k)
            ppRef = &tmp->pRight;
        else
            ppRef = &tmp->pLeft;
        tmp = *ppRef;
    }
    if (tmp == nullptr)
    {
        SetRetCode(TabNoRec);
        return nullptr;
    }
    else
    {
        SetRetCode(TabOK);
        return tmp->GetValuePTR();
    }
    Efficiency++;
}

void TTreeTable::InsRecord(TKey k, PTDatValue pVal)
{
    if (IsFull())
    {
        SetRetCode(TabFull);
    }
    else
    {
        if (FindRecord(k) != nullptr)
        {
            SetRetCode(TabRecDbl);
        }
        else
        {
            *ppRef = new TTreeNode(k, pVal);
            DataCount++;
        }
    }
}

void TTreeTable::DelRecord(TKey k)
{
    FindRecord(k);
    if (GetRetCode() == TabNoRec)
    {
        SetRetCode(TabNoRec);
    }
    else
    {
        PTTreeNode tmp = pRoot;

        while (!St.empty())
            St.pop();
        while (tmp->GetKey() != k)
        {
            St.push(tmp);
            if (tmp->GetKey() < k)
                tmp = tmp->GetRight();
            else
                tmp = tmp->GetLeft();
        }
        // удаление листа
        if ((tmp->pLeft == nullptr) && (tmp->pRight == nullptr))
        {
            if (!St.empty())
            {
                PTTreeNode prev = St.top();
                if (prev != nullptr)
                {
                    if (prev->GetRight() == tmp)
                        prev->pRight = nullptr;
                    else if (prev->GetLeft() == tmp)
                        prev->pLeft = nullptr;
                }
            }
            else
            {
                pRoot = nullptr;
            }
            delete tmp;
            DataCount--;
        }
        // удаление звена с одним потомком (справа)
        else if (tmp->pLeft == nullptr)
        {
            if (!St.empty())
            {
                PTTreeNode prev = St.top();
                if (prev != nullptr)
                {
                    if (prev->GetRight() == tmp)
                        prev->pRight = tmp->pRight;
                    if (prev->GetLeft() == tmp)
                        prev->pLeft = tmp->pRight;
                }
            }
            else
            {
                pRoot = tmp->GetRight();
            }
            delete tmp;
            DataCount--;
        }
        // удаление звена с одним потомком (слева)
        else if (tmp->pRight == nullptr)
        {
            if (!St.empty())
            {
                PTTreeNode prev = St.top();
                if (prev != nullptr)
                {
                    if (prev->GetRight() == tmp)
                        prev->pRight = tmp->pLeft;
                    if (prev->GetLeft() == tmp)
                        prev->pLeft = tmp->pLeft;
                }
            }
            else
            {
                pRoot = tmp->GetLeft();
            }
            delete tmp;
            DataCount--;
        }
        // удаление звена с двумя потомками
        else
        {
            PTTreeNode down_left = tmp->GetRight();
            while (down_left->GetLeft() != nullptr)
                down_left = down_left->pLeft;
            down_left->pLeft = tmp->GetLeft();

            if (!St.empty())
            {
                PTTreeNode prev = St.top();
                if (prev != nullptr)
                {
                    if (prev->GetRight() == tmp)
                        prev->pRight = tmp->pRight;
                    if (prev->GetLeft() == tmp)
                        prev->pLeft = tmp->pRight;
                }
            }
            else
            {
                pRoot = tmp->GetRight();
            }
            delete tmp;
            DataCount--;
        }
    }
}

TKey TTreeTable::GetKey(void) const
{
    return (pCurrent == nullptr) ? "" : pCurrent->GetKey();
}

PTDatValue TTreeTable::GetValuePTR(void) const
{
    return (pCurrent == nullptr) ? nullptr : pCurrent->GetValuePTR();
}

int TTreeTable::Reset(void)
{
    while (!St.empty())
        St.pop();
    PTTreeNode pNode = pCurrent = pRoot;
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
    return DataCount <= CurrPos;
}

int TTreeTable::GoNext(void)
{
    if (!IsTabEnded() && (pCurrent != nullptr))
    {
        PTTreeNode pNode = pCurrent = pCurrent->GetRight();
        St.pop();
        while (pNode != nullptr)
        {
            St.push(pNode);
            pCurrent = pNode;
            pNode = pNode->GetLeft();
        }
        if ((pCurrent == nullptr) && !St.empty())
            pCurrent = St.top();
        CurrPos++;
    }
    else
        SetRetCode(TabNoRec);
    return GetRetCode();
}