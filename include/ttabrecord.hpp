#pragma once

#include <string>
#include "tdatvalue.hpp"

typedef std::string TKey; // key type

class TTabRecord : public TDatValue
{
protected:
    TKey Key;          // record key
    PTDatValue pValue; // pointer to the record value
public:
    TTabRecord(TKey k = "", PTDatValue pVal = nullptr) : Key(k), pValue(pVal){};
    // setters / getters
    void SetKey(TKey k);
    TKey GetKey();

    void SetValuePtr(PTDatValue p);
    PTDatValue GetValuePTR();

    virtual TDatValue *GetCopy();
    // comparison methods
    TTabRecord &operator=(TTabRecord &tr);

    virtual bool operator==(const TTabRecord &tr);
    virtual bool operator<(const TTabRecord &tr);
    virtual bool operator>(const TTabRecord &tr);
    // friend classes
    friend class TArrayTable;
    friend class TScanTable;
    friend class TSortTable;
    friend class TTreeNode;
    friend class TTreeTable;
    friend class TArrayHash;
    friend class TListHash;
};

typedef TTabRecord *PTTabRecord;
