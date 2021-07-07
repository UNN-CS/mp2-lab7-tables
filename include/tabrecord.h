#pragma once

#include "defines.h"

#include "datvalue.h"

class TTabRecord : public TDatValue {
  public:
    TTabRecord(TKey k="", PTDatValue pVal = nullptr);

    virtual PTDatValue GetCopy() const override;

    TTabRecord & operator=(const TTabRecord &tr);
    virtual bool operator==(const TTabRecord &tr) const;
    virtual bool operator<(const TTabRecord &tr) const;
    virtual bool operator>(const TTabRecord &tr) const;
    
    void SetKey(TKey k);
    TKey GetKey(void);
    
    void SetValuePtr(PTDatValue p);
    PTDatValue GetValuePtr(void);

  protected:
    PTDatValue pValue;
    TKey key;

    friend class TArrayTable;
    friend class TScanTable;
    friend class TSortTable;
    friend class TTreeTable;
    friend class TArrayHash;
    friend class TListHash;
};
