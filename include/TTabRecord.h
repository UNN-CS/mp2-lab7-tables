// класс объектов-значений для записей таблицы
#ifndef TTAB_RECORD_H
#define TTAB_RECORD_H
#include <string>
#include "TDatValue.h"

typedef std::string TKey;

class TTabRecord : public TDatValue {
protected:
    TKey Key; //ключ записи
    PTDatValue pValue; //указатель на значение
public:  
    TTabRecord(TKey k = "", PTDatValue pVal = nullptr) { 
        Key = k; pValue = pVal;
    }
    void SetKey(TKey k) { Key = k; }
    TKey GetKey() { return Key; } 
    void SetValuePtr(PTDatValue p) { pValue = p; }
    PTDatValue GetValuePTR() { return pValue; } 
    virtual TDatValue * GetCopy();  //изготовить копию
    TTabRecord & operator = (TTabRecord &tr) { 
        Key = tr.Key; pValue = tr.pValue;
        return *this;
    }
    virtual int operator == (const TTabRecord &tr) { 
        return Key == tr.Key;
    }
    virtual int operator < (const TTabRecord &tr) {  
        return Key < tr.Key;
    }
    virtual int operator > (const TTabRecord &tr) {  
        return Key > tr.Key;
    }

   
    friend class TArrayTable;
    friend class TScanTable;
    friend class TSortTable;
    friend class TTreeNode;
    friend class TTreeTable;
    friend class TArrayHash;
    friend class TListHash;
};
typedef TTabRecord *PTTabRecord;
#endif //TTAB_RECORD_H