#ifndef __DATLIST_H
#define __DATLIST_H
#include "TDatLink.h"
#include "tdatacom.h"

#define ListOK 0 // no mistakes
#define ListEmpty -101 // list is empty
#define ListNoMem -102// no memory
#define ListNoPos -103// mistake position  pCurrLink

class TDatList : public TDataCom
{
protected:
	PTDatLink pFirst;
	PTDatLink pLast;// ��������� �������
	PTDatLink pCurrLink;
	PTDatLink pPrevLink;
	PTDatLink pStop; // ����� ������
	int CurrPos;
	int ListLen;
protected:
	PTDatLink GetLink(PTDatValue pVal = nullptr, PTDatLink pLink = nullptr);
	void DelLink(PTDatLink pLink);
public:
	TDatList();
	~TDatList() { DelList(); }
	// ������ 
	PTDatValue GetDatValue() const;
	// �������� 
	virtual int IsEmpty() const { return pFirst == pStop; } // ������ ���� ? 
	int GetListLength() const { return ListLen; } // �-�� ������� 
												  // ��������� 
	int SetCurrentPos(int pos); // ���������� ������� ����� 
	int GetCurrentPos(void) const;// �������� ����� ���. ����� 
	virtual int Reset(void); // ���������� �� ������ ������ 
	virtual int IsListEnded(void) const; // ������ �������� ? 
	int GoNext(void); // ����� ������ �������� ����� // (=1 ����� ���������� GoNext ��� ���������� ����� ������) // ������� ������� 
	virtual void InsFirst(PTDatValue pVal = nullptr); // ����� ������ 
	virtual void InsLast(PTDatValue pVal = nullptr); // �������� ��������� 
	virtual void InsCurrent(PTDatValue pVal = nullptr); // ����� ������� 
														// �������� ������� 
	virtual void DelFirst(void); // ������� ������ ����� 
	virtual void DelCurrent(void); // ������� ������� ����� 
	virtual void DelList(void); // ������� ���� ������

};
typedef TDatList *PTDatList;
#endif