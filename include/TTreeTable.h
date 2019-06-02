#ifndef __TREETABLE_H__
#define __TREETABLE_H__

#include "TTreeNode.h"
#include "TTable.h"
#include <stack>

class  TTreeTable : public TTable {
protected:
	PTTreeNode pRoot; // ��������� �� ������ ������
	PTTreeNode *ppRef;// ����� ��������� �� �������-���������� � FindRecord
	PTTreeNode pCurrent;// ��������� �� ������� �������
	PTTreeNode InsNode(PTTreeNode root,TKey k, PTDatValue pVal = nullptr);
	PTDatValue SearchNode(PTTreeNode root, TKey k);
	PTTreeNode DeleteNode(PTTreeNode root, TKey k);
	int CurrPos;        // ����� ������� �������
	std::stack < PTTreeNode> St;// ���� ��� ���������
	void DeleteTreeTab(PTTreeNode pNode); // ��������
public:
	TTreeTable();
	~TTreeTable();// ����������
	// �������������� ������
	virtual int IsFull() const; //���������?
	//�������� ������
	virtual PTDatValue FindRecord(TKey k); // ����� ������
	virtual void InsRecord(TKey k, PTDatValue pVal = nullptr); // ��������
	virtual void DelRecord(TKey k);       // ������� ������
	// ���������
	virtual TKey GetKey() const;
	virtual PTDatValue GetValuePTR() const;
	virtual int Reset();  // ���������� �� ������ ������
	virtual int IsTabEnded() const; // ������� ���������?
	virtual int GoNext();// ������� � ��������� ������
	//(=1 ����� ���������� ��� ��������� ������ �������)
};

#endif
