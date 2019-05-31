#ifndef __TTABLE_H
#define __TTABLE_H
#include <iostream>
#include "TTabRecord.h"
#include "tdatacom.h"
using namespace std;

#define TabOK 0 // ошибок нет
#define TabEmpty -101 //таблица пуста
#define TabFull -102 // таблица полна
#define TabNoRec -103 // нет записи
#define TabNoMem -104 // нет памяти
#define TabRecDbl -105 // дублирование записи

class TTable : public TDataCom
{
protected:
	int DataCount; // кол-во записей в таблице
	int Efficiency; // показатель эффективности выполнения операций
public :
	TTable() { DataCount = 0; Efficiency = 0; }
	virtual ~TTable() {};
	//информационные методы
	int GetDataCount() const { return DataCount; } //получить кол-во записей
	int GetEfficiency() const { return Efficiency; } //получить эффективность
	int IsEmpty() const { return DataCount == 0; }
	virtual int IsFull() const = 0;
	// основные методы
	virtual PTDatValue FindRecord(TKey k) = 0; // найти запись по ключу
	virtual void InsRecord(TKey,PTDatValue) = 0; // вставить запись
	virtual void DelRecord(TKey k) = 0;// удалить запись по ключу
	// навигация
	virtual int Reset() = 0; // установить на первую запись
	virtual int IsTabEnded() const = 0; //таблица завершена?
	virtual int GoNext() = 0;// переход к следующей записи
	// доступ
	virtual TKey GetKey() const = 0;
	virtual PTDatValue GetValuePtr() const = 0;
	// печать таблицы
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
