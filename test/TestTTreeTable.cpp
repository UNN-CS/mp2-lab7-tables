#include <gtest.h>
#include "TTreeTab.h"


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
    tab->Reset();
    tab->GoNext();
    tab->GoNext();
    tab->GoNext();
    tab->GoNext();

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
	tab->Reset();
	tab->GoNext();
	tab->GoNext();
	tab->GoNext();
	tab->GoNext();
	tab->GoNext();

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
