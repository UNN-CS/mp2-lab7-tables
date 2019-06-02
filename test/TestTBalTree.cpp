#include <gtest.h>
#include "TBalTree.h"

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
	tab->Reset();
	tab->GoNext();


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
