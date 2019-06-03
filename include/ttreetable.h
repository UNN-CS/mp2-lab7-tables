// Таблицы со структурой хранения в виде деревьев поиска

#pragma once

#include <stack>

#include "ttable.h"
#include "ttreenode.h"

class  TTreeTable: public TTable {
  protected: 
    PTTreeNode pRoot;                                                    // указатель на корень дерева
    PTTreeNode *ppRef;                                                   // адрес указателя на вершину-результата в FindRecord
    PTTreeNode pCurrent;                                                 // указатель на текущую вершину
    int currPos;                                                         // номер текущей вершины
    std::stack<PTTreeNode> st;                                           // стек для итератора
    void DeleteTreeTab (PTTreeNode pNode);                               // удаление

  public:
    TTreeTable(): TTable() { currPos = 0; pRoot = pCurrent = NULL;
                             ppRef = NULL; }   
    ~TTreeTable() { DeleteTreeTab (pRoot); }                             // деструктор

    // информационные методы
    virtual bool IsFull () const;                                         // заполнена?

    // основные методы
    virtual PTDatValue FindRecord (TKey k);                              // найти запись
    virtual void InsRecord (TKey k, PTDatValue pVal );                   // вставить
    virtual void DelRecord (TKey k);                                     // удалить запись

    // навигация
    virtual TKey GetKey () const;
    virtual PTDatValue GetValuePTR () const;
    virtual int Reset ();                                                // установить на первую запись
    virtual int IsTabEnded () const;                                     // таблица завершена?
    virtual int GoNext () ;                                           // переход к следующей записи
    //(=1 после применения для последней записи таблицы)

    void Print(PTTreeNode pNode, int depth);                             // печать
};
