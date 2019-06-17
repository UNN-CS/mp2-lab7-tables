// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tdatacom.h - Copyright (c) ������� �.�. 30.08.2000
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (21.04.2015)
//
// ��������� ����� ����������

#ifndef __DATACOM_H__
#define __DATACOM_H__

#define DataOK   0
#define DataErr -1

// TDataCom �������� ����� ������� �������
class TDataCom
{
protected:
	int RetCode; // ��� ����������

	int SetRetCode(int ret) { return RetCode = ret; }
public:
	TDataCom() : RetCode(DataOK) {}
	virtual ~TDataCom() = 0 {}
	int GetRetCode()
	{
		int temp = RetCode;
		RetCode = DataOK;
		return temp;
	}
};

#endif