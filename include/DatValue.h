#pragma once
#include <iostream>
using namespace std;

class TDatValue;
typedef TDatValue * PTDatValue;

class TDatValue {  //������, ����������� ����������� ����� ��������-�������� ������
  public:
    virtual TDatValue * GetCopy() =0; // �������� �����
   ~TDatValue() {}
};