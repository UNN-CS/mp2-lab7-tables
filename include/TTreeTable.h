#ifndef __TREETABLE_H__
#define __TREETABLE_H__

#include "TTreeNode.h"
#include "TTable.h"
#include <stack>

class  TTreeTable : public TTable {
protected:
	PTTreeNode pRoot; // указатель на корень дерева
	PTTreeNode *ppRef;// адрес указателя на вершину-результата в FindRecord
	PTTreeNode pCurrent;// указатель на текущую вершину
	PTTreeNode InsNode(PTTreeNode root,TKey k, PTDatValue pVal = nullptr);
	PTDatValue SearchNode(PTTreeNode root, TKey k);
	PTTreeNode DeleteNode(PTTreeNode root, TKey k);
	int CurrPos;        // номер текущей вершины
	std::stack < PTTreeNode> St;// стек для итератора
	void DeleteTreeTab(PTTreeNode pNode); // удаление
public:
	TTreeTable();
	~TTreeTable();// деструктор
	// информационные методы
	virtual int IsFull() const; //заполнена?
	//основные методы
	virtual PTDatValue FindRecord(TKey k); // найти запись
	virtual void InsRecord(TKey k, PTDatValue pVal = nullptr); // вставить
	virtual void DelRecord(TKey k);       // удалить запись
	// навигация
	virtual TKey GetKey() const;
	virtual PTDatValue GetValuePTR() const;
	virtual int Reset();  // установить на первую запись
	virtual int IsTabEnded() const; // таблица завершена?
	virtual int GoNext();// переход к следующей записи
	//(=1 после применения для последней записи таблицы)
};

#endif
