#ifndef _LISTHASH_H
#define _LISTHASH_H

#include "THashTable.h"
#include "TDatList.h"
#define TabMaxSize 25
class  TListHash : public THashTable {
protected:
    PTDatList * pList; 
    int TabSize;     
    int CurrList;     
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

#endif 