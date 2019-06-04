#include <gtest.h>
#include <iostream>
#include <vector>
#include <map>
#include "tsorttable.h"
#include "ttreetable.h"
#include "tbalancetree.h"
#include "tarrayhash.h"
#include "tlisthash.h"

TEST(TScanTable, can_create)
{
	ASSERT_NO_THROW(TScanTable tab(4));
}

TEST(TScanTable, can_use_is_full)
{
	TScanTable tab(4);
	EXPECT_EQ(0, tab.IsFull());
}

TEST(TScanTable, can_use_is_empty)
{
	TScanTable tab(4);
	EXPECT_EQ(1, tab.IsEmpty());
}

TEST(TScanTable, can_get_efficienty)
{
	TScanTable tab(6);
	EXPECT_EQ(0, tab.GetEfficiency());
}

TEST(TScanTable, can_get_data_count)
{
	TScanTable tab(6);
	EXPECT_EQ(0, tab.GetDataCount());
}

TEST(TScanTable, can_insert)
{
	TScanTable tab(4);
	ASSERT_NO_THROW(tab.InsRecord("kek", nullptr));
}

TEST(TScanTable, can_delete)
{
	TScanTable a(6);
	a.InsRecord("ss", nullptr);
	a.DelRecord("ss");
	EXPECT_EQ(0, a.GetDataCount());
}

TEST(TScanTable, data_count_can_be_increased)
{
	TScanTable a(6);
	a.InsRecord("t", nullptr);
	EXPECT_EQ(1, a.GetDataCount());
}

TEST(TScanTable, can_get_key)
{
	TScanTable a(6);
	a.InsRecord("yes", nullptr);
	EXPECT_EQ("yes", a.GetKey());
}

TEST(TScanTable, can_get_tab_size)
{
	TScanTable a(8);
	EXPECT_EQ(8, a.GetTabSize());
}

TEST(TScanTable, cant_add_in_full_tab)
{
	TScanTable a(3);
	a.InsRecord("gg", nullptr);
	a.InsRecord("pp", nullptr);
	a.InsRecord("kj", nullptr);
	ASSERT_ANY_THROW(a.InsRecord("u", nullptr));
}

TEST(TScanTable, can_reset)
{
	TScanTable a(5);
	a.InsRecord("t", nullptr);
	a.InsRecord("yu", nullptr);
	a.GoNext();
	a.Reset();
	EXPECT_EQ("t", a.GetKey());
}

TEST(TScanTable, can_check_if_tab_ended)
{
	TScanTable a(4);
	EXPECT_EQ(1, a.IsTabEnded());
}

TEST(TScanTable, can_go_next)
{
	TScanTable a(6);
	a.InsRecord("tt", nullptr);
	a.InsRecord("e", nullptr);
	a.GoNext();
	EXPECT_EQ("e", a.GetKey());
}

TEST(TSortTable, can_create)
{
	ASSERT_NO_THROW(TSortTable t(2));
}

TEST(TSortTable, can_set_sort_method)
{
	TSortTable b;
	b.SetSortMethod(TSortMethod::INSERT_SORT);
	EXPECT_EQ(TSortMethod::INSERT_SORT, b.GetSortMethod());
}

TEST(TTreeTable, can_create_object)
{
	ASSERT_NO_THROW(TTreeTable a);
}

TEST(TTreeTable, can_insert_record)
{
	TTreeTable a;
	ASSERT_NO_THROW(a.InsRecord("h", nullptr));
}

TEST(TTreeTable, can_reset)
{
	TTreeTable a;
	a.InsRecord("u", nullptr);
	a.InsRecord("r", nullptr);
	a.InsRecord("w", nullptr);
	a.DelRecord("u");
	ASSERT_NO_THROW(a.Reset());
}

TEST(TBalanceTree, can_insert)
{
	TBalanceTree a;
	ASSERT_NO_THROW(a.InsRecord("d", nullptr));
}

TEST(TBalanceTree, can_delete)
{
	TBalanceTree a;
	a.InsRecord("d", nullptr);
	a.DelRecord("d");
	EXPECT_EQ(nullptr, a.FindRecord("d"));
}

TEST(TArrayHash, can_insert)
{
	TArrayHash a(7, 3);
	ASSERT_NO_THROW(a.InsRecord("y", nullptr));
}

TEST(TArrayHash, can_delete)
{
	TArrayHash a(7, 3);
	a.InsRecord("eee", nullptr);
	a.DelRecord("eee");
	EXPECT_EQ(nullptr, a.FindRecord("eee"));
}

TEST(TListHash, can_insert)
{
	TListHash a(5);
	ASSERT_NO_THROW(a.InsRecord("gg", nullptr));
}

TEST(TListHash, can_delete)
{
	TListHash a(5);
	a.InsRecord("d", nullptr);
	a.DelRecord("d");
	EXPECT_EQ(nullptr, a.FindRecord("d"));
}