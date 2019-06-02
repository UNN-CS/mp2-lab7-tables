#include <gtest.h>
#include <iostream>
#include <vector>
#include <map>
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"

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