#include "../include/tbalancetree.h"
#include "../gtest/gtest.h"


TEST(TBalanceTree, Can_Ins)
{
    TBalanceTree tb;

    tb.InsRecord("a", nullptr);

    EXPECT_EQ(tb.GetRetCode(), TabOK);
}

TEST(TBalanceTree, Can_Find)
{
    TBalanceTree tb;

    tb.InsRecord("a", PTDatValue(12));

    EXPECT_NE((PTDatValue)12, tb.FindRecord("a"));
}

TEST(TBalanceTree, Can_Delete)
{
    TBalanceTree tb;

    tb.InsRecord("c", nullptr);
    tb.DelRecord("c");

    EXPECT_EQ(nullptr, tb.FindRecord("c"));
}
