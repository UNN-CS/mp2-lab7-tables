#include <iostream>
#include "ttreetable.h"
#include "tword.h"


bool TTreeTable::IsFull() const {
    return currPos == DataCount;
}       /*================================================*/

PTDatValue TTreeTable::FindRecord(TKey k) {
    PTTreeNode pNode = pRoot;
    ppRef = &pRoot;

    while (pNode) {
        ++Efficiency;
        if (pNode->key == k)
            break;
        if (pNode->key < k)
            ppRef = &pNode->pRight;
        else
            ppRef = &pNode->pLeft;
        pNode = *ppRef;
    }
    ++Efficiency;
    return pNode ? pNode->pValue : nullptr;
}       /*================================================*/

void TTreeTable::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull())
        throw -1;
    if (FindRecord(k))
        return;
    *ppRef = new TTreeNode(k, pVal);
    ++DataCount;
}       /*================================================*/

void TTreeTable::DelRecord(TKey k) {
    PTDatValue tmp = FindRecord(k);
    if (!tmp)
        return;
    PTTreeNode pNode = *ppRef;
    if (!pNode->pRight)
        *ppRef = pNode->pLeft;
    else if (!pNode->pLeft)
        *ppRef = pNode->pRight;
    else {
        PTTreeNode pN = pNode->pLeft, *ppR = &pNode->pLeft;
        while (pN->pRight) {
            ++Efficiency;
            ppR = &pN->pRight;
            pN = *ppR;
        }
        pNode->pValue = pN->pValue;
        pNode->key = pN->key;
        pNode = pN;
        *ppR = pN->pLeft;
    }
    --DataCount;
    delete pNode;
}       /*================================================*/

TKey TTreeTable::GetKey() const {
    return pCurrent ? pCurrent->key : "";
}       /*================================================*/

PTDatValue TTreeTable::GetValuePTR() const {
    return pCurrent ? pCurrent->pValue : nullptr;
}       /*================================================*/

int TTreeTable::Reset() {
    PTTreeNode pNode = pCurrent = pRoot;
    while (st.size())
        st.pop();
    currPos = 0;
    while (pNode) {
        st.push(pNode);
        pCurrent = pNode;
        pNode = pNode->pLeft;
    }
    return IsTabEnded();
}       /*================================================*/

int TTreeTable::IsTabEnded() const {
    return currPos >= DataCount;
}       /*================================================*/

int TTreeTable::GoNext() {
    PTTreeNode pNode = pRoot;
    if (!IsTabEnded() && pCurrent) {
        pNode = pCurrent = pCurrent->pRight;
        st.pop();
        while(pNode) {
            st.push(pNode);
            pCurrent = pNode;
            pNode = pNode->pLeft;
        }
        if (!pCurrent && st.size())
            pCurrent = st.top();
        ++currPos;
    }
    return IsTabEnded();
}       /*================================================*/

void TTreeTable::DeleteTreeTab (PTTreeNode pNode) {
    if (pNode) {
        DeleteTreeTab(pNode->pLeft);
        DeleteTreeTab(pNode->pRight);
    }
    delete pNode;
}       /*================================================*/

void TTreeTable::Print(PTTreeNode pNode, int depth) {
    if (pNode) {
        Print(pNode->pLeft, depth + 1);
        std::cout << pNode->key << " " << ((PTWord)(pNode->pValue))->GetWord() << " " << depth << std::endl;
        Print(pNode->pRight, depth + 1);
    }
}       /*================================================*/
