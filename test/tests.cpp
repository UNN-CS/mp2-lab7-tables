#include <gtest.h>
#include <iostream>
#include <vector>
#include <map>
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"

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

TEST(TScanTable, can_find)
{
    TScanTable a(4);
    a.InsRecord("lol", nullptr);
    EXPECT_NE(nullptr, a.FindRecord("lol"));
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

TEST(TSortTable, can_create_from_tscantable)
{
    TScanTable a(6);
    a.InsRecord("yyyy", nullptr);
    a.InsRecord("ha", nullptr);
    ASSERT_NO_THROW(TSortTable b(a, QUIQ_SORT));
}

TEST(TSortTable, can_assign_from_tscantable)
{
    TScanTable a(6);
    a.InsRecord("yt", nullptr);
    a.InsRecord("yn", nullptr);
    TSortTable b;
    ASSERT_NO_THROW(b = a);
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
    a.InsRecord("tttt", nullptr);
    a.InsRecord("hhh", nullptr);
    TSortTable b(0);
    b = a;
    EXPECT_NE(nullptr, b.FindRecord("hhh"));
}

TEST(TSortTable, cant_find_if_it_is_not_exist)
{
    TScanTable a(4);
    a.InsRecord("y", nullptr);
    a.InsRecord("e", nullptr);
    TSortTable b(0);
    b = a;
    EXPECT_EQ(nullptr, b.FindRecord("o"));
}

TEST(TSortTable, can_insert)
{
    TScanTable a(4);
    a.InsRecord("u", nullptr);
    a.InsRecord("h", nullptr);
    TSortTable b(0);
    b = a;
    b.InsRecord("y", nullptr);
    EXPECT_NE(nullptr, b.FindRecord("y"));
}

TEST(TSortTable, cant_insert_if_full)
{
    TScanTable a(2);
    a.InsRecord("tttt", nullptr);
    a.InsRecord("hhhh", nullptr);
    TSortTable b(0);
    b = a;
    ASSERT_ANY_THROW(b.InsRecord("y", nullptr));
}

TEST(TSortTable, can_delete)
{
    TScanTable a(2);
    a.InsRecord("aaaa", nullptr);
    a.InsRecord("ss", nullptr);
    TSortTable b(0);
    b = a;
    b.DelRecord("aaaa");
    EXPECT_EQ(nullptr, b.FindRecord("aaaa"));
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

TEST(TTreeTable, can_find_record)
{
    TTreeTable a;
    a.InsRecord("h", nullptr);
    a.InsRecord("t", nullptr);
    EXPECT_NE(nullptr, a.FindRecord("t"));
}

TEST(TTreeTable, can_delete_record)
{
    TTreeTable a;
    a.InsRecord("h", nullptr);
    a.InsRecord("yyy", nullptr);
    a.InsRecord("aaa", nullptr);
    a.DelRecord("h");
    EXPECT_NE(nullptr, a.FindRecord("aaa"));
    EXPECT_NE(nullptr, a.FindRecord("yyy"));
    EXPECT_EQ(nullptr, a.FindRecord("h"));
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

TEST(TTreeTable, can_go_next)
{
    TTreeTable a;
    a.InsRecord("ha", nullptr);
    a.InsRecord("rrr", nullptr);
    a.InsRecord("cok", nullptr);
    a.DelRecord("ha");
    a.Reset();
    a.GoNext();
    EXPECT_TRUE(a.GetKey() == "rrr");
}

TEST(TBalanceTree, can_insert)
{
    TBalanceTree a;
    ASSERT_NO_THROW(a.InsRecord("d", nullptr));
}

TEST(TBalanceTree, can_find)
{
    TBalanceTree a;
    a.InsRecord("d", nullptr);
    EXPECT_NE(nullptr, a.FindRecord("d"));
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

TEST(TArrayHash, can_find)
{
    TArrayHash a(7, 3);
    a.InsRecord("u", nullptr);
    EXPECT_NE(nullptr, a.FindRecord("u"));
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

TEST(TListHash, can_find)
{
    TListHash a(5);
    a.InsRecord("gg", nullptr);
    EXPECT_NE(nullptr, a.FindRecord("gg"));

}

TEST(TListHash, can_delete)
{
    TListHash a(5);
    a.InsRecord("d", nullptr);
    a.DelRecord("d");
    EXPECT_EQ(nullptr, a.FindRecord("d"));
}
