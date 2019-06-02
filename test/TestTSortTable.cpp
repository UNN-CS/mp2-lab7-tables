#include <gtest.h>
#include "TSortTable.h"

TEST(TSortTable, can_create)
{
	TSortTable *tab;

	ASSERT_NO_THROW(tab = new TSortTable(50));
}

TEST(TSortTable, check_operator_equal)
{
	TSortTable tabSort;
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);

	bool flag = true;
	tabSort = tab;
	for (tab.Reset(), tabSort.Reset(); tab.IsTabEnded(),
		tabSort.IsTabEnded(); tab.GoNext(), tabSort.GoNext())
		if (tab.GetKey() != tabSort.GetKey() ||
			tab.GetValuePTR() == tabSort.GetValuePTR())
			flag = false;

	EXPECT_EQ(true, flag);
}

TEST(TSortTable, can_insert_record_and_check_sort)
{
	TSortTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();
    PTDatValue t4 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("3", t3);
	tab.InsRecord("4", t4);
	tab.InsRecord("2", t2);

	tab.SetCurrentPos(3);

	EXPECT_EQ("4", tab.GetKey());
}

TEST(TSortTable, can_insert_record_and_check_dataCount)
{
	TSortTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();
    PTDatValue t4 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("3", t3);
    tab.InsRecord("4", t4);
    tab.InsRecord("2", t2);

	EXPECT_EQ(4, tab.GetDataCount());
}

TEST(TSortTable, can_delete_record_and_check_dataCount)
{
	TSortTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();
    PTDatValue t4 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("3", t3);
    tab.InsRecord("4", t4);
    tab.InsRecord("2", t2);

	tab.DelRecord("4");

	EXPECT_EQ(3, tab.GetDataCount());
}

TEST(TSortTable, check_sort_merge)
{
	TSortTable tabSort(5);

	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();
    PTDatValue t4 = new TTabRecord();
    PTDatValue t5 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("5", t5);
	tab.InsRecord("3", t3);
	tab.InsRecord("4", t4);
	tab.InsRecord("2", t2);

	tabSort.SetSortMethod(MERGE_SORT);
	tabSort = tab;
	int i = 1;
	bool flag = true;
	for (tabSort.Reset(); tabSort.IsTabEnded(); tabSort.GoNext(), i++)
		if (tabSort.GetValuePTR() != (PTDatValue)i)
			flag = false;

	EXPECT_EQ(true, flag);
}

TEST(TSortTable, check_sort_quick)
{
	TSortTable tabSort(5);

	TScanTable tab(5);

    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();
    PTDatValue t4 = new TTabRecord();
    PTDatValue t5 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("5", t5);
    tab.InsRecord("3", t3);
    tab.InsRecord("4", t4);
    tab.InsRecord("2", t2);

	tabSort.SetSortMethod(QUICK_SORT);
	tabSort = tab;
	int i = 1;
	bool flag = true;
	for (tabSort.Reset(); tabSort.IsTabEnded(); tabSort.GoNext(), i++)
		if (tabSort.GetValuePTR() != (PTDatValue)i)
			flag = false;

	EXPECT_EQ(true, flag);
}