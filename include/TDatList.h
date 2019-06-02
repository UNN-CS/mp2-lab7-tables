#ifndef __DATLIST_H
#define __DATLIST_H
#include "TDatLink.h"
#include "tdatacom.h"

#define ListOK 0 // no mistakes
#define ListEmpty -101 // list is empty
#define ListNoMem -102// no memory
#define ListNoPos -103// mistake position  pCurrLink

class TDatList : public TDataCom
{
protected:
    PTDatLink pFirst;
    PTDatLink pLast;// последний элемент
    PTDatLink pCurrLink;
    PTDatLink pPrevLink;
    PTDatLink pStop; // конец списка
    int CurrPos;
    int ListLen;
protected:
    PTDatLink GetLink(PTDatValue pVal = nullptr, PTDatLink pLink = nullptr);
    void DelLink(PTDatLink pLink);
public:
    TDatList();
    ~TDatList() { DelList(); }
    // доступ 
    PTDatValue GetDatValue() const;
    // значение 
    virtual int IsEmpty() const { return pFirst == pStop; } // список пуст ? 
    int GetListLength() const { return ListLen; } // к-во звеньев 
                                                  // навигация 
    int SetCurrentPos(int pos); // установить текущее звено 
    int GetCurrentPos(void) const;// получить номер тек. звена 
    virtual int Reset(void); // установить на начало списка 
    virtual int IsListEnded(void) const; // список завершен ? 
    int GoNext(void); // сдвиг вправо текущего звена // (=1 после применения GoNext для последнего звена списка) // вставка звеньев 
    virtual void InsFirst(PTDatValue pVal = nullptr); // перед первым 
    virtual void InsLast(PTDatValue pVal = nullptr); // вставить последним 
    virtual void InsCurrent(PTDatValue pVal = nullptr); // перед текущим 
                                                        // удаление звеньев 
    virtual void DelFirst(void); // удалить первое звено 
    virtual void DelCurrent(void); // удалить текущее звено 
    virtual void DelList(void); // удалить весь список

};
typedef TDatList *PTDatList;
#endif