#ifndef LISTHASH_H_
#define LISTHASH_H_
#include "hashtable.h"
#include "datlist.h"

class TListHash : public THashTable {
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
    virtual TKey GetKey() const;
    virtual PTDatValue GetValuePtr() const;
    // �������� ������
    virtual PTDatValue FindRecord(TKey k); // ����� ������
    virtual void InsRecord(TKey k, PTDatValue pVal); // ��������
    virtual void DelRecord(TKey k);        // ������� ������
    // ���������
    virtual int Reset();   // ���������� �� ������ ������
    virtual int IsTabEnded() const; // ������� ���������?
    virtual int GoNext(); // ������� � ��������� ������
    //(=1 ����� ���������� ��� ��������� ������ �������)
};

#endif // LISTHASH_H_
