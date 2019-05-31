#ifndef __TDATLIST_H
#define __TDATLIST_H

#include "TDatLink.h"

enum TLinkPos
{
	FIRST,
	CURRENT,
	LAST
};

class TDatList
{
protected:
	PTDatLink pFirst;//указатель на первой звено в списке 
	PTDatLink pLast;// указатель на последнее звено в списке
	PTDatLink pCurrent;// указатель на текущее звено в списке
	PTDatLink pPrev;//указатель на звено перед текущем в списке
	PTDatLink pStop;//значение указателя, означающего конец списка
	int CurPos;// номер текущего звена (начиная с 0)
	int ListLen;//число звеньев
protected:
	PTDatLink GetLink(PTDatValue pDat = nullptr, PTDatLink pLink = nullptr);
	void DellLink(PTDatLink pLink);// удаление звена
public:
	TDatList();
	~TDatList() { DelList(); }
	//доступ
	PTDatValue GetDatValue(TLinkPos t = CURRENT) const;// значение элемента в одном из звеньев
	virtual int IsEmpty() const { return pFirst == pStop; }//проверяет пуст ли список
	int GetListLength() { return ListLen; }//кол-во звеньев в списке
	//навигация
	int GoNext();//сдвиг вправо текущего звена
	int GetCurrentPos();//получить номер текущего звена
	int SetCurrentPos(int pos);// установить на текущую позицию
	virtual int Reset();//установить на начало списка
	virtual int IsListEnded() const { return pCurrent == pStop; }// список завершен?
	//вставка звеньев 
	virtual void InsFirst(PTDatValue pVal = nullptr);// вставить перед первым
	virtual void InsLast(PTDatValue pVal = nullptr);//вставить последним
	virtual void InsCurrent(PTDatValue pVal = nullptr);// вставить перед текущим
	//удаление звеньев
	virtual void DelFirst();//удалить первое звено
	virtual void DelCurrent();//удалить текущее звено
	virtual void DelList();//удалить весь список
};
typedef TDatList * PTDatList;
#endif // !__TDATLIST_H
