#ifndef __T_TREE_TABLE__
#define __T_TREE_TABLE__

//#include "TTable.h"
//#include "TTreeNode.h"
//#include <stack>

//class  TTreeTable: public TTable {
//  protected: 
//    PTTreeNode pRoot; // указатель на корень дерева
//    PTTreeNode *ppRef;// адрес указателя на вершину-результата в FindRecord
//    PTTreeNode pCurrent;// указатель на текущую вершину
//    int CurrPos;        // номер текущей вершины
//    std::stack<PTTreeNode> St;// стек для итератора
//    void DeleteTreeTab (PTTreeNode pNode); // удаление
//  public:
//    TTreeTable(): TTable(){CurrPos=0; pRoot=pCurrent=NULL; ppRef=NULL;}   
//    ~TTreeTable(){DeleteTreeTab (pRoot);} // деструктор
//    // информационные методы
//    virtual int IsFull ( ) const ; //заполнена?
//    //основные методы
//    virtual PTDatValue FindRecord (TKey k); // найти запись
//    virtual void InsRecord (TKey k, PTDatValue pVal ); // вставить
//    virtual void DelRecord (TKey k);       // удалить запись
//    // навигация
//    virtual TKey GetKey (void) const;
//    virtual PTDatValue GetValuePTR (void) const;
//    virtual int Reset (void);  // установить на первую запись
//    virtual int IsTabEnded (void) const; // таблица завершена?
//    virtual int GoNext (void) ;// переход к следующей записи
//    //(=1 после применения для последней записи таблицы)
//};

#include <stack>
#include "TTable.h"
#include "TTreeNode.h"

class TTreeTable : public TTable {
protected:
	PTTreeNode pRoot; // óêàçàòåëü íà êîðåíü äåðåâà
	PTTreeNode *ppRef;// àäðåñ óêàçàòåëÿ íà âåðøèíó-ðåçóëüòàòà â FindRecord
	PTTreeNode pCurrent;// óêàçàòåëü íà òåêóùóþ âåðøèíó
	int CurrPos;        // íîìåð òåêóùåé âåðøèíû
	std::stack <PTTreeNode> St;// ñòåê äëÿ èòåðàòîðà
	void DeleteTreeTab(PTTreeNode pNode); // óäàëåíèå
public:
	TTreeTable() : TTable() {
		CurrPos = 0;
		pRoot = pCurrent = nullptr;
		ppRef = nullptr;
	}
	~TTreeTable() { DeleteTreeTab(pRoot); } // äåñòðóêòîð
	// èíôîðìàöèîííûå ìåòîäû
	virtual int IsFull() const; //çàïîëíåíà?
	//îñíîâíûå ìåòîäû
	virtual PTDatValue FindRecord(TKey k); // íàéòè çàïèñü
	virtual void InsRecord(TKey k, PTDatValue pVal); // âñòàâèòü
	virtual void DelRecord(TKey k);       // óäàëèòü çàïèñü
	void Print(PTTreeNode pNode, int depth = 0);
	void Print() { Print(pRoot); }
	// íàâèãàöèÿ
	virtual TKey GetKey() const;
	virtual PTDatValue GetValuePTR() const;
	virtual int Reset();  // óñòàíîâèòü íà ïåðâóþ çàïèñü
	virtual int IsTabEnded() const; // òàáëèöà çàâåðøåíà?
	virtual int GoNext();// ïåðåõîä ê ñëåäóþùåé çàïèñè
	//(=1 ïîñëå ïðèìåíåíèÿ äëÿ ïîñëåäíåé çàïèñè òàáëèöû)
};

#endif //__T_TREE_TABLE__