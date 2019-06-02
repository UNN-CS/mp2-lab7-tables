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