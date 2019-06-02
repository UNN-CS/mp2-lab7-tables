#ifndef _TREETAB_H
#define _TREETAB_H

#include<stack>
#include"TTable.h"
#include"TTreeNode.h"

class  TTreeTable : public TTable {
protected:
	PTTreeNode pRoot; // óêàçàòåëü íà êîðåíü äåðåâà
	PTTreeNode *ppRef;// àäðåñ óêàçàòåëÿ íà âåðøèíó-ðåçóëüòàòà â FindRecord
	PTTreeNode pCurrent;// óêàçàòåëü íà òåêóùóþ âåðøèíó
	int CurrPos;        // íîìåð òåêóùåé âåðøèíû
	stack<PTTreeNode> St;// ñòåê äëÿ èòåðàòîðà
	void DeleteTreeTab(PTTreeNode pNode); // óäàëåíèå
public:
	TTreeTable() : TTable() { CurrPos = 0; pRoot = pCurrent = nullptr; ppRef = nullptr; }
	~TTreeTable() { DeleteTreeTab(pRoot); } // äåñòðóêòîð
											// èíôîðìàöèîííûå ìåòîäû
	virtual int IsFull() const; //çàïîëíåíà?
								//îñíîâíûå ìåòîäû
	virtual PTDatValue FindRecord(TKey k); // íàéòè çàïèñü
	virtual void InsRecord(TKey k, PTDatValue pVal); // âñòàâèòü
	virtual void DelRecord(TKey k);       // óäàëèòü çàïèñü
										  // íàâèãàöèÿ
	virtual TKey GetKey(void) const;
	virtual PTDatValue GetValuePTR(void) const;
	virtual int Reset(void);  // óñòàíîâèòü íà ïåðâóþ çàïèñü
	virtual int IsTabEnded(void) const; // òàáëèöà çàâåðøåíà?
	virtual int GoNext(void);// ïåðåõîä ê ñëåäóþùåé çàïèñè
							 //(=1 ïîñëå ïðèìåíåíèÿ äëÿ ïîñëåäíåé çàïèñè òàáëèöû)

protected:
	string tk[20];
	int tl[20], pos;
	void PutValues(PTTreeNode pNode, int Level);
};
#endif 
