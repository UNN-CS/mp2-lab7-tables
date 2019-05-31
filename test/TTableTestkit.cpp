#include <gtest/gtest.h>
#include "TScanTable.h"
#include "TSortTable.h"
#include "TBalTree.h"
#include "TArrayHash.h"
#include "TListHash.h"

//TScanTable

TEST(TScanTable, can_create_with_positive_lenght)
{
	TScanTable *tab;

	ASSERT_NO_THROW(tab = new TScanTable(11));
}

TEST(TScanTable, can_create_with_negative_lenght)
{
	TScanTable *tab;

	ASSERT_NO_THROW(tab = new TScanTable(-11));
}

TEST(TScanTable, can_check_full_fasle)
{
	TScanTable tab(5);

	EXPECT_EQ(0, tab.IsFull());
}

TEST(TScanTable, can_check_full_true)
{
	TScanTable tab(5);
	for (int i = 0; i < 5; i++)
	{
		tab.InsRecord("", (PTDatValue)i);
	}
	EXPECT_EQ(1, tab.IsFull());
}

TEST(TScanTable, can_find_record)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("2", t2);
	tab.InsRecord("3", t3);

	EXPECT_EQ(t2, tab.FindRecord("2"));
}

TEST(TScanTable, can_find_nonexistent_record)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("2", t2);
	tab.InsRecord("3", t3);

	EXPECT_EQ(nullptr, tab.FindRecord("5"));
}

TEST(TScanTable, can_delete_record_check_DataCount)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("2", t2);
	tab.InsRecord("3", t3);

	tab.DelRecord("2");

	EXPECT_EQ(2, tab.GetDataCount());
}

TEST(TScanTable, can_insert_record_check_DataCount)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("3", t2);

	tab.InsRecord("2");

	EXPECT_EQ(3, tab.GetDataCount());
}

TEST(TScanTable, can_check_empty_true)
{
	TScanTable tab(5);

	EXPECT_EQ(1, tab.IsEmpty());
}

TEST(TScanTable, can_check_empty_false)
{
	TScanTable tab(5);
	for (int i = 0; i < 5; i++)
	{
		tab.InsRecord("", new TTabRecord());
	}
	EXPECT_EQ(0, tab.IsEmpty());
}

TEST(TScanTable, can_get_key_first_pos)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("2", t2);

	EXPECT_EQ("1", tab.GetKey(FIRST_POS));
}

TEST(TScanTable, can_get_key_last_pos)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("2", t2);

	EXPECT_EQ("2", tab.GetKey(LAST_POS));
}

TEST(TScanTable, can_get_key_current_pos)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("2", t2);
	tab.InsRecord("3", t3);

	tab.SetCurrentPos(1);
	EXPECT_EQ("2", tab.GetKey(CURRENT_POS));
}

TEST(TScanTable, can_get_key)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();

	tab.InsRecord("1", t1);

	EXPECT_EQ("1", tab.GetKey());
}

TEST(TScanTable, can_get_value)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();

	tab.InsRecord("1", t1);

	EXPECT_EQ(t1, tab.GetValuePTR());
}

TEST(TScanTable, can_get_value_first_pos)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);

	EXPECT_EQ(t1, tab.GetValuePTR(FIRST_POS));
}

TEST(TScanTable, can_get_value_last_pos)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);

	EXPECT_EQ(t3, tab.GetValuePTR(LAST_POS));
}

TEST(TScanTable, can_get_value_current_pos)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);
	tab.SetCurrentPos(1);

	EXPECT_EQ(t2, tab.GetValuePTR(CURRENT_POS));
}

TEST(TScanTable, can_get_size)
{
	TScanTable tab(5);

	EXPECT_EQ(5, tab.GetTabSize());
}

TEST(TScanTable, can_reset)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);
	tab.SetCurrentPos(1);

	tab.Reset();

	EXPECT_EQ(0, tab.GetCurrentPos());
}

TEST(TScanTable, can_go_next)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);

	tab.GoNext();

	EXPECT_EQ(1, tab.GetCurrentPos());
}

