#include "../include/tarrayhash.h"
#include "../gtest/gtest.h"


TEST(TArrayHash, Can_Create_ArrayHash)
{
    ASSERT_NO_THROW(TArrayHash tb(6, 3));
}

TEST(TArrayHash, Can_Insert_Rec)
{
    TArrayHash tb(10, 3);

    tb.InsRecord("sss", PTDatValue(111));

    EXPECT_EQ(tb.GetRetCode(), TabOK);
}

TEST(TArrayHash, Can_Find_Rec)
{
    TArrayHash tb(11, 3);

    tb.InsRecord("f", PTDatValue(14));

    EXPECT_EQ(nullptr, tb.FindRecord("f"));
}

TEST(TArrayHash, Can_Delete)
{
    TArrayHash tb(10, 5);

    tb.InsRecord("h", nullptr);
    tb.DelRecord("h");

    EXPECT_EQ(tb.GetRetCode(), TabNoRec);
}

TEST(TArrayHash, Cant_Find_Missing_Record)
{
    TArrayHash tb(12, 3);

    tb.InsRecord("h", nullptr);
    tb.InsRecord("ss", nullptr);
    tb.InsRecord("23", nullptr);
    tb.InsRecord("qdf", nullptr);
    tb.InsRecord("i", nullptr);
    tb.InsRecord("c", nullptr);
    tb.InsRecord("bj", nullptr);

    tb.FindRecord("p");

    EXPECT_EQ(tb.GetRetCode(), TabNoRec);
}

TEST(TArrayHash, Cant_Ins_In_Full)
{
    TArrayHash tb(7, 3);

    tb.InsRecord("h", nullptr);
    tb.InsRecord("ff", nullptr);
    tb.InsRecord("sda", nullptr);
    tb.InsRecord("q", nullptr);
    tb.InsRecord("czx", nullptr);
    tb.InsRecord("xxx", nullptr);
    tb.InsRecord("zz j1", nullptr);

    tb.InsRecord("px", nullptr);

    EXPECT_EQ(tb.GetRetCode(), TabFull);
}
