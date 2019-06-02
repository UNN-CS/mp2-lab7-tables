#include "stdio.h"
#include <iostream>
#include <ctime>
#include "TScanTable.h"
#include "TSortTable.h"
#include "TTreeTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"
using namespace std;
int TStudRec::marks_number = 4;

typedef char* pchar;

char* gen_random(const int len) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	char* s = new char[len];

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	s[len] = 0;
	return s;
}

int main()
{
	srand(time(0));
	int Size = 1000;
	int count = 1000;
	pchar* kmass = new pchar[Size];
	PTStudRec psr = new TStudRec[Size];
	TScanTable tscant(Size);
	TSortTable tsortt(Size);
	TTreeTable ttreet;
	TBalanceTree tbalancet;
	TArrayHash tarrayh(Size);
	TListHash tlisth(Size);

	//key generation 
	for (int i = 0;i < count;i++)
		kmass[i] = gen_random(5);

	//insert
	for (int i = 0;i <count;i++)
	{
		tscant.InsRecord(kmass[i], nullptr);
		tsortt.InsRecord(kmass[i], nullptr);
		ttreet.InsRecord(kmass[i], nullptr);
		tbalancet.InsRecord(kmass[i], nullptr);
		tarrayh.InsRecord(kmass[i], psr);
		tlisth.InsRecord(kmass[i], psr);
	}

	// insert efficiency
	cout << "Insert - number of operations " << endl;
	cout << "ScanTable - number of operations = " << tscant.GetEfficiency() << endl;
	cout << "SortTable - number of operations = " << tsortt.GetEfficiency() << endl;
	cout << "TreeTable - number of operations = " << ttreet.GetEfficiency() << endl;
	cout << "BalanceTree - number of operations = " << tbalancet.GetEfficiency() << endl;
	cout << "ArrayHash - number of operations = " << tarrayh.GetEfficiency() << endl;
	cout << "ListHash - number of operations = " << tlisth.GetEfficiency() << endl<<endl;

	tscant.ResetEfficiency();
	tsortt.ResetEfficiency();
	ttreet.ResetEfficiency();
	tbalancet.ResetEfficiency();
	tarrayh.ResetEfficiency();
	tlisth.ResetEfficiency();

	//find
	for (int i = 0;i < count;i++)
	{
		tscant.FindRecord(kmass[i]);
		tsortt.FindRecord(kmass[i]);
		ttreet.FindRecord(kmass[i]);
		tbalancet.FindRecord(kmass[i]);
		tarrayh.FindRecord(kmass[i]);
		tlisth.FindRecord(kmass[i]);
	}

	//Find efficiency
	cout << "Find - number of operations " << endl;
	cout << "ScanTable - number of operations = " << tscant.GetEfficiency() << endl;
	cout << "SortTable - number of operations = " << tsortt.GetEfficiency() << endl;
	cout << "TreeTable - number of operations = " << ttreet.GetEfficiency() << endl;
	cout << "BalanceTree - number of operations = " << tbalancet.GetEfficiency() << endl;
	cout << "ArrayHash - number of operations = " << tarrayh.GetEfficiency() << endl;
	cout << "ListHash - number of operations = " << tlisth.GetEfficiency() << endl<<endl;

	tscant.ResetEfficiency();
	tsortt.ResetEfficiency();
	ttreet.ResetEfficiency();
	tbalancet.ResetEfficiency();
	tarrayh.ResetEfficiency();
	tlisth.ResetEfficiency();

	//delete
	for (int i = 0;i < count;i++)
	{
		tscant.DelRecord(kmass[i]);
		tsortt.DelRecord(kmass[i]);
		ttreet.DelRecord(kmass[i]);
		tbalancet.DelRecord(kmass[i]);
		tarrayh.DelRecord(kmass[i]);
		tlisth.DelRecord(kmass[i]);
	}

	//Delete efficiency
	cout << "Delete - number of operations " << endl;
	cout << "ScanTable - number of operations = " << tscant.GetEfficiency() << endl;
	cout << "SortTable - number of operations = " << tsortt.GetEfficiency() << endl;
	cout << "TreeTable - number of operations = " << ttreet.GetEfficiency() << endl;
	cout << "BalanceTree - number of operations = " << tbalancet.GetEfficiency() << endl;
	cout << "ArrayHash - number of operations = " << tarrayh.GetEfficiency() << endl;
	cout << "ListHash - number of operations = " << tlisth.GetEfficiency() << endl;

	tscant.ResetEfficiency();
	tsortt.ResetEfficiency();
	ttreet.ResetEfficiency();
	tbalancet.ResetEfficiency();
	tarrayh.ResetEfficiency();
	tlisth.ResetEfficiency();

	return 0;
}