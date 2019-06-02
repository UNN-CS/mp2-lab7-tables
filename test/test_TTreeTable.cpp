#include <gtest.h>
#include <iostream>
#include <vector>
#include <map>
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"

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