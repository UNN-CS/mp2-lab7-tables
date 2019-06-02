#include <gtest.h>
#include <iostream>
#include <vector>
#include <map>
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"

TEST(TScanTable, can_create_scan_table)
{
	ASSERT_NO_THROW(TScanTable t(5));
}

TEST(TScanTable, can_check_full)
{
	TScanTable t(5);
	EXPECT_EQ(0, t.IsFull());
}

TEST(TScanTable, can_check_empty)
{
	TScanTable t(5);
	EXPECT_EQ(1, t.IsEmpty());
}

TEST(TScanTable, can_get_efficienty)
{
	TScanTable t(5);
	EXPECT_EQ(0, t.GetEfficiency());
}

TEST(TScanTable, can_get_data_count)
{
	TScanTable t(5);
	EXPECT_EQ(0, t.GetDataCount());
}

TEST(TScanTable, can_insert)
{
	TScanTable t(5);
	ASSERT_NO_THROW(t.InsRecord("aaa", nullptr));
}

TEST(TScanTable, can_find)
{
	TScanTable a(4);
	a.InsRecord("aaa", nullptr);
	EXPECT_NE(nullptr, a.FindRecord("aaa"));
}

TEST(TScanTable, can_delete)
{
	TScanTable a(6);
	a.InsRecord("aaa", nullptr);
	a.DelRecord("aaa");
	EXPECT_EQ(0, a.GetDataCount());
}

TEST(TScanTable, data_count_is_increased_after_insert)
{
	TScanTable a(6);
	a.InsRecord("a", nullptr);
	EXPECT_EQ(1, a.GetDataCount());
}

TEST(TScanTable, data_count_is_decreased_after_delete)
{
	TScanTable a(6);
	a.InsRecord("a", nullptr);
	a.DelRecord("a");
	EXPECT_EQ(0, a.GetDataCount());
}

TEST(TScanTable, can_get_key)
{
	TScanTable a(6);
	a.InsRecord("aaa", nullptr);
	EXPECT_EQ("aaa", a.GetKey());
}

TEST(TScanTable, can_get_tab_size)
{
	TScanTable a(5);
	EXPECT_EQ(5, a.GetTabSize());
}

TEST(TScanTable, cant_add_in_full_tab)
{
	TScanTable a(3);
	a.InsRecord("gg", nullptr);
	a.InsRecord("pp", nullptr);
	a.InsRecord("kj", nullptr);
	ASSERT_ANY_THROW(a.InsRecord("u", nullptr));
}

TEST(TScanTable, can_go_next)
{
	TScanTable a(6);
	a.InsRecord("tt", nullptr);
	a.InsRecord("e", nullptr);
	a.GoNext();
	EXPECT_EQ("e", a.GetKey());
}

TEST(TSortTable, can_create_sort_table)
{
	ASSERT_NO_THROW(TSortTable t(5));
}

TEST(TSortTable, can_get_sort_method)
{
	TSortTable b;
	EXPECT_EQ(TSortMethod::QUIQ_SORT, b.GetSortMethod());
}

TEST(TSortTable, can_set_sort_method)
{
	TSortTable b;
	b.SetSortMethod(TSortMethod::INSERT_SORT);
	EXPECT_EQ(TSortMethod::INSERT_SORT, b.GetSortMethod());
}

TEST(TSortTable, can_find_value)
{
	TScanTable a(6);
	a.InsRecord("aaa", nullptr);
	a.InsRecord("bbb", nullptr);
	a.InsRecord("ccc", nullptr);
	EXPECT_NE(nullptr, a.FindRecord("bbb"));
}

TEST(TSortTable, can_insert)
{
	TScanTable a(5);
	a.InsRecord("a", nullptr);
	a.InsRecord("b", nullptr);
	a.InsRecord("c", nullptr);
	EXPECT_NE(nullptr, a.FindRecord("c"));
}

TEST(TSortTable, cant_insert_if_full)
{
	TScanTable a(2);
	a.InsRecord("aaaaaa", nullptr);
	a.InsRecord("a", nullptr);
	ASSERT_ANY_THROW(a.InsRecord("b", nullptr));
}

TEST(TSortTable, can_delete)
{
	TScanTable a(2);
	a.InsRecord("aaaaaa", nullptr);
	a.InsRecord("bbbb", nullptr);
	a.DelRecord("aaaaaa");
	EXPECT_EQ(nullptr, a.FindRecord("aaaaaa"));
}

TEST(TTreeTable, can_create_tree_table)
{
	ASSERT_NO_THROW(TTreeTable a);
}

TEST(TTreeTable, can_insert_record)
{
	TTreeTable a;
	ASSERT_NO_THROW(a.InsRecord("aaa", nullptr));
}

TEST(TTreeTable, can_find_record)
{
	TTreeTable a;
	a.InsRecord("aaa", nullptr);
	a.InsRecord("bbb", nullptr);
	EXPECT_NE(nullptr, a.FindRecord("aaa"));
}

TEST(TTreeTable, can_delete_record)
{
	TTreeTable a;
	a.InsRecord("a", nullptr);
	a.InsRecord("aa", nullptr);
	a.InsRecord("aaa", nullptr);
	a.DelRecord("aa");
	EXPECT_NE(nullptr, a.FindRecord("a"));
	EXPECT_NE(nullptr, a.FindRecord("aaa"));
	EXPECT_EQ(nullptr, a.FindRecord("aa"));
}

TEST(TTreeTable, can_reset)
{
	TTreeTable a;
	a.InsRecord("aaa", nullptr);
	a.InsRecord("bbb", nullptr);
	ASSERT_NO_THROW(a.Reset());
}

TEST(TTreeTable, can_go_next)
{
	TTreeTable a;
	a.InsRecord("1", nullptr);
	a.InsRecord("2", nullptr);
	a.InsRecord("3", nullptr);
	a.Reset();
	a.GoNext();
	EXPECT_TRUE(a.GetKey() == "2");
}

TEST(TBalanceTree, can_create_balance_tree)
{
	TBalanceTree a;
	ASSERT_NO_THROW(a.InsRecord("123", nullptr));
}

TEST(TBalanceTree, can_insert)
{
	TBalanceTree a;
	ASSERT_NO_THROW(a.InsRecord("g", nullptr));
}

TEST(TBalanceTree, can_find)
{
	TBalanceTree a;
	a.InsRecord("111", nullptr);
	EXPECT_NE(nullptr, a.FindRecord("111"));
}

TEST(TBalanceTree, can_delete)
{
	TBalanceTree a;
	a.InsRecord("aaa", nullptr);
	a.DelRecord("aaa");
	EXPECT_EQ(nullptr, a.FindRecord("aaa"));
}

TEST(TArrayHash, can_create_array_hash)
{
	ASSERT_NO_THROW(TArrayHash a(10, 3));
}

TEST(TArrayHash, can_insert)
{
	TArrayHash a(8, 4);
	ASSERT_NO_THROW(a.InsRecord("2", nullptr));
}

TEST(TArrayHash, can_find)
{
	TArrayHash a(8, 4);
	a.InsRecord("123", nullptr);
	EXPECT_NE(nullptr, a.FindRecord("123"));
}

TEST(TArrayHash, can_delete)
{
	TArrayHash a(8, 4);
	a.InsRecord("123", nullptr);
	a.DelRecord("123");
	EXPECT_EQ(nullptr, a.FindRecord("123"));
}

TEST(TListHash, can_insert)
{
	TListHash a(7);
	ASSERT_NO_THROW(a.InsRecord("help", nullptr));
}

TEST(TListHash, can_find)
{
	TListHash a(5);
	a.InsRecord("123", nullptr);
	EXPECT_NE(nullptr, a.FindRecord("123"));

}

TEST(TListHash, can_delete)
{
	TListHash a(5);
	a.InsRecord("a", nullptr);
	a.DelRecord("a");
	EXPECT_EQ(nullptr, a.FindRecord("a"));
}