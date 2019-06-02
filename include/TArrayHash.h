#ifndef _ARRAYHASH_H
#define _ARRAYHASH_H

#include "THashTable.h"


#define TabMaxSize 25
#define TabHashStep 5
class  TArrayHash : public THashTable {
protected:
    PTTabRecord * pRecs;
    int TabSize;
    int HashStep;
    int FreePos;
    int CurrPos;
    PTTabRecord pMark;
    int GetNextPos(int pos) { return (pos + HashStep) % TabSize; };
public:
    TArrayHash(int Size = TabMaxSize, int Step = TabHashStep);
    ~TArrayHash();

    virtual int IsFull() const { return DataCount >= TabSize; }

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