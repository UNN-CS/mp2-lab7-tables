#include <gtest.h>
#include <iostream>
#include <vector>
#include <map>
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"

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