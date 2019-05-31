#ifndef __TDATLIST_H
#define __TDATLIST_H

#include "TDatLink.h"

enum TLinkPos
{
	FIRST,
	CURRENT,
	LAST
};

class TDatList
{
protected:
	PTDatLink pFirst;//��������� �� ������ ����� � ������ 
	PTDatLink pLast;// ��������� �� ��������� ����� � ������
	PTDatLink pCurrent;// ��������� �� ������� ����� � ������
	PTDatLink pPrev;//��������� �� ����� ����� ������� � ������
	PTDatLink pStop;//�������� ���������, ����������� ����� ������
	int CurPos;// ����� �������� ����� (������� � 0)
	int ListLen;//����� �������
protected:
	PTDatLink GetLink(PTDatValue pDat = nullptr, PTDatLink pLink = nullptr);
	void DellLink(PTDatLink pLink);// �������� �����
public:
	TDatList();
	~TDatList() { DelList(); }
	//������
	PTDatValue GetDatValue(TLinkPos t = CURRENT) const;// �������� �������� � ����� �� �������
	virtual int IsEmpty() const { return pFirst == pStop; }//��������� ���� �� ������
	int GetListLength() { return ListLen; }//���-�� ������� � ������
	//���������
	int GoNext();//����� ������ �������� �����
	int GetCurrentPos();//�������� ����� �������� �����
	int SetCurrentPos(int pos);// ���������� �� ������� �������
	virtual int Reset();//���������� �� ������ ������
	virtual int IsListEnded() const { return pCurrent == pStop; }// ������ ��������?
	//������� ������� 
	virtual void InsFirst(PTDatValue pVal = nullptr);// �������� ����� ������
	virtual void InsLast(PTDatValue pVal = nullptr);//�������� ���������
	virtual void InsCurrent(PTDatValue pVal = nullptr);// �������� ����� �������
	//�������� �������
	virtual void DelFirst();//������� ������ �����
	virtual void DelCurrent();//������� ������� �����
	virtual void DelList();//������� ���� ������
};
typedef TDatList * PTDatList;
#endif // !__TDATLIST_H
