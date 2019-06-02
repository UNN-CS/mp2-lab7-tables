#ifndef TABLE_H
#define TABLE_H
#include "TTabRecord.h"

class  TTable {
protected:
    int DataCount;  
    int Efficiency; 
public:
    TTable() { DataCount = 0; Efficiency = 0; } 
    virtual ~TTable() {}; 

    int GetDataCount() const { return DataCount; }    
    int GetEfficiency() const { return Efficiency; } 
    void ResetEfficiency() { Efficiency = 0; }
    int IsEmpty() const { return DataCount == 0; }  
    virtual int IsFull() const = 0;                 

    virtual TKey GetKey() const = 0;
    virtual PTDatValue GetValuePTR() const = 0;

    virtual PTDatValue FindRecord(TKey k) = 0; 
    virtual void InsRecord(TKey k, PTDatValue pVal) = 0; 
    virtual void DelRecord(TKey k) = 0;        
                                              
    virtual int Reset() = 0; 
    virtual int IsTabEnded() const = 0; 
    virtual int GoNext() = 0; 
};
#endif