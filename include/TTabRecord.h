#pragma once

#include "TDatValue.h"
#include <iostream>

typedef std::string TKey;     // тип ключа записи
							  // Класс объектов-значений для записей таблицы
class TTabRecord : public TDatValue {
protected:    // поля
	TKey Key;   // ключ записи
	PTDatValue pValue;   // указатель на значение
public:  // методы
	TTabRecord(TKey k = "", PTDatValue pVal = nullptr);// конструктор
	void SetKey(TKey k);// установить значение ключа
	TKey GetKey();  // получить значение ключа
	void SetValuePtr(PTDatValue p);// установить указатель на данные
	PTDatValue GetValuePtr(); // получить указатель на данные
	virtual TDatValue * GetCopy(); // изготовить копию
	TTabRecord & operator = (TTabRecord &tr);// присваивание
	virtual int operator == (const TTabRecord &tr); // сравнение =
	virtual int operator < (const TTabRecord &tr);  // сравнение «<»
	virtual int operator > (const TTabRecord &tr);  // сравнение «>»
													
	friend class TArrayTable;
	friend class TScanTable;
	friend class TSortTable;
	friend class TTreeNode;
	friend class TTreeTable;
	friend class TArrayHash;
	friend class TListHash;
};
typedef TTabRecord* PTTabRecord;

