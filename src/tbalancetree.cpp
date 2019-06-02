#include "tbalancetree.h"

void TBalanceTree::InsRecord(TKey k, PTDatValue pVal) {
    if (IsFull())
        SetRetCode(TabFull);
    else 
        InsBalanceTree((PTBalanceNode&)pRoot, k, pVal);
}

int TBalanceTree::InsBalanceTree(PTBalanceNode &pNode, TKey k, PTDatValue pVal) {
    int HeightIndex = HeightOK;

    if (pNode == NULL) {                // вставка вершины
        SetRetCode(TabOK);
        pNode = new TBalanceNode(k, pVal);
        HeightIndex = HeightInc;
        DataCount++;
    } else if (k < pNode->GetKey()) {
        if (InsBalanceTree((PTBalanceNode&)(pNode->pLeft), k, pVal) == HeightInc)
            // после вставки высота левого поддерева увеличилась - балансировка
            HeightIndex = LeftTreeBalancing(pNode);
    } else if (k > pNode->GetKey()) {
        if (InsBalanceTree((PTBalanceNode&)(pNode->pRight), k, pVal) == HeightInc)
            // после вставки высота правого поддерева увеличилась - балансировка
            HeightIndex = RightTreeBalancing(pNode);
    } else {
        SetRetCode(TabRecDbl);
        HeightIndex = HeightOK;
    }

    return HeightIndex;
}       /*================================================*/

int TBalanceTree::LeftTreeBalancing(PTBalanceNode &pNode) {
    int HeightIndex = HeightOK;

    switch (pNode->GetBalance()) {              // проверка предыдущей банасировки
    case BalRight:  pNode->SetBalance(BalOk);   // в поддереве был перевес справа
         HeightIndex = HeightOK; break;         // устанавливается равновесие
    case BalOk:     pNode->SetBalance(BalLeft); // в поддереве было равновесие
         HeightIndex = HeightInc; break;        // устанавливается перевес слева
    case BalLeft:      // в поддереве был перевес слева - необходима балансировка
        PTBalanceNode p1, p2;
        p1 = PTBalanceNode(pNode->pLeft);
        if (p1->GetBalance() == BalLeft) {      // случай 1 - однократный LL поворот
            pNode->pLeft = p1->pRight;  // 1
            p1->pRight   = pNode;       // 2
            pNode->SetBalance(BalOk);   // 3
            pNode = p1;
        } else {                                // случай 2 - двукратный LR поворот
            p2 = PTBalanceNode(p1->pRight);
            p1->pRight   = p2->pLeft;       // 1
            p2->pLeft    = p1;              // 2
            pNode->pLeft = p2->pRight;      // 3
            p2->pRight   = pNode;           // 4
            if (p2->GetBalance() == BalLeft) pNode->SetBalance(BalRight);
            else pNode->SetBalance(BalOk);  // 5

            if (p2->GetBalance() == BalRight) pNode->SetBalance(BalLeft);
            else p1->SetBalance(BalOk);     // 6

            pNode = p2;
        }

        pNode->SetBalance(BalOk); HeightIndex = HeightOK;
    }

    return HeightIndex;
}       /*================================================*/

int TBalanceTree::RightTreeBalancing(PTBalanceNode &pNode) {
    int HeightIndex = HeightOK;

    switch (pNode->GetBalance()) {                  // проверка предыдущей банасировки
    case BalLeft:  pNode->SetBalance(BalOk);        // в поддереве был перевес слева
         HeightIndex = HeightOK; break;             // устанавливается равновесие
    case BalOk:     pNode->SetBalance(BalRight);    // в поддереве было равновесие
         HeightIndex = HeightInc; break;            // устанавливается перевес справа
    case BalRight:      // в поддереве был перевес справа - необходима балансировка
        PTBalanceNode p1, p2;
        p1 = PTBalanceNode(pNode->pRight);
        if (p1->GetBalance() == BalRight) {     // случай 1 - однократный RR поворот
            pNode->pRight = p1->pLeft;  // 1
            p1->pLeft     = pNode;      // 2
            pNode->SetBalance(BalOk);   // 3
            pNode = p1;
        } else {                                // случай 2 - двукратный RL поворот
            p2 = PTBalanceNode(p1->pLeft);
            p1->pLeft     = p2->pRight;     // 1
            p2->pRight    = p1;             // 2
            pNode->pRight = p2->pLeft;      // 3
            p2->pLeft     = pNode;          // 4
            if (p2->GetBalance() == BalRight) pNode->SetBalance(BalLeft);
            else pNode->SetBalance(BalOk);  // 5

            if (p2->GetBalance() == BalLeft) pNode->SetBalance(BalRight);
            else p1->SetBalance(BalOk);     // 6

            pNode = p2;
        }

        pNode->SetBalance(BalOk); HeightIndex = HeightOK;
    }

    return HeightIndex;
}       /*================================================*/
