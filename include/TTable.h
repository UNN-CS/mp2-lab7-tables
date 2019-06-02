// Таблицы - базовый класс
#ifndef TTABLE_H
#define TTABLE_H
#include "TTabRecord.h"

class  TTable {
protected:
    int DataCount;  // количество записей в таблице
    int Efficiency; // показатель эффективности выполнения операции
public:
    TTable() { DataCount = 0; Efficiency = 0; } 
    virtual ~TTable() {}; 
	//информационные методы
    int GetDataCount() const { return DataCount; }    
    int GetEfficiency() const { return Efficiency; } 
    void ResetEfficiency() { Efficiency = 0; }
    int IsEmpty() const { return DataCount == 0; }  
    virtual int IsFull() const = 0;                 
	//основные методы
    virtual PTDatValue FindRecord(TKey k) = 0; 
    virtual void InsRecord(TKey k, PTDatValue pVal) = 0; 
    virtual void DelRecord(TKey k) = 0;        
	//доступ
	virtual TKey GetKey() const = 0;
    virtual PTDatValue GetValuePTR() const = 0;
	//навигация
    virtual int Reset() = 0; //установить на первую запись
    virtual int IsTabEnded() const = 0; 
    virtual int GoNext() = 0; 
};
#endif //TTABLE_H