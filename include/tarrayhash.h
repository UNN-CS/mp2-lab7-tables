#ifndef __T_ARRAY_HASH_H__
#define __T_ARRAY_HASH_H__

typedef string TKey     // тип ключа записи
//  ласс объектов-значений дл€ записей таблицыclass TTabRecord : public TDatValue {  protected:    // пол€    TKey Key;   // ключ записи
    PTDatValue pValue;   // указатель на значение
  public:  // методы
    TTabRecord (TKey k=ФФ, PTDatValue pVal = NULL)// конструктор
    void SetKey(TKey k);// установить значение ключа
    TKey GetKey(void);  // получить значение ключа
    void SetValuePtr(PTDatValue p);// установить указатель на данные
    PTDatValue GetValuePTR (void); // получить указатель на данные
    virtual TDatValue * GetCopy(); // изготовить копию
    TTabRecord & operator = (TTabRecord &tr);// присваивание
    virtual int operator == (const TTabRecord &tr); // сравнение =
    virtual int operator < (const TTabRecord &tr);  // сравнение Ђ<ї
    virtual int operator > (const TTabRecord &tr);  // сравнение Ђ>ї
//дружественные классы дл€ различных типов таблиц, см. далее
  friend class TArrayTable;
  friend class TScanTable;
  friend class TSortTable;
  friend class TTreeNode;
  friend class TTreeTable;
  friend class TArrayHash;
  friend class TListHash;
};

#endif // __T_ARRAY_HASH_H__
