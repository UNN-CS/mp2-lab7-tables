#ifndef _ARRAY_TABLE_H
#define _ARRAY_TABLE_H
#include "TTabRecord.h"
#include "TTable.h"
#define TabMaxSize 25
enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class  TArrayTable : public TTable {
protected:
    PTTabRecord * pRecs; 
    int TabSize;        
    int CurrPos;        
public:
    TArrayTable(int Size = TabMaxSize) { 
        pRecs = new PTTabRecord[Size];
        for (int i = 0; i < Size; ++i) pRecs[i] = nullptr;
        TabSize = Size; DataCount = CurrPos = 0;
    }

    ~TArrayTable() {
        for (int i = 0; i < DataCount; ++i)
            delete pRecs[i];
        delete[] pRecs;
    }

    virtual int IsFull() const { 
        return DataCount >= TabSize;
    }

    int GetTabSize() const { return TabSize; }     

    virtual TKey GetKey() const { return GetKey(CURRENT_POS); }
    virtual PTDatValue GetValuePTR() const { return GetValuePTR(CURRENT_POS); }
    virtual TKey GetKey(TDataPos mode) const;
    virtual PTDatValue GetValuePTR(TDataPos mode) const;

    
    virtual PTDatValue FindRecord(TKey k) = 0; 
    virtual void InsRecord(TKey k, PTDatValue pVal) = 0; 
    virtual void DelRecord(TKey k) = 0;        
                                             
    virtual int Reset();  
    virtual int IsTabEnded() const; 
    virtual int GoNext(); 
                          
    virtual int SetCurrentPos(int pos);
    int GetCurrentPos() const { return CurrPos; }     
    friend class TSortTable;
};

#endif 