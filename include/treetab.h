#ifndef __treetab_h
#define __treetab_h

#include <stack>
#include <TTable.h>
#include "treenode.h"

class TreeTable : public TTable {
 protected:
	PTreeNode pRoot; // указатель на корень дерева
	PTreeNode* ppRef; // адрес указателя на вершину-результата в FindRecord
	PTreeNode pCurrent; // указатель на текущую вершину
	int CurrPos; // номер текущей вершины
	stack<PTreeNode> St; // стек для итератора
	void PrintTreeTab(ostream & os, PTreeNode); // Печать дерева
	void DrawTreeTab(PTreeNode pNode, int level); // Печать с ярусами
	void DeleteTreeTab(PTreeNode  pNode); // удаление
 public:
	TreeTable() :TTable() { CurrPos = 0; pRoot = pCurrent = NULL; ppRef = NULL; }
	~TreeTable() { DeleteTreeTab(pRoot); }
	// информационные методы
	virtual int IsFull() const;  // заполнена
	// основные методы
	virtual PTDatValue FindRecord(TKey k); // найти запись по ключу
	virtual void InsRecord(TKey, PTDatValue); // вставить запись
	virtual void DelRecord(TKey k);// удалить запись по ключу
	// навигация
	virtual TKey GetKey() const; // ключ текущей записи
	virtual PTDatValue GetValuePtr() const; // указатель на значение
	virtual int Reset(); // установить на превую запись
	virtual int IsTabEnded() const; // таблица завершена?
	virtual int GoNext(); // переход к следующей записи
	// печать таблицы
	void Draw(); // печать дерева (рисурок слева направо)
	void Show(); // печать дерева (рисунок сверху вниз)
	friend ostream& operator<<(ostream &os, TreeTable& tab);
 protected:
	string tk[20];
	int tl[20], pos;
	void PutValues(PTreeNode pNode, int level); // служебный метод для Show()
};
#endif // ! __treetab_h
