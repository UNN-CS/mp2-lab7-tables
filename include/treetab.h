#ifndef __treetab_h
#define __treetab_h

#include <stack>
#include <TTable.h>
#include "treenode.h"

class TreeTable : public TTable {
 protected:
	PTreeNode pRoot; // ��������� �� ������ ������
	PTreeNode* ppRef; // ����� ��������� �� �������-���������� � FindRecord
	PTreeNode pCurrent; // ��������� �� ������� �������
	int CurrPos; // ����� ������� �������
	stack<PTreeNode> St; // ���� ��� ���������
	void PrintTreeTab(ostream & os, PTreeNode); // ������ ������
	void DrawTreeTab(PTreeNode pNode, int level); // ������ � �������
	void DeleteTreeTab(PTreeNode  pNode); // ��������
 public:
	TreeTable() :TTable() { CurrPos = 0; pRoot = pCurrent = NULL; ppRef = NULL; }
	~TreeTable() { DeleteTreeTab(pRoot); }
	// �������������� ������
	virtual int IsFull() const;  // ���������
	// �������� ������
	virtual PTDatValue FindRecord(TKey k); // ����� ������ �� �����
	virtual void InsRecord(TKey, PTDatValue); // �������� ������
	virtual void DelRecord(TKey k);// ������� ������ �� �����
	// ���������
	virtual TKey GetKey() const; // ���� ������� ������
	virtual PTDatValue GetValuePtr() const; // ��������� �� ��������
	virtual int Reset(); // ���������� �� ������ ������
	virtual int IsTabEnded() const; // ������� ���������?
	virtual int GoNext(); // ������� � ��������� ������
	// ������ �������
	void Draw(); // ������ ������ (������� ����� �������)
	void Show(); // ������ ������ (������� ������ ����)
	friend ostream& operator<<(ostream &os, TreeTable& tab);
 protected:
	string tk[20];
	int tl[20], pos;
	void PutValues(PTreeNode pNode, int level); // ��������� ����� ��� Show()
};
#endif // ! __treetab_h
