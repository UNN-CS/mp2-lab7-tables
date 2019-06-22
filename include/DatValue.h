#pragma once
#include <iostream>
using namespace std;

// class TDatValue;
// typedef TDatValue * PTDatValue;
typedef string * PTDatValue; // because we need operator<<
typedef string TDatValue; // because we need operator<<

/*
class TDatValue {  //модуль, объ€вл€ющий абстрактный класс объектов-значений списка
  public:
    virtual TDatValue * GetCopy() =0; // создание копии
   ~TDatValue() {}
};
*/