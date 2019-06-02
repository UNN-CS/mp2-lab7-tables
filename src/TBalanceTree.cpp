#include <math.h>
#include "TBalanceTree.h"

#define HeightOK 0 
#define HeightInc 1 

int TBalanceTree :: InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal) {
	Efficiency++;
	int HeighIndex = HeightOK;
	if ( pNode == nullptr ) {
		pNode = new TBalanceNode(k,pVal);
		HeighIndex = HeightInc;
		DataCount++;
	}
	else if ( k < pNode -> GetKey() ) {
		if ( InsBalanceTree((PTBalanceNode&)(pNode->pLeft),k,pVal) == HeightInc )
			HeighIndex = LeftTreeBalancing(pNode);
	}
	else if ( k > pNode->GetKey() ) {
		if ( InsBalanceTree((PTBalanceNode&)(pNode->pRight),k,pVal) == HeightInc )
			HeighIndex = RightTreeBalancing(pNode);
	}
	else
		throw -1; 
	return HeighIndex;
}

int TBalanceTree :: LeftTreeBalancing(PTBalanceNode &pNode) {
	int HeighIndex = HeightOK;
	switch ( pNode->GetBalance() ) {
    case BalRight: 
		pNode -> SetBalance(BalOk); 
        HeighIndex = HeightOK; 
		break;  
    case BalOk:    
		pNode->SetBalance(BalLeft);
        HeighIndex = HeightInc; 
		break;
    case BalLeft:
		Efficiency++;
        PTBalanceNode p1;
        p1 = PTBalanceNode(pNode->pLeft);
		if ( p1 ) break;
        if ( p1 -> GetBalance() == BalLeft ) {
			pNode->pLeft = p1->pRight;
            p1->pRight   = pNode;
            pNode->SetBalance(BalOk);
            pNode = p1;
        }
        else {
            PTBalanceNode p2 = PTBalanceNode (p1->pRight);
            p1->pRight   = p2->pLeft;
            p2->pLeft    = p1;
            pNode->pLeft = p2->pRight;
            p2->pRight = pNode;
            if ( p2->GetBalance()==BalLeft ) 
				p1->SetBalance(BalRight);
			else p1->SetBalance(BalOk);
            if ( p2->GetBalance()==BalRight) 
				pNode->SetBalance(BalLeft);
            else pNode->SetBalance(BalOk);
            pNode = p2;
        }
		pNode->SetBalance(BalOk);
		HeighIndex = HeightOK;
		break;
	}
	return HeighIndex;
}
int TBalanceTree :: RightTreeBalancing(PTBalanceNode &pNode) {
	int HeighIndex = HeightOK;
	switch ( pNode->GetBalance() ) {
    case BalLeft: 
		pNode -> SetBalance(BalOk);
        HeighIndex = HeightOK; 
		break;
    case BalOk:    
		pNode->SetBalance(BalRight);
        HeighIndex = HeightInc; 
		break;
    case BalRight:
		Efficiency++;
        PTBalanceNode p1;
        p1 = PTBalanceNode(pNode->pRight);
		if ( p1 ) break;
        if ( p1 -> GetBalance() >= 0 ) {
			pNode->pRight = p1->pLeft;
            p1->pLeft   = pNode; 
            pNode->SetBalance(BalOk);
            pNode = p1;
        }
        else {
            PTBalanceNode p2 = (PTBalanceNode)(p1->pLeft);
            p1->pLeft = p2->pRight;
			p2->pRight = p1;
			pNode->pRight = p2->pLeft;
			p2->pLeft = pNode;
            if ( p2->GetBalance()==BalRight ) 
				p1->SetBalance(BalLeft);
			else p1->SetBalance(BalOk);
            if ( p2->GetBalance()==BalLeft) 
				pNode->SetBalance(BalRight);
            else pNode->SetBalance(BalOk);
            pNode = p2;
        }
		pNode->SetBalance(BalOk);
        HeighIndex = HeightOK;
        break;
	}
	return HeighIndex;
}

int TBalanceTree :: DeleteBalTree(PTBalanceNode &pNode, TKey k) {
	Efficiency++;
	int HeighIndex = HeightOK;
	if (pNode == nullptr) 
		throw -1;
	else if (pNode && k < pNode -> Key) {
		if (DeleteBalTree((PTBalanceNode&)pNode -> pLeft, k))
			HeighIndex = RightDelBalancing(pNode);
		} else if (pNode && k > pNode -> Key) {
		if (DeleteBalTree((PTBalanceNode&)pNode -> pRight, k))
			HeighIndex = LeftDelBalancing(pNode);
		} else {
		PTTreeNode ptr = pNode;
		if (ptr -> pRight == nullptr) {
			pNode = (PTBalanceNode)ptr -> pLeft;
			HeighIndex = HeightInc;
		} else if (ptr -> pLeft == nullptr) {
			pNode = (PTBalanceNode)ptr -> pRight;
			HeighIndex = HeightInc;
		} else {
			 if (DelNode((PTBalanceNode&)ptr->pLeft, (PTBalanceNode&)ptr))
				HeighIndex = RightDelBalancing(pNode);
			}
		DataCount--;
		}
	}


int TBalanceTree :: RightDelBalancing(PTBalanceNode& pNode)
{
    int HeighIndex = HeightInc;

    switch (pNode->GetBalance())
    {
    case BalLeft:
        pNode->SetBalance(BalOk);
        break;
    case BalOk:
        pNode->SetBalance(BalRight);
        HeighIndex = HeightOK;
        break;
    case BalRight:
		PTBalanceNode p1;
		if ( p1 ) break;
        p1 = PTBalanceNode(pNode->pRight);
        if ( p1 -> GetBalance() >= 0 ) {
			pNode->pRight = p1->pLeft;
            p1->pLeft   = pNode;
             if (p1->GetBalance() == BalOk)
            {
                pNode->SetBalance(BalRight);
                p1->Balance = BalLeft;
                HeighIndex = HeightOK;
            }
            else
            {
                pNode->Balance = BalOk;
                p1->Balance = BalOk;
            }
            pNode = p1;
        }
        else
        {
            PTBalanceNode p2 = (PTBalanceNode)(p1->pLeft);
            p1->pLeft = p2->pRight;
			p2->pRight = p1;
			pNode->pRight = p2->pLeft;
			p2->pLeft = pNode;
            if (p2->GetBalance() == BalRight) pNode->SetBalance(BalLeft);
            else pNode->SetBalance(BalOk);
            if (p2->GetBalance() == BalLeft) p1->SetBalance(BalRight);
            else p1->SetBalance(BalOk);

            pNode = p2;
            p2->SetBalance(BalOk);
        }
    }
    return HeighIndex;
}

int TBalanceTree :: LeftDelBalancing(PTBalanceNode& pNode)
{
    int HeighIndex = HeightInc;

    switch (pNode->Balance)
    {
    case BalRight:
        pNode->SetBalance(BalOk);
        break;
    case BalOk:
        pNode->SetBalance(BalLeft);
        HeighIndex = HeightOK;
        break;
    case BalLeft:
        PTBalanceNode p1;
		if ( p1 ) break;
        p1 = PTBalanceNode(pNode->pLeft);
        if ( p1 -> GetBalance() == BalLeft ) {
			pNode->pLeft = p1->pRight;
            p1->pRight   = pNode; 
            if (p1->Balance == BalOk)
            {
                pNode->SetBalance(BalLeft);
                p1->SetBalance(BalRight);
                HeighIndex = HeightOK;
            }
            else
            {
                pNode->SetBalance(BalOk);
                p1->SetBalance(BalOk);
            }
            pNode = p1;
        }
        else
        {
            PTBalanceNode p2 = PTBalanceNode (p1->pRight);
            p1->pRight   = p2->pLeft;
            p2->pLeft    = p1;  
            pNode->pLeft = p2->pRight;
            p2->pRight   = pNode;

            if (p2->Balance == BalLeft) pNode->SetBalance(BalRight);
            else pNode->SetBalance(BalOk);
            if (p2->Balance == BalRight) p1->SetBalance(BalLeft);
            else p1->SetBalance(BalOk);

            pNode = p2;
            p2->SetBalance(BalOk);
        }
    }
    return HeighIndex;
}


int TBalanceTree::DelNode(PTBalanceNode& pNode, PTBalanceNode& pParent)
{
    bool HeighIndex = HeightOK;

    if (pNode->pRight != nullptr) {
        if (DelNode((PTBalanceNode&)pNode->pRight, pParent))
            HeighIndex = LeftDelBalancing(pNode);
    }
    else {
        delete pParent->pValue;
        pParent->Key = pNode->Key;
        pParent->pValue = pNode->pValue;
        pNode->pValue = nullptr;
        pNode = (PTBalanceNode)pNode->pLeft;
        HeighIndex = HeightInc;
    }
    return HeighIndex;
}

void TBalanceTree :: InsRecord (TKey k, PTDatValue pVal ) {
	if (IsFull()) throw -1;
	InsBalanceTree((PTBalanceNode&)pRoot,k,pVal);
}
void TBalanceTree :: DelRecord (TKey k) {
	if (IsEmpty()) 
		throw -1;
	DeleteBalTree((PTBalanceNode&)pRoot,k);

}
