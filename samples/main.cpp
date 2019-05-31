#include <conio.h>
#include <string>
#include <iostream>
#include <TScanTable.h>
#include "TWord.h"
#include "sorttab.h"
#include "ListHash.h"
#include "balancetree.h"
#include "arrhash.h"
#include "treetab.h"
using namespace std;
TScanTable * Tab = NULL;
string * pKeys = NULL;

int DataCount = 0, mem;

// заполнение таблицы
/*void TableGenerator()
{
	int MaxKeyValue, RetCode;
	char Line[100];
	cout << "Input the record's number - ";
	cin >> DataCount;
	cout << "Input the Maximum Key Value - ";
	cin >> MaxKeyValue;
	mem = DataCount + 10;
	Tab = new TScanTable(mem);
	pKeys = new string[mem];
	pWords = new string[mem];
	for (int i = 0; i < DataCount; ++i)
	{
		sprintf(Line, "%d", rand()%MaxKeyValue+1);
		pKeys[i] = string(Line);
		pWords[i] = string("*" + pKeys[i] + "*");
		Tab->InsRecord(pKeys[i], pWords[i]);
	}

}*/

int main()
{
	int n;
	cin >> n;
	TScanTable tab1(n);
	TreeTable t;
	BalanceTree t2;
	ArrayHash arh(10,3);
	ListHash ltab(10);
	SortTable tab2(n);
	TWord * w1 = new TWord[n];
	for (int i = 0; i < n; ++i)
	{
		string s,s1;
		cin >> s>>s1;
		w1[i] = s1;
		tab1.InsRecord(s, &w1[i]);
		tab2.InsRecord(s, &w1[i]);
		t.InsRecord(s, &w1[i]);
		t2.InsRecord(s, &w1[i]);
		arh.InsRecord(s, &w1[i]);
		ltab.InsRecord(s, &w1[i]);
	}
	SortTable tab3 = tab1;
	tab1.DelRecord(string("1"));
	cout << tab1<<endl;
	cout << endl;
	cout << tab2 << endl;
	tab2.DelRecord(string("3"));
	tab2.DelRecord(string("4"));
    cout << tab2<<endl;
	cout << tab3 << endl;
	cout << "-------------------------------------" << endl;
	for (t.Reset();!t.IsTabEnded();t.GoNext())
	    cout << t.GetKey() << endl;
	t.Show();
	cout << endl;
	t.DelRecord(string("3"));
	cout << t << endl;
	t.Draw();
	cout << endl;
	t.Show();
	t.Reset();
	cout << t.GetKey()<<endl;
	cout << "-------------------------------------" << endl;
	t2.Show();
	cout << endl;
	cout << t2 << endl;
	t2.Draw();
	cout << "-------------------------------------" << endl;
	cout<<t2;
	t2.Show();
	cout << "-------------------------------------" << endl;
	cout << arh<<endl;
	arh.DelRecord("b");
	cout << arh;
	cout << "-------------------------------------" << endl;
	ltab.InsRecord("d", &w1[0]);
	ltab.InsRecord("n", &w1[1]);
	ltab.InsRecord("x", &w1[2]);
	cout << ltab << endl;
	ltab.DelRecord("f");
	ltab.DelRecord("m");
	cout << ltab << endl;
	system("pause");

	return 0;
}
/*
4
1 cat
2 ox
4 bird
3 elefant

10
a 1
e 5
h 8
b 2
d 4
c 3
f 6
m 8
g 7
i 9


*/