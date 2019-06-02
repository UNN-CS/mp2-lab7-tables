// таблицы с вычислимым входом - Метод цепочек
#ifndef _TLISTHASH_H
#define _TLISTHASH_H

#include "THashTable.h"
#include "TDatList.h"

#define TabMaxSize 25

class  TListHash : public THashTable {
protected:
    PTDatList * pList; // память для массива указателей на списки записей
    int TabSize;       // р-р массива указателей
    int CurrList;      // список, в котором выполнялся поиск
public:
    TListHash(int Size = TabMaxSize); 
    ~TListHash();
   
    virtual int IsFull() const; 

    virtual TKey GetKey() const;
    virtual PTDatValue GetValuePTR() const;
   
    virtual PTDatValue FindRecord(TKey k); 
    virtual void InsRecord(TKey k, PTDatValue pVal); 
    virtual void DelRecord(TKey k);        

    virtual int Reset();
    virtual int IsTabEnded() const; 
    virtual int GoNext(); 
};

#endif //_TLISTHASH_H