#ifndef TREETABLE_H_
#define TREETABLE_H_
#include <stack>
#include "table.h"
#include "treenode.h"

class TTreeTable: public TTable {
 protected:
    PTTreeNode pRoot; // ��������� �� ������ ������
    PTTreeNode *ppRef;// ����� ��������� �� �������-���������� � FindRecord
    PTTreeNode pCurrent;// ��������� �� ������� �������
    int CurrPos;        // ����� ������� �������
    std::stack <PTTreeNode> St;// ���� ��� ���������
    void DeleteTreeTab (PTTreeNode pNode); // ��������
 public:
    TTreeTable(): TTable() {
        CurrPos = 0;
        pRoot = pCurrent = nullptr;
        ppRef = nullptr;
    }
    ~TTreeTable() {DeleteTreeTab(pRoot);} // ����������
    // �������������� ������
    virtual int IsFull() const ; //���������?
    //�������� ������
    virtual PTDatValue FindRecord(TKey k); // ����� ������
    virtual void InsRecord(TKey k, PTDatValue pVal); // ��������
    virtual void DelRecord(TKey k);       // ������� ������
    void Print(PTTreeNode pNode, int depth = 0);
    void Print() {Print(pRoot);}
    // ���������
    virtual TKey GetKey() const;
    virtual PTDatValue GetValuePtr() const;
    virtual int Reset();  // ���������� �� ������ ������
    virtual int IsTabEnded() const; // ������� ���������?
    virtual int GoNext() ;// ������� � ��������� ������
    //(=1 ����� ���������� ��� ��������� ������ �������)
};

#endif // TREETABLE_H_