TEST(TScanTable, can_go_next_if_table_is_end)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();

	tab.GoNext();

	EXPECT_EQ(3, tab.GetCurrentPos());
}

TEST(TScanTable, can_check_end_tab_true)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();

	EXPECT_EQ(1, tab.IsTabEnded());
}

TEST(TScanTable, can_check_end_tab_return_false)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);
	tab.GoNext();

	EXPECT_EQ(0, tab.IsTabEnded());
}

//TSortTable

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

//TTreeTable

TEST(TTreeTable, can_create)
{
	TTreeTable *tab;

	ASSERT_NO_THROW(tab = new TTreeTable());
}

TEST(TTreeTable, can_insert_record)
{
	TTreeTable *tab;

	tab = new TTreeTable();
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

	tab->InsRecord("1", t1);
	tab->InsRecord("2", t2);
	tab->InsRecord("3", t3);
	tab->Reset();
	tab->GoNext();

	EXPECT_EQ("2", tab->GetKey());
}

TEST(TTreeTable, can_delete_record_if_no_record)
{
	TTreeTable *tab;

	tab = new TTreeTable();

    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab->InsRecord("1", t1);
    tab->InsRecord("2", t2);
    tab->InsRecord("3", t3);

	tab->DelRecord("5");

	EXPECT_EQ(3, tab->GetDataCount());
}

TEST(TTreeTable, can_delete_record)
{
	TTreeTable *tab;

	tab = new TTreeTable();

    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab->InsRecord("1", t1);
    tab->InsRecord("2", t2);
    tab->InsRecord("3", t3);

	tab->DelRecord("3");

	EXPECT_EQ(nullptr, tab->FindRecord("3"));
}

TEST(TTreeTable, can_delete_root)
{
	TTreeTable *tab;

	tab = new TTreeTable();

    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab->InsRecord("1", t1);
    tab->InsRecord("2", t2);
    tab->InsRecord("3", t3);

	tab->DelRecord("2");
	tab->Reset();
	tab->GoNext();

	EXPECT_EQ("3", tab->GetKey());
}

TEST(TTreeTable, can_delete_record_with_two_child)
{
	TTreeTable *tab;

	tab = new TTreeTable();
    PTDatValue t1 = new TTabRecord();

	tab->InsRecord("8", t1);
	tab->InsRecord("12", t1);
	tab->InsRecord("9", t1);
	tab->InsRecord("11", t1);
	tab->InsRecord("15", t1);
	tab->InsRecord("78", t1);

	tab->DelRecord("12");

	EXPECT_EQ(nullptr, tab->FindRecord("12"));
}

TEST(TTreeTable, can_delete_record_with_two_child_check_order)
{
	TTreeTable *tab;

	tab = new TTreeTable();
    PTDatValue t1 = new TTabRecord();

    tab->InsRecord("10", t1);
    tab->InsRecord("13", t1);
    tab->InsRecord("11", t1);
    tab->InsRecord("12", t1);
    tab->InsRecord("1", t1);
    tab->InsRecord("25", t1);

    tab->DelRecord("13");
    tab->Reset(); //1
    tab->GoNext();//10
    tab->GoNext(); //11
    tab->GoNext();//12
    tab->GoNext();//25

    EXPECT_EQ("25", tab->GetKey());
}

TEST(TTreeTable, can_delete_record_with_one_left_child)
{
	TTreeTable *tab;

	tab = new TTreeTable();
    PTDatValue t1 = new TTabRecord();

	tab->InsRecord("10", t1);
	tab->InsRecord("130", t1);
	tab->InsRecord("11", t1);
	tab->InsRecord("127", t1);
	tab->InsRecord("1", t1);
	tab->InsRecord("0", t1);
	tab->InsRecord("25", t1);

	tab->DelRecord("1");

	EXPECT_EQ(nullptr, tab->FindRecord("1"));
}

TEST(TTreeTable, can_delete_record_with_one_left_cild_check_order)
{
	TTreeTable *tab;

	tab = new TTreeTable();
    PTDatValue t1 = new TTabRecord();

	tab->InsRecord("10", t1);
	tab->InsRecord("13", t1);
	tab->InsRecord("11", t1);
	tab->InsRecord("12", t1);
	tab->InsRecord("1", t1);
	tab->InsRecord("25", t1);
	tab->InsRecord("20", t1);

	tab->DelRecord("25");
	tab->Reset();//1
	tab->GoNext();//10
	tab->GoNext();//11
	tab->GoNext();//12
	tab->GoNext();//13
	tab->GoNext();// 20	

	EXPECT_EQ("20", tab->GetKey());
}

TEST(TTreeTable, can_delete_record_with_one_right_child)
{
	TTreeTable *tab;

	tab = new TTreeTable();
    PTDatValue t1 = new TTabRecord();

	tab->InsRecord("10", t1);
	tab->InsRecord("13", t1);
	tab->InsRecord("11", t1);
	tab->InsRecord("12", t1);
	tab->InsRecord("1", t1);
	tab->InsRecord("0", t1);
	tab->InsRecord("25", t1);

	tab->DelRecord("11");

	EXPECT_EQ(nullptr, tab->FindRecord("11"));
}

TEST(TTreeTable, can_delete_record_with_one_right_child_check_order)
{
	TTreeTable *tab;

	tab = new TTreeTable();
    PTDatValue t1 = new TTabRecord();

	tab->InsRecord("10", t1);
	tab->InsRecord("13", t1);
	tab->InsRecord("11", t1);
	tab->InsRecord("12", t1);
	tab->InsRecord("1", t1);
	tab->InsRecord("25", t1);
	tab->InsRecord("20", t1);

	tab->DelRecord("11");
	tab->Reset();
	tab->GoNext();
	tab->GoNext();

	EXPECT_EQ("12", tab->GetKey());
}

TEST(TTreeTable, can_insert_after_delete)
{
	TTreeTable *tab;

	tab = new TTreeTable();
    PTDatValue t1 = new TTabRecord();

	tab->InsRecord("10", t1);
	tab->InsRecord("16", t1);
	tab->InsRecord("12", t1);
	tab->InsRecord("15", t1);
	tab->InsRecord("1", t1);
	tab->InsRecord("25", t1);
	tab->InsRecord("20", t1);

	tab->DelRecord("12");
	tab->InsRecord("11", (PTDatValue)1);
	tab->Reset();
	tab->GoNext();
	tab->GoNext();

	EXPECT_EQ("11", tab->GetKey());
}


//TBallTree

TEST(TBalanceTree, can_create)
{
	TBalanceTree *tab;

	ASSERT_NO_THROW(tab = new TBalanceTree());
}

TEST(TBalanceTree, can_insert_record)
{
	TBalanceTree *tab = new TBalanceTree();
    PTDatValue t1 = new TTabRecord();

	tab->InsRecord("1", t1);
	tab->Reset();

	EXPECT_EQ("1", tab->GetKey());
}

TEST(TBalanceTree, can_delete_record_without_child_check_order)
{
	TBalanceTree *tab = new TBalanceTree();
    PTDatValue t1 = new TTabRecord();

	tab->InsRecord("3", t1);
	tab->InsRecord("2", t1);
	tab->InsRecord("1", t1);
	tab->InsRecord("6", t1);
	tab->InsRecord("7", t1);
	tab->InsRecord("4", t1);
	tab->InsRecord("5", t1);

	tab->DelRecord("1");
	tab->Reset();	

	EXPECT_EQ("2", tab->GetKey());
}

TEST(TBalanceTree, can_delete_record_without_child)
{
	TBalanceTree *tab = new TBalanceTree();
    PTDatValue t1 = new TTabRecord();

	tab->InsRecord("1", t1);
	tab->InsRecord("2", t1);
	tab->InsRecord("3", t1);
	tab->InsRecord("4", t1);
	tab->InsRecord("5", t1);
	tab->InsRecord("6", t1);
	tab->InsRecord("7", t1);

	tab->DelRecord("1");

	EXPECT_EQ(nullptr, tab->FindRecord("1"));
}

TEST(TBalanceTree, can_del_rec_with_one_left_child_check_order)
{
	TBalanceTree *tab = new TBalanceTree();
    PTDatValue t1 = new TTabRecord();

	tab->InsRecord("3", t1);
	tab->InsRecord("2", t1);
	tab->InsRecord("1", t1);
	tab->InsRecord("6", t1);
	tab->InsRecord("7", t1);
	tab->InsRecord("4", t1);
	tab->InsRecord("5", t1);

	tab->DelRecord("2");
	tab->Reset();//1
	tab->GoNext();//3


	EXPECT_EQ("3", tab->GetKey());
}

TEST(TBalanceTree, can_delete_record_with_one_left_child)
{
	TBalanceTree *tab = new TBalanceTree();
    PTDatValue t1 = new TTabRecord();

	tab->InsRecord("3", t1);
	tab->InsRecord("2", t1);
	tab->InsRecord("1", t1);
	tab->InsRecord("6", t1);
	tab->InsRecord("7", t1);
	tab->InsRecord("4", t1);
	tab->InsRecord("5", t1);

	tab->DelRecord("2");

	EXPECT_EQ(nullptr, tab->FindRecord("2"));
}

TEST(TBalanceTree, can_delete_record_with_one_right_child_check_order)
{
	TBalanceTree *tab = new TBalanceTree();
    PTDatValue t1 = new TTabRecord();

	tab->InsRecord("3", t1);
	tab->InsRecord("2", t1);
	tab->InsRecord("1", t1);
	tab->InsRecord("6", t1);
	tab->InsRecord("7", t1);
	tab->InsRecord("4", t1);
	tab->InsRecord("5", t1);

	tab->DelRecord("4");
	tab->Reset();
	tab->GoNext();
	tab->GoNext();
	tab->GoNext();

	EXPECT_EQ("5", tab->GetKey());
}

TEST(TBalanceTree, can_del_rec_with_one_right_child)
{
	TBalanceTree *tab = new TBalanceTree();
    PTDatValue t1 = new TTabRecord();

	tab->InsRecord("3", t1);
	tab->InsRecord("2", t1);
	tab->InsRecord("1", t1);
	tab->InsRecord("6", t1);
	tab->InsRecord("7", t1);
	tab->InsRecord("4", t1);
	tab->InsRecord("5", t1);

	tab->DelRecord("4");

	EXPECT_EQ(nullptr, tab->FindRecord("4"));
}

//TArrayHach

TEST(TArrayHash, can_create_default)
{
	TArrayHash *tab;

	ASSERT_NO_THROW(tab = new TArrayHash());
}

TEST(TArrayHash, can_create_with_incorrect_size)
{
	TArrayHash *tab;

	ASSERT_ANY_THROW(tab = new TArrayHash(-1));
}

TEST(TArrayHash, can_create_with_step_larger_size)
{
	TArrayHash *tab;

	ASSERT_ANY_THROW(tab = new TArrayHash(10, 15));
}

TEST(TArrayHash, can_create_with_incorrect_step)
{
	TArrayHash *tab;

	ASSERT_ANY_THROW(tab = new TArrayHash(10, 1));
}

TEST(TArrayHash, can_insert_record)
{
	TArrayHash tab(10, 3);
    PTDatValue t1 = new TTabRecord();

	tab.InsRecord("Babushkin", t1);

	EXPECT_EQ(tab.FindRecord("Babushkin"), t1);
}

TEST(TArrayHash, can_not_ins_rec_if_tab_full)
{
	TArrayHash tab(3, 2);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

	tab.InsRecord("Babushkin", t1);
	tab.InsRecord("Sazanov", t2);
	tab.InsRecord("Kurakin", t3);
	tab.InsRecord("Sadikov", t3);

	EXPECT_EQ(tab.FindRecord("Sadikov"), nullptr);
}

TEST(TArrayHash, check_empty_after_del_all_rec)
{
	TArrayHash tab(5, 2);
    PTDatValue t1 = new TTabRecord();

	tab.InsRecord("Babushkin", t1);
	tab.InsRecord("Sazanov", t1);
	tab.InsRecord("Kurakin", t1);
	tab.InsRecord("Sadikov", t1);
	tab.InsRecord("Cheloguzov", t1);

	tab.DelRecord("Babushkin");
	tab.DelRecord("Sazanov");
	tab.DelRecord("Kurakin");
	tab.DelRecord("Sadikov");
	tab.DelRecord("Cheloguzov");

	EXPECT_EQ(true, tab.IsEmpty());
}

TEST(TArrayHash, check_full_after_ins_all_rec)
{
	TArrayHash tab(5, 2);
    PTDatValue t1 = new TTabRecord();

	tab.InsRecord("Babushkin", t1);
	tab.InsRecord("Sazanov", t1);
	tab.InsRecord("Kurakin", t1);
	tab.InsRecord("Sadikov", t1);
	tab.InsRecord("Cheloguzov", t1);

	EXPECT_EQ(true, tab.IsFull());
}

TEST(TArrayHash, check_ended_tab)
{
	TArrayHash tab(5, 2);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("Babushkin", t1);
	tab.InsRecord("Sazanov", t1);
	tab.InsRecord("Kurakin", t1);
	tab.InsRecord("Sadikov", t1);
	tab.InsRecord("Cheloguzov", t1);

	tab.Reset();
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();

	EXPECT_EQ(tab.IsTabEnded(), true);
}

//TListHas

TEST(TListHash, can_create_default)
{
	TListHash *tab;

	ASSERT_NO_THROW(tab = new TListHash());
}

TEST(TListHash, can_not_create_with_negative_size)
{
	TListHash *tab;

	ASSERT_ANY_THROW(tab = new TListHash(-5));
}

TEST(TListHash, can_create)
{
	TListHash *tab;

	ASSERT_NO_THROW(tab = new TListHash(5));
}

TEST(TListHash, can_insert_record)
{
	TListHash tab(5);
    PTDatValue t1 = new TTabRecord();

	tab.InsRecord("Sazanov", t1);

	EXPECT_EQ(tab.FindRecord("Sazanov"), t1);
}

TEST(TListHash, can_insert_record_dbl)
{
	TListHash tab(5);
    PTDatValue t1 = new TTabRecord();

	tab.InsRecord("Kurakin", t1);
	tab.InsRecord("Kurakin", t1);

	EXPECT_EQ(TabRecDbl, tab.GetRetCode());
}

TEST(TListHash, can_find_record)
{
	TListHash tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("Babushkin", t1);
	tab.InsRecord("Sokolyuk", t2);

	EXPECT_EQ(tab.FindRecord("Babushkin"), t1);
}

TEST(TListHash, can_delete_record)
{
	TListHash tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("Sazanov", t1);
	tab.InsRecord("Kurakin", t2);

	tab.DelRecord("Sazanov");

	EXPECT_EQ(tab.FindRecord("Sazanov"), nullptr);
}

TEST(TListHash, check_tab_empty_after_del)
{
	TListHash tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("Babushkin", t1);
	tab.InsRecord("Sazanov", t1);
	tab.InsRecord("Kurakin", t1);
	tab.InsRecord("Sadikov", t1);
	tab.InsRecord("Cheloguzov", t1);

	tab.DelRecord("Babushkin");
	tab.DelRecord("Sazanov");
	tab.DelRecord("Kurakin");
	tab.DelRecord("Sadikov");
	tab.DelRecord("Cheloguzov");

	EXPECT_EQ(true, tab.IsEmpty());
}

TEST(TListHash, check_ended_tab)
{
	TListHash tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("Babushkin", t1);
	tab.InsRecord("Sazanov", t1);
	tab.InsRecord("Kurakin", t1);
	tab.InsRecord("Sadikov", t1);
	tab.InsRecord("Cheloguzov", t1);

	tab.Reset();
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();

	EXPECT_EQ(tab.IsTabEnded(), true);

}
