// TTreeTable.h
#ifndef _TREETAB_H
#define _TREETAB_H

#include <stack>
#include "TTable.h"
#include "TTreeNode.h"

class  TTreeTable : public TTable {
protected:
    PTTreeNode pRoot; // указатель на корень дерева
    PTTreeNode *ppRef;// адрес указателя на вершину-результата в FindRecord
    PTTreeNode pCurrent;// указатель на текущую вершину
    int CurrPos;        // номер текущей вершины
    std::stack < PTTreeNode> St;// стек для итератора
    void DeleteTreeTab(PTTreeNode pNode); // удаление
public:
    TTreeTable() : TTable() { CurrPos = 0; pRoot = pCurrent = NULL; ppRef = NULL; }
    ~TTreeTable() { DeleteTreeTab(pRoot); } // деструктор
    // информационные методы
    virtual int IsFull() const; //заполнена?
    //основные методы
    virtual PTDatValue FindRecord(TKey k); // найти запись
    virtual void InsRecord(TKey k, PTDatValue pVal); // вставить
    virtual void DelRecord(TKey k);       // удалить запись
    // навигация
    virtual TKey GetKey(void) const;
    virtual PTDatValue GetValuePTR(void) const;
    virtual int Reset(void);  // установить на первую запись
    virtual int IsTabEnded(void) const; // таблица завершена?
    virtual int GoNext(void);// переход к следующей записи
    //(=1 после применения для последней записи таблицы)
};

#endif