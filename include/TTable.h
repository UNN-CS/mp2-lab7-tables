#ifndef __TTABLE_H
#define __TTABLE_H
#include <iostream>
#include "TTabRecord.h"
#include "tdatacom.h"
using namespace std;

#define TabOK 0 // ������ ���
#define TabEmpty -101 //������� �����
#define TabFull -102 // ������� �����
#define TabNoRec -103 // ��� ������
#define TabNoMem -104 // ��� ������
#define TabRecDbl -105 // ������������ ������

class TTable : public TDataCom
{
protected:
	int DataCount; // ���-�� ������� � �������
	int Efficiency; // ���������� ������������� ���������� ��������
public :
	TTable() { DataCount = 0; Efficiency = 0; }
	virtual ~TTable() {};
	//�������������� ������
	int GetDataCount() const { return DataCount; } //�������� ���-�� �������
	int GetEfficiency() const { return Efficiency; } //�������� �������������
	int IsEmpty() const { return DataCount == 0; }
	virtual int IsFull() const = 0;
	// �������� ������
	virtual PTDatValue FindRecord(TKey k) = 0; // ����� ������ �� �����
	virtual void InsRecord(TKey,PTDatValue) = 0; // �������� ������
	virtual void DelRecord(TKey k) = 0;// ������� ������ �� �����
	// ���������
	virtual int Reset() = 0; // ���������� �� ������ ������
	virtual int IsTabEnded() const = 0; //������� ���������?
	virtual int GoNext() = 0;// ������� � ��������� ������
	// ������
	virtual TKey GetKey() const = 0;
	virtual PTDatValue GetValuePtr() const = 0;
	// ������ �������
	friend ostream& operator<<(ostream& ost, TTable& t)
	{
		cout << "Table is : " << endl;
		for (t.Reset(); !t.IsTabEnded(); t.GoNext())
		{
			ost << " Key : " << t.GetKey();
			if (t.GetValuePtr() != nullptr) {
				ost << " Val : "; 
				(t.GetValuePtr())->Print();
			}
			ost<< endl;
		}
		return ost;
	}
};
#endif // !__TTABLE_H
