#ifndef __TABRECORD_H__
#define __TABRECORD_H__

#include <string>

#include "tdatvalue.h"

typedef std::string TKey;

class TTabRecord: public TDatValue {
protected:
    TKey Key;
    PTDatValue pValue;
public:
    TTabRecord(TKey k = "", PTDatValue pVal = nullptr) : Key(k), pValue(pVal) {};
    void SetKey(TKey k);
    TKey GetKey();
    void SetValuePtr(PTDatValue p);
    PTDatValue GetValuePTR();
    virtual TDatValue* GetCopy();
    TTabRecord& operator=(TTabRecord& tr);
    virtual bool operator==(const TTabRecord& tr);
    virtual bool operator<(const TTabRecord& tr);
    virtual bool operator>(const TTabRecord& tr);
    friend class TArrayTable;
    friend class TScanTable;
    friend class TSortTable;
    friend class TTreeNode;
    friend class TTreeTable;
    friend class TArrayHash;
    friend class TListHash;
};

typedef TTabRecord* PTTabRecord;

#endif
