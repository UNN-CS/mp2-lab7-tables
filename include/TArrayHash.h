#pragma once

#include "THashTable.h"

#define TabMaxSize 25
#define TabHashStep 5
class TArrayHash : public THashTable
{
protected:
  PTTabRecord *pRecs;
  int TabSize;
  int HashStep;
  int FreePos;
  int CurrPos;
  PTTabRecord pMark;
  int GetNextPos(int pos) { return (pos + HashStep) % TabSize; };
public:
  TArrayHash(int size = TabMaxSize, int Step = TabHashStep);
  ~TArrayHash();
  virtual int IsFull() const;
  ///basic methods
  virtual TKey GetKey(void) const;
  virtual PTDatValue GetValuePTR(void) const;
  //navigation
  virtual PTDatValue FindRecord(TKey k);           
  virtual void InsRecord(TKey k, PTDatValue pVal);
  virtual void DelRecord(TKey k);                 
  //Access
  virtual int Reset(void);            
  virtual int IsTabEnded(void) const;
  virtual int GoNext(void);
};
