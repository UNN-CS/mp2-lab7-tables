#include <gtest.h>
#include <iostream>
#include <vector>
#include <map>
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"

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