#ifndef __T_TREE_TABLE__
#define __T_TREE_TABLE__

#include <stack>
#include "ttable.h"
#include "ttreenode.h"

class TTreeTable : public TTable {
protected:
	PTTreeNode pRoot; // óêàçàòåëü íà êîðåíü äåðåâà
	PTTreeNode *ppRef;// àäðåñ óêàçàòåëÿ íà âåðøèíó-ðåçóëüòàòà â FindRecord
	PTTreeNode pCurrent;// óêàçàòåëü íà òåêóùóþ âåðøèíó
	int CurrPos;        // íîìåð òåêóùåé âåðøèíû
	std::stack <PTTreeNode> St;// ñòåê äëÿ èòåðàòîðà
	void DeleteTreeTab(PTTreeNode pNode); // óäàëåíèå
public:
	TTreeTable() : TTable() {
		CurrPos = 0;
		pRoot = pCurrent = nullptr;
		ppRef = nullptr;
	}
	~TTreeTable() { DeleteTreeTab(pRoot); } // äåñòðóêòîð
											// èíôîðìàöèîííûå ìåòîäû
	virtual int IsFull() const; //çàïîëíåíà?
								//îñíîâíûå ìåòîäû
	virtual PTDatValue FindRecord(TKey k); // íàéòè çàïèñü
	virtual void InsRecord(TKey k, PTDatValue pVal); // âñòàâèòü
	virtual void DelRecord(TKey k);       // óäàëèòü çàïèñü
	void Show(); // ïå÷àòü äåðåâà (ðèñóíîê ñâåðõó âíèç)
	void Print(PTTreeNode pNode, int depth = 0);
	void Print() { Print(pRoot); }
	// íàâèãàöèÿ
	virtual TKey GetKey() const;
	virtual PTDatValue GetValuePtr() const;
	virtual int Reset();  // óñòàíîâèòü íà ïåðâóþ çàïèñü
	virtual int IsTabEnded() const; // òàáëèöà çàâåðøåíà?
	virtual int GoNext();// ïåðåõîä ê ñëåäóþùåé çàïèñè
						 //(=1 ïîñëå ïðèìåíåíèÿ äëÿ ïîñëåäíåé çàïèñè òàáëèöû)
	
};


#endif //__T_TREE_TABLE__