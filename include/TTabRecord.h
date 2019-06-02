#ifndef __TABRECORD_H__
#define __TABRECORD_H__

#include "TDatValue.h"
#include "TStudentRecord.h"

typedef std::string TKey;

class TTabRecord : public TDatValue {
protected:
	TKey Key;
	PTDatValue pValue;
public: // методы
	TTabRecord(TKey k = "", PTDatValue pVal = nullptr);// конструктор
	void SetKey(TKey k);// установить значение ключа
	TKey GetKey(); // получить значение ключа
	void SetValuePtr(PTDatValue p);// установить указатель на данные
	PTDatValue GetValuePTR(); // получить указатель на данные
	virtual TDatValue * GetCopy(); // изготовить копию
	TTabRecord & operator = (TTabRecord &tr);// присваивание
	virtual int operator == (const TTabRecord &tr); // сравнение =
	virtual int operator < (const TTabRecord &tr); // сравнение «<»
	virtual int operator > (const TTabRecord &tr); // сравнение «>»
   //дружественные классы для различных типов таблиц, см. далее
	friend class TArrayTable;
	friend class TScanTable;
	friend class TSortTable;
	friend class TTreeNode;
	friend class TTreeTable;
	friend class TArrayHash;
	friend class TListHash;
};
typedef TTabRecord* PTTabRecord;

#endif