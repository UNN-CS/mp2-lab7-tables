#include <gtest.h>
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"
#include "TTreeTable.h"

//______________________TScanTable____________________
TEST(TScanTable, can_create)
{
    ASSERT_NO_THROW(TScanTable tab(4));
}

TEST(TScanTable, can_insert)
{
    TScanTable tab(4);
    ASSERT_NO_THROW(tab.InsRecord("angel", nullptr));
}

TEST(TScanTable, cant_add_in_full_table)
{
    TScanTable table(2);
    table.InsRecord("let", nullptr);
    table.InsRecord("my", nullptr);
    ASSERT_ANY_THROW(table.InsRecord("people", nullptr));
}

TEST(TScanTable, can_find)
{
    TScanTable table(4);
    table.InsRecord("road", nullptr);
    EXPECT_NE(nullptr, table.FindRecord("road"));
}

TEST(TScanTable, can_delete)
{
    TScanTable table(4);
    table.InsRecord("road", nullptr);
    table.DelRecord("road");
    EXPECT_EQ(0, table.GetDataCount());
}

TEST(TScanTable, cant_find_after_delete)
{
    TScanTable t;
    TScanTable table(4);
    table.InsRecord("road", nullptr);
    table.DelRecord("road");
    EXPECT_EQ(t.FindRecord("road"), nullptr);
}

//___________________________TSortTable_____________________
TEST(TSortTable, can_create)
{
    ASSERT_NO_THROW(TSortTable table(4));
}

TEST(TSortTable, can_create_from_tscantable)
{
    TScanTable table(4);
    table.InsRecord("road", nullptr);
    table.InsRecord("to", nullptr);
    table.InsRecord("hell", nullptr);
    ASSERT_NO_THROW(TSortTable sorttable(table, QUICK_SORT));
}

TEST(TSortTable, can_assign_from_tscantable)
{
    TScanTable table(4);
	table.InsRecord("road", nullptr);
	table.InsRecord("to", nullptr);
	table.InsRecord("hell", nullptr);
    TSortTable tab;
    ASSERT_NO_THROW(tab = table);
}

TEST(TSortTable, can_find)
{
    TScanTable table(4);
    table.InsRecord("road", nullptr);
    table.InsRecord("to", nullptr);
    table.InsRecord("hell", nullptr);
    TSortTable tab(0);
    tab = table;
    EXPECT_NE(nullptr, tab.FindRecord("hell"));
}

TEST(TSortTable, can_insert)
{
    TScanTable table(4);
	table.InsRecord("smbdody", nullptr);
	table.InsRecord("usedtoknow", nullptr);
    TSortTable tab(0);
    tab = table;
    tab.InsRecord("usedtoknow", nullptr);
    EXPECT_NE(nullptr, tab.FindRecord("usedtoknow"));
}

TEST(TSortTable, cant_insert_in_full)
{
    TScanTable table(2);
    table.InsRecord("road", nullptr);
    table.InsRecord("to", nullptr);
    TSortTable tab(0);
    tab = table;
    ASSERT_ANY_THROW(tab.InsRecord("hell", nullptr));
}

TEST(TSortTable, can_delete)
{
    TScanTable table(2);
    table.InsRecord("midnight", nullptr);
    table.InsRecord("city", nullptr);
    TSortTable tab(0);
    tab = table;
    tab.DelRecord("city");
    EXPECT_EQ(nullptr, tab.FindRecord("city"));
}

//___________________________TTreeTable______________________________
TEST(TTreeTable, can_create)
{
    ASSERT_NO_THROW(TTreeTable tree);
}

TEST(TTreeTable, can_insert)
{
    TTreeTable tree;
    ASSERT_NO_THROW(tree.InsRecord("whatscookinggoodlooking", nullptr));
}

TEST(TTreeTable, can_find)
{
    TTreeTable tree;
    tree.InsRecord("midnight", nullptr);
    tree.InsRecord("city", nullptr);
    EXPECT_NE(nullptr, tree.FindRecord("city"));
}

TEST(TTreeTable, can_delete)
{
    TTreeTable tree;
    tree.InsRecord("road", nullptr);
    tree.InsRecord("to", nullptr);
    tree.InsRecord("hell", nullptr);
    tree.DelRecord("road");
    EXPECT_NE(nullptr, tree.FindRecord("to"));
    EXPECT_NE(nullptr, tree.FindRecord("hell"));
    EXPECT_EQ(nullptr, tree.FindRecord("road"));
}

TEST(TTreeTable, can_delete_if_no_record)
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

//________________________TBalanceTree________________________
TEST(TBalanceTree, can_insert)
{
    TBalanceTree tree;
    ASSERT_NO_THROW(tree.InsRecord("whatscookinggoodlooking", nullptr));
}

TEST(TBalanceTree, can_find)
{
    TBalanceTree tree;
    tree.InsRecord("whatscookinggoodlooking", nullptr);
    EXPECT_NE(nullptr, tree.FindRecord("whatscookinggoodlooking"));
}

TEST(TBalanceTree, can_delete)
{
    TBalanceTree tree;
    tree.InsRecord("heyhowudoing", nullptr);
    tree.DelRecord("heyhowudoing");
    EXPECT_EQ(nullptr, tree.FindRecord("heyhowudoing"));
}

//________________TArrayHash_______________________
TEST(TArrayHash, can_insert)
{
    TArrayHash ah(7, 3);
    ASSERT_NO_THROW(ah.InsRecord("heyhowudoing", nullptr));
}

TEST(TArrayHash, can_delete)
{
    TArrayHash ah(8, 7);
    ah.InsRecord("heyhowudoing", nullptr);
    ah.DelRecord("heyhowudoing");
    EXPECT_EQ(nullptr, ah.FindRecord("heyhowudoing"));
}

TEST(TArrayHash, can_find)
{
	TArrayHash ah(8, 7);
	ah.InsRecord("arr", nullptr);
	EXPECT_NE(nullptr, ah.FindRecord("arr"));
}


//__________________TListHash________________________
TEST(TListHash, can_insert)
{
    TListHash lh(5);
    ASSERT_NO_THROW(lh.InsRecord("hello", nullptr));
}

TEST(TListHash, can_find)
{
    TListHash lh(5);
    lh.InsRecord("hello", nullptr);
    EXPECT_NE(nullptr, lh.FindRecord("hello"));

}

TEST(TListHash, can_delete)
{
    TListHash lh(5);
    lh.InsRecord("hello", nullptr);
    lh.DelRecord("hello");
    EXPECT_EQ(nullptr, lh.FindRecord("hello"));
}

