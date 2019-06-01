#pragma once

#include "THashTable.h"
#include "TDatList.h"

#define TabMaxSize 25

class TListHash : public THashTable
{
protected:
  PTDatList *pList;
  int TabSize;
  int CurrList;

public:
  TListHash(int size = TabMaxSize);
  ~TListHash();
  // info methods
  virtual int IsFull() const;
  // ������
  virtual TKey GetKey(void) const;
  virtual PTDatValue GetValuePTR(void) const;
  // access methods
  virtual PTDatValue FindRecord(TKey k);
  virtual void InsRecord(TKey k, PTDatValue pVal);
  virtual void DelRecord(TKey k);
  //  navigation
  virtual int Reset();
  virtual int IsTabEnded() const;
  virtual int GoNext();
};

