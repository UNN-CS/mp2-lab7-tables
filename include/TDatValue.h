// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tdatvalue.h 
//
// �������� �����

#ifndef __TDATVALUE_H__
#define __TDATVALUE_H__

class TDatValue;
typedef TDatValue *PTDatValue;

class TDatValue {
  public:
    virtual PTDatValue GetCopy() = 0; // �������� �����
	~TDatValue() {}
}; 

#endif //__TDATVALUE_H__
