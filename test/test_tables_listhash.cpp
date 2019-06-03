#include "../include/tlisthash.h"
#include "../gtest/gtest.h"


TEST(TListHash, Can_Create_ListHash)
{
    TListHash tb(5);

    EXPECT_EQ(tb.GetRetCode(), TabOK);
}

TEST(TListHash, Can_Insert)
{
    TListHash tb(5);

    tb.InsRecord("s", nullptr);

    EXPECT_EQ(tb.GetRetCode(), TabOK);
}

TEST(TListHash, Can_Find)
{
    TListHash tb(5);

    tb.InsRecord("s", PTDatValue(144));

    EXPECT_EQ((PTDatValue)144, tb.FindRecord("s"));
}

TEST(TListHash, Can_Del)
{
    TListHash tb(5);

    tb.InsRecord("s", nullptr);
    tb.DelRecord("s");

    tb.FindRecord("s");

    EXPECT_EQ(tb.GetRetCode(), TabNoRec);
}
