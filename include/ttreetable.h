#ifndef __T_TREE_TABLE_H__
#define __T_TREE_TABLE_H__

#include "ttable.h"
#include "ttreenode.h"
#include <stack>

class  TTreeTable: public TTable {
  protected:
    PTTreeNode pRoot; // указатель на корень дерева
    PTTreeNode *ppRef;// адрес указателя на вершину-результата в FindRecord
    PTTreeNode pCurrent;// указатель на текущую вершину
    int CurrPos;        // номер текущей вершины
    std::stack < PTTreeNode> St;// стек для итератора
    void DeleteTreeTab (PTTreeNode pNode); // удаление
  public:
    TTreeTable(): TTable() {CurrPos=0; pRoot=pCurrent=nullptr; ppRef=nullptr;}
    ~TTreeTable(){DeleteTreeTab (pRoot);} // деструктор
    // информационные методы
    virtual int IsFull () const ; //заполнена?
    //основные методы
    virtual PTDatValue FindRecord (TKey k); // найти запись
    virtual void InsRecord (TKey k, PTDatValue pVal ); // вставить
    virtual void DelRecord (TKey k);       // удалить запись
    // навигация
    virtual TKey GetKey () const;
    virtual PTDatValue GetValuePtr () const;
    virtual int Reset ();  // установить на первую запись
    virtual int IsTabEnded () const; // таблица завершена?
    virtual int GoNext () ;// переход к следующей записи
    //(=1 после применения для последней записи таблицы)
};

#endif // __T_TREE_TABLE_H__
