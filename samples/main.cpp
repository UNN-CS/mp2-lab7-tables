#include "TScanTable.h"
#include "TSortTable.h"
#include "TTreeTab.h"
#include "TBalTree.h"
#include "TArrayHash.h"
#include "TListHash.h"
#include <iostream>
#include <fstream>
#include "Application.h"

using namespace std;
int main()
{
	TTable** tables = new TTable*[2];

	tables[0] = new TScanTable();
	ReadFromFile("gr1.txt", tables[0]);

	tables[1] = new TListHash();
	ReadFromFile("gr2.txt", tables[1]);


	cout << "Group 1" << endl;
	Print(tables[0]);
	cout << "Group 2" << endl;
	Print(tables[1]);


	cout << "Excellent in first group = " << GetExcellent(tables[0])<< endl;
	cout << "Excellent in second group = " << GetExcellent(tables[1]) << endl;
	cout << "Excellent in all group = " << GetExcellentAllGroup(tables , 2) << endl <<endl;

	cout << "Average mark by Prog in first group = "<< AverMarkGroupBySub(tables[0], "Prog") <<endl;
	cout << "Average mark by Prog in second group = " << AverMarkGroupBySub(tables[1], "Prog") << endl;
	cout << "Average mark by Prog in all group = " << AverMarkAllGroupBySub(tables , 2, "Prog") <<endl<< endl;

	cout << "Average mark by all sub in first group = " << AverMarkGroup(tables[0]) << endl;
	cout << "Average mark by all sub in second group = " << AverMarkGroup(tables[1]) << endl;
	cout << "Excellent in all group = " << AverMarkAllGroup(tables , 2) << endl <<endl;

	return 0;
}
