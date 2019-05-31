#include "TDatList.h"
#include <iostream>
using namespace std;
TDatList::TDatList()
{
	pFirst = pLast = pStop = nullptr;
	ListLen = 0;
	Reset();
}

PTDatLink TDatList::GetLink(PTDatValue pVal, PTDatLink pLink)
{
	PTDatLink temp = new TDatLink(pVal, pLink);
	 return temp;
}
void TDatList::DellLink(PTDatLink pLink)
{
	if (pLink != nullptr)
	{
		if (pLink->pValue!=nullptr)
			delete pLink->pValue;
		delete pLink;
	}
}

PTDatValue TDatList::GetDatValue(TLinkPos t) const
{
	PTDatLink tmp;
	switch (t)
	{
	case FIRST: tmp = pFirst; break;
	case CURRENT: tmp = pCurrent; break;
	case LAST: tmp = pLast; break;
	}
	//cout << CurPos<<" ";
	return (tmp==nullptr)?0:tmp->pValue;
}
int TDatList::GoNext() // ����� ������ �������� �����
{
	if (pCurrent == pStop) return 1;
	else
	{
		pPrev = pCurrent;
		pCurrent = pCurrent->GetNextDatLink();
		CurPos++;
		return 0;
	}
}
int TDatList::SetCurrentPos(int pos) //���������� ������� �����
{
	Reset();
	for (int i = 0; i < pos; i++)
	{
		GoNext();
	}
	return 0;
}
int TDatList::GetCurrentPos() // ��������� ����� �������� �����
{
	return CurPos;
}

int TDatList::Reset()
{
	pPrev = pStop;
	if (IsEmpty()) { pCurrent = pStop; CurPos = -1; return 1; }
	else { pCurrent = pFirst; CurPos = 0; return 0; }
}


// ������ ������� �������
void TDatList::InsFirst(PTDatValue pVal)
{
	PTDatLink temp = GetLink(pVal, pFirst);
	if (temp == nullptr) throw - 1;
	else
	{
		pFirst = temp;
		ListLen++;
		if (ListLen == 1)
		{
			pLast = temp;
			Reset();
		}
		else if (CurPos == 0) pCurrent = temp;
		else CurPos++;
	}
}

void TDatList::InsLast(PTDatValue pVal)
{
	PTDatLink temp = GetLink(pVal, pStop);
	if (temp == nullptr) throw - 1;
	else
	{
		if (pLast != nullptr) pLast->SetNextLink(temp);
		pLast = temp;
		ListLen++;
		// �������� ������� ������ ����� �������� 
		if (ListLen == 1) 
		{
			pFirst = temp;
			Reset();
		}
		// ������������� ������� ������� - ������� ��� pCurrLink �� ������ ������ 
		if (IsListEnded()) pCurrent = temp;
	}
}

void TDatList::InsCurrent(PTDatValue pVal)
{
	if (IsEmpty() || (pCurrent == pFirst)) InsFirst(pVal);
	else if (IsListEnded()) InsLast(pVal);
	else if (pPrev == pStop) throw - 1;
	else
	{
		PTDatLink temp = GetLink(pVal, pCurrent);
		if (temp == nullptr) throw - 1;
		else
		{
			pCurrent = temp;
			pPrev->SetNextLink(temp);
			ListLen++;
		}
	}
}

//������ �������� �������
void TDatList::DelFirst() //�������� ������� �����
{
	if (IsEmpty()) throw - 1;
	else
	{
		PTDatLink temp = pFirst;
		pFirst = pFirst->GetNextDatLink();
		DellLink(temp);
		ListLen--;
		if (IsEmpty())
		{
			pLast = pStop;
			Reset();
		}
		// ������������� ������� �������
		else if (CurPos == 0)
			pCurrent = pFirst;
		else if (CurPos == 1) pPrev = pStop;
		if (CurPos > 0) CurPos--;
	}
}

void TDatList::DelCurrent() //�������� �������� �����
{
	if (pCurrent == pStop) throw - 1;
	else if (pCurrent == pFirst) DelFirst();
	else
	{
		PTDatLink temp = pCurrent;
		pCurrent = pCurrent->GetNextDatLink();
		pPrev->SetNextLink(pCurrent);
		DellLink(temp);
		ListLen--;
		// ��������� �������� �������� ���������� �����
		if (pCurrent == pStop) { pLast = pPrev; pCurrent = pStop; }
	}
}

void TDatList::DelList()// ������� ���� ����
{
	while (!IsEmpty()) DelFirst();
	pFirst = pLast = pPrev = pCurrent = pStop;
	CurPos = -1;
}
