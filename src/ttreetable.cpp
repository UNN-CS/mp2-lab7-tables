#include "ttreetable.h"

int TTreeTable::IsFull() const {
    PTTreeNode pNode = new TTreeNode();
    int temp = pNode == nullptr;
    delete pNode;
    return temp;
}

PTDatValue TTreeTable::FindRecord(TKey k) {
    PTTreeNode pNode = pRoot;
    ppRef = &pRoot;
    Efficiency = 0;
    while(pNode != nullptr) {
        Efficiency++;
        if(pNode->Key == k)
            break;
        if(k >= pNode->Key)
            ppRef = &pNode->pRight;
        else
            ppRef = &pNode->pLeft;
        pNode = *ppRef;
    }
    return (pNode == nullptr)?nullptr:pNode->pValue;
}

void TTreeTable::InsRecord(TKey k, PTDatValue pVal) {
    if(IsFull())
        throw TabFull;
    if(FindRecord(k) != nullptr)
        throw TabRecDbl;
    *ppRef = new TTreeNode(k, pVal);
    DataCount++;
}

void TTreeTable::DelRecord(TKey k) {
    if(IsEmpty())
        throw TabEmpty;
    if(FindRecord(k) == nullptr)
        throw TabNoRec;
    PTTreeNode pNode = *ppRef;
    if(pNode->pRight == nullptr)
        *ppRef = pNode->pLeft;
    else if(pNode->pLeft == nullptr)
        *ppRef = pNode->pRight;
    else
    {
        PTTreeNode pN = pNode->pLeft, *ppR = &pNode->pLeft;
        while(pN->pRight != nullptr) {
            ppR = &pN->pRight;
            pN = *ppR;
        }
        pNode->pValue = pN->pValue;
        pNode->Key = pN->Key;
        pNode = pN;
        *ppR = pN->pLeft;  // ?
    }
    delete pNode;
    // CHECK IT!
    // >:-/
}

TKey TTreeTable::GetKey() const {
    return (pCurrent == nullptr)?std::string(""):pCurrent->Key;
}

PTDatValue TTreeTable::GetValuePtr() const {
    return (pCurrent == nullptr)?nullptr:pCurrent->pValue;
}

int TTreeTable::Reset() {
    PTTreeNode pNode = pCurrent = pRoot;
    while(!St.empty())
        St.pop();
    CurrPos = 0;
    while(pNode != nullptr) {
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
    if(!IsTabEnded() && (pCurrent != nullptr)) {
        PTTreeNode pNode = pCurrent = pCurrent->GetRight();
        St.pop();
        while(pNode != nullptr) {
            St.push(pNode);
            pCurrent = pNode;
            pNode = pNode->GetLeft();
        }
        if(pCurrent == nullptr && !St.empty())
            pCurrent = St.top();
        CurrPos++;
    }
    return 0;//????
    // >:-/
}

