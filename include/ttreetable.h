#ifndef __T_TREE_TABLE_H__
#define __T_TREE_TABLE_H__

#include "ttable.h"
#include "ttreenode.h"
#include <stack>

class  TTreeTable: public TTable {
  protected:
    PTTreeNode pRoot; // ��������� �� ������ ������
    PTTreeNode *ppRef;// ����� ��������� �� �������-���������� � FindRecord
    PTTreeNode pCurrent;// ��������� �� ������� �������
    int CurrPos;        // ����� ������� �������
    std::stack < PTTreeNode> St;// ���� ��� ���������
    void DeleteTreeTab (PTTreeNode pNode); // ��������
  public:
    TTreeTable(): TTable() {CurrPos=0; pRoot=pCurrent=nullptr; ppRef=nullptr;}
    ~TTreeTable(){DeleteTreeTab (pRoot);} // ����������
    // �������������� ������
    virtual int IsFull () const ; //���������?
    //�������� ������
    virtual PTDatValue FindRecord (TKey k); // ����� ������
    virtual void InsRecord (TKey k, PTDatValue pVal ); // ��������
    virtual void DelRecord (TKey k);       // ������� ������
    // ���������
    virtual TKey GetKey () const;
    virtual PTDatValue GetValuePtr () const;
    virtual int Reset ();  // ���������� �� ������ ������
    virtual int IsTabEnded () const; // ������� ���������?
    virtual int GoNext () ;// ������� � ��������� ������
    //(=1 ����� ���������� ��� ��������� ������ �������)
};

#endif // __T_TREE_TABLE_H__
