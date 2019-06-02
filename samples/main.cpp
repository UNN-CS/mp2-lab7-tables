#include "TScanTable.h"
#include "TSortTable.h"
#include "TTreeTab.h"
#include "TBalTree.h"
#include "TArrayHash.h"
#include "TListHash.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "Application.h"

using namespace std;

int main()
{
	TTable** tables = new TTable*[3];

	tables[0] = new TScanTable();
	ReadFromFile("gr1.txt", tables[0]);

	tables[1] = new TListHash();
	ReadFromFile("gr2.txt", tables[1]);

	tables[2] = new TSortTable();
	ReadFromFile("gr3.txt", tables[2]);

	tables[3] = new TTreeTable();
	ReadFromFile("gr4.txt", tables[3]);


	cout << "Group 1(Scan)" << endl;
	Print(tables[0]);
	cout << endl << "Group 2(Hash)" << endl;
	Print(tables[1]);
	cout << endl << "Group 3(Sort)" << endl;
	Print(tables[2]);
	cout << endl << "Group 4(Tree)" << endl;
	Print(tables[3]);



	for (int i = 0; i <= 3; i++)
	{
		cout << "Excellent in "<< i+1 <<" group = " << GetExcellent(tables[i]) << endl;
	}
	cout << "Excellent in all group = " << GetExcellentAllGroup(tables , 4) << endl <<endl;

	for (int i = 0; i <= 3; i++)
	{
		cout << "Average mark by Prog in "<< i+1 <<" group = " << AverMarkGroupBySub(tables[i], "Prog") << endl;
	}
	cout << "Average mark by Prog in all group = " << AverMarkAllGroupBySub(tables , 4, "Prog") <<endl<< endl;

	for (int i = 0; i <= 3; i++)
	{
		cout << "Average mark by all sub in "<< i+1 <<" group = " << AverMarkGroup(tables[i]) << endl;
	}
	cout << "Excellent in all group = " << AverMarkAllGroup(tables , 4) << endl <<endl;
	
	for (int i = 0; i <= 3; i++)
	{
		cout << "efficiency " << i + 1 << " table = " << GetTebleEfficiency(tables[i]) << endl;
	}
	return 0;
}
