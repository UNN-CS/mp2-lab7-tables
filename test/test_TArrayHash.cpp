#include <gtest.h>
#include <iostream>
#include <vector>
#include <map>
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"

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