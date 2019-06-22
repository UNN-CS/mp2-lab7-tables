#include "TTreeTable.h"

int TTreeTable::IsFull()const {
    PTTreeNode pNode = new TTreeNode();
    int temp = pNode == NULL;
    delete pNode;
    return temp;
}

PTDatValue TTreeTable::FindRecord(TKey k) {
    PTTreeNode pNode = pRoot;
    ppRef = &pRoot;
    Efficiency = 0;
    while (pNode != NULL) {
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
    return (pNode == NULL) ? NULL : pNode->pValue;
}

void TTreeTable::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull())
        SetRetCode(TabFull);
    else if (FindRecord(k) != NULL)
        SetRetCode(TabRecDbl);
    else {
        SetRetCode(TabOK);
        *ppRef = new TTreeNode(k, pVal);
        DataCount++;
    }
}

void TTreeTable::DelRecord(TKey k) {
    PTDatValue tmp = FindRecord(k);
    if (tmp == NULL) SetRetCode(TabNoRec);
    else
    {
        SetRetCode(TabOK);
        PTTreeNode pNode = *ppRef;
        if (pNode->pRight == NULL)
            *ppRef = pNode->pLeft;
        else if (pNode->pLeft == NULL)
            *ppRef = pNode->pRight;
        else
        {
            PTTreeNode pN = pNode->pLeft, *ppR = &pNode->pLeft;
            while (pN->pRight != NULL)
            {
                ppR = &pN->pRight;
                pN = *ppR;
            }
            pNode->pValue = pN->pValue;
            pNode->Key = pN->Key;
            pNode = pN;
            *ppR = pN->pLeft;
        }
        delete pNode;
        DataCount--;
    }
}

TKey TTreeTable::GetKey()const {
    return (pCurrent == NULL) ? string("") : pCurrent->Key;
}

PTDatValue TTreeTable::GetValuePTR()const {
    return (pCurrent == NULL) ? NULL : pCurrent->pValue;
}

int TTreeTable::Reset() {
    PTTreeNode pNode = pCurrent = pRoot;
    while (!St.empty()) St.pop();
    CurrPos = 0;
    while (pNode != NULL)
    {
        St.push(pNode);
        pCurrent = pNode;
        pNode = pNode->pLeft;
    }
    SetRetCode(TabOK);
    return IsTabEnded();
}

int TTreeTable::IsTabEnded() const {
    return CurrPos >= DataCount;
}

int TTreeTable::GoNext() {
    if (!IsTabEnded() && (pCurrent != NULL))
    {
        PTTreeNode pNode = pCurrent = pCurrent->pRight;
        St.pop();
        while (pNode != NULL)
        {
            St.push(pNode);
            pCurrent = pNode;
            pNode = pNode->pLeft;
        }
        if (pCurrent == NULL && (!St.empty()))
            pCurrent = St.top();
        CurrPos++;
    }
    return IsTabEnded();
}

void TTreeTable::DeleteTreeTab(PTTreeNode pNode) {
    if (pNode != NULL) {
        DeleteTreeTab(pNode->pLeft);
        DeleteTreeTab(pNode->pRight);
        delete pNode;
    }
}