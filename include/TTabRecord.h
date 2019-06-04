#ifndef TABRECORD_H_
#define TABRECORD_H_
#include <string>
#include "TDatValue.h"

using namespace std;
typedef string TKey;															 // ��� ����� ������
							
class TTabRecord : public TDatValue {  
	protected:    
		// ����    
	TKey Key;																	// ���� ������
	PTDatValue pValue;															// ��������� �� ��������
  public:																		 // ������
	TTabRecord(TKey k = "", PTDatValue pVal = NULL);						// ����������� 
	void SetKey(TKey k);													// ���������� �������� �����
	  TKey GetKey(void);														 // �������� �������� �����
	  void SetValuePtr(PTDatValue p);											// ���������� ��������� �� ������
	  PTDatValue GetValuePTR(void);												// �������� ��������� �� ������
	  virtual TDatValue * GetCopy();												// ���������� �����
	  TTabRecord & operator = (TTabRecord &tr);									// ������������
	  virtual int operator == (const TTabRecord &tr);							// ��������� =
	  virtual int operator < (const TTabRecord &tr);							// ��������� �<�
	  virtual int operator > (const TTabRecord &tr);							// ��������� �>�
													  //������������� ������ ��� ��������� ����� ������, ��. �����
	  friend class TArrayTable;
	  friend class TScanTable;
	  friend class TSortTable;
	  friend class TTreeNode;
	  friend class TTreeTable;
	  friend class TArrayHash;
	  friend class TListHash;
};

typedef TTabRecord *PTTabRecord;

#endif  // TABRECORD_H_
