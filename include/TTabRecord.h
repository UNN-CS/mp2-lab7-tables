#include <string>
#include <string.h>
#include "TDatValue.h"

typedef TTabRecord* PTTabRecord;
typedef std::string TKey;
class TTabRecord : public TDatValue
{
protected:
    PTDatValue pValue;

public:
    TTabRecord(TKey k = "", PTDatValue pVal = NULL);
    void SetKey(TKey k);
    TKey GetKey(void);
    void SetValuePtr(PTDatValue p);
    PTDatValue GetValuePtr(void);
    virtual TDatValue *GetCopy();
    TTabRecord &operator=(TTabRecord &tr);
    virtual int operator==(const TTabRecord &tr);
    virtual int operator<(const TTabRecord &tr);
    virtual int operator>(const TTabRecord &tr);
    friend class TArrayTable;
    friend class TScanTable;
    friend class TSortTable;
    friend class TTreeNode;
    friend class TTreeTable;
    friend class TArrayHash;
    friend class TListHash;
};
