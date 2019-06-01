#ifndef __LISTHASH_H
#define __LISTHASH_H

#include "datlist.h"
#include "hashtab.h"

#define TabMaxSize 25

class  TListHash : public THashTable {
protected:
    PTDatList *pList; // ������ ��� ������� ���������� �� ������ ������� 
    int TabSize;      // ������ ������� ����������
    int CurrList;     // ������, � ������� ���������� �����
public:
    TListHash(int Size = TabMaxSize); // �����������
    ~TListHash();
    // �������������� ������
    virtual int IsFull() const; // ���������?
    // ������
    virtual TKey GetKey(void) const;
    virtual PTDatValue GetValuePtr(void) const;
    // �������� ������
    virtual PTDatValue FindRecord(TKey k); // ����� ������
    virtual void InsRecord(TKey k, PTDatValue pVal); // ��������
    virtual void DelRecord(TKey k);        // ������� ������
    // ���������
    virtual int Reset(void);   // ���������� �� ������ ������
    virtual int IsTabEnded(void) const; // ������� ���������?
    virtual int GoNext(void); // ������� � ��������� ������
    //(=1 ����� ���������� ��� ��������� ������ �������)
};

#endif
