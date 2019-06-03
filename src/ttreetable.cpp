#include "ttreetable.h"

int TTreeTable::IsFull() const {
    PTTreeNode pNode = new TTreeNode();
    int tmp = pNode == nullptr;
    delete pNode;
    return tmp;
}

PTDatValue TTreeTable::FindRecord(TKey k) {
    PTTreeNode pNode = pRoot;
    ppRef = &pRoot;
    while (pNode) {
        ++Efficiency;
        if (pNode->Key == k)
            break;
        if (pNode->Key < k)
            ppRef = &pNode->pRight;
        else
            ppRef = &pNode->pLeft;
        pNode = *ppRef;
    }
    ++Efficiency;
    return pNode ? pNode->pValue : nullptr;
}

void TTreeTable::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull()) throw "Error: is full";
    if (FindRecord(k) != nullptr)
        return;
    *ppRef = new TTreeNode(k, pVal);
    ++DataCount;
}

void TTreeTable::DelRecord(TKey k) {
    PTDatValue tmp = FindRecord(k);
    if (tmp == nullptr)
        return;
    PTTreeNode pNode = *ppRef;
    if (pNode->pRight == nullptr)
        *ppRef = pNode->pLeft;
    else if (pNode->pLeft == nullptr)
        *ppRef = pNode->pRight;
    else {
        PTTreeNode pN = pNode->pLeft, *ppN = &pNode->pLeft;
        while (pN->pRight != nullptr) {
            ++Efficiency;
            ppN = &pN->pRight;
            pN = *ppN;
        }
        pNode->pValue = pN->pValue;
        pNode->Key = pN->Key;
        pNode = pN;
        *ppN = pN->pLeft;
    }
    --DataCount;
    delete pNode;
}

TKey TTreeTable::GetKey() const {
    return (pCurrent == nullptr) ? "" : pCurrent->Key;
}

PTDatValue TTreeTable::GetValuePtr() const {
    return (pCurrent == nullptr) ? nullptr : pCurrent->pValue;
}

int TTreeTable::Reset() {
    PTTreeNode pNode = pCurrent = pRoot;
    while (!St.empty())
        St.pop();
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
    PTTreeNode pNode = pRoot;
    if (!IsTabEnded() && (pCurrent != nullptr)) {
        pNode = pCurrent = pCurrent->pRight;
        St.pop();
        while (pNode != nullptr) {
            St.push(pNode);
            pCurrent = pNode;
            pNode = pNode->pLeft;
        }
        if ((pCurrent == nullptr) && !St.empty())
            pCurrent = St.top();
        ++CurrPos;
    }
    return IsTabEnded();
}

void TTreeTable::DeleteTreeTab(PTTreeNode pNode) {
    if (pNode != nullptr) {
        DeleteTreeTab(pNode->pLeft);
        DeleteTreeTab(pNode->pRight);
    }
    delete pNode;
}
