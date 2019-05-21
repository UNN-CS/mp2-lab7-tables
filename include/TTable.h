#include "TDataCom.h"
#include "TTabRecord.h"

class TTable : public TDataCom
{
protected:
    int DataCount;
    int Efficiency;

public:
    TTable()
    {
        DataCount = 0;
        Efficiency = 0;
    }
    virtual ~TTable(){};
    int GetDataCOunt() const { return DataCount; }
    int GetEfficiency() const { return Efficiency; }
    int isEmpty() const { return DataCount == 0; }
    virtual int isFull() const = 0;
    virtual TKey GetKey(void) const = 0;
    virtual PTDatValue GetValuePTR(void) const = 0;
    virtual PTDatValue FindRecord(TKey k) = 0;
    virtual void InsRecord(TKey, PTDatValue pval) = 0;
    virtual int Reset(void) = 0;
    virtual int IsTabEnded(void) = 0;
    virtual int GoNext(void) = 0;
};