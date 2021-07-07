#include "treetable.h"

#include "treenode.h"

TTreeTable::TTreeTable() : TTable() {
    currPos = 0;
    pRoot = pCurrent = nullptr;
    ppRef = nullptr;
}

TTreeTable::~TTreeTable() {
    DeleteTreeTab(pRoot);
}

bool TTreeTable::IsFull() const {
    return false;
}

PTDatValue TTreeTable::FindRecord(TKey k) {
    PTTreeNode p = pRoot;
    ppRef = &pRoot;
    while (p != nullptr) {
        ++efficiency;
        if (p->GetKey() == k) {
            return p;
        }
        if (p->GetKey() > k) {
            ppRef = &p->pLeft;
            p = p->GetLeft();
        } else {
            ppRef = &p->pRight;
            p = p->GetRight();
        }
    }
    ++efficiency;
    return nullptr;
}

void TTreeTable::InsRecord(TKey k, PTDatValue pVal) {
    if (FindRecord(k) == nullptr) {
        return;
    }

    *ppRef = new TTreeNode(k, pVal);
    ++dataCount;
}

void TTreeTable::DelRecord(TKey k) {
    if (FindRecord(k) == nullptr) {
        return;
    }
    if ((*ppRef)->GetLeft() == nullptr) {
        PTTreeNode p = *ppRef;
        (*ppRef) = (*ppRef)->GetRight();
        delete p;
    } else if ((*ppRef)->GetRight() == nullptr) {
        PTTreeNode p = *ppRef;
        (*ppRef) = (*ppRef)->GetLeft();
        delete p;
    } else {
        PTTreeNode l = (*ppRef)->GetLeft();
        PTTreeNode r = (*ppRef)->GetRight();
        PTTreeNode oldL = l;
        PTTreeNode oldR = r;
        while (true) {
            ++efficiency;
            if (l->GetRight() == nullptr) {
                oldL->pRight = l->GetLeft();
                l->pRight = (*ppRef)->GetRight();
                if (l != oldL) {
                    l->pLeft = (*ppRef)->GetLeft();
                }
                delete (*ppRef);
                (*ppRef) = l;
                break;
            } else if (r->GetLeft() == nullptr) {
                oldR->pLeft = r->GetRight();
                r->pLeft = (*ppRef)->GetLeft();
                if (r != oldR) {
                    r->pRight = (*ppRef)->GetRight();
                }
                delete (*ppRef);
                (*ppRef) = r;
                break;
            }
            oldL = l;
            oldR = r;
            l = l->GetRight();
            r = r->GetLeft();
        }
    }
    --dataCount;
}

TKey TTreeTable::GetKey() const {
    return pCurrent->GetKey();
}

PTDatValue TTreeTable::GetValuePtr() const {
    return pCurrent->GetValuePtr();
}

bool TTreeTable::Reset() {
    currPos = 0;
    pCurrent = nullptr;

    while (st.size() > 0) {
        st.pop();
    }

    PTTreeNode tmp = pRoot;

    while (tmp != nullptr) {
        st.push(tmp);
        tmp = tmp->GetLeft();
    }

    if (st.size() > 0) {
        pCurrent = st.top();
    }

    return IsTabEnded();
}

bool TTreeTable::IsTabEnded() const {
    return currPos >= dataCount;
}

bool TTreeTable::GoNext() {
    st.pop();
    PTTreeNode p = pCurrent->GetRight();
    while (p) {
        st.push(p);
        p = p->GetLeft();
    }
    if (st.size()) {
        pCurrent = st.top();
    }
    else {
        pCurrent = nullptr;
    }
    ++currPos;
    return IsTabEnded();
}

void TTreeTable::DeleteTreeTab(PTTreeNode p) {
    if (p != nullptr) {
        DeleteTreeTab(p->GetLeft());
        DeleteTreeTab(p->GetRight());
    }
}
