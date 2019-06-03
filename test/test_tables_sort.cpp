#include "../include/tsorttable.h"
#include "../gtest/gtest.h"


TEST(TSortTable, Can_Create_Sort)
{
    TSortTable tb(2);

    EXPECT_EQ(tb.GetRetCode(), TabOK);
}

TEST(TSortTable, Can_Create_From_TScanTable)
{
    TScanTable tb(6);

    tb.InsRecord("a", nullptr);
    tb.InsRecord("b", nullptr);

    ASSERT_NO_THROW(TSortTable f(tb));
}

TEST(TSortTable, Can_Go_Next)
{
    TScanTable tb(3);

    tb.InsRecord("a", nullptr);
    tb.InsRecord("b", nullptr);

    tb.GoNext();

    EXPECT_EQ("b", tb.GetKey());
}

TEST(TSortTable, Can_Assign_From_TScanTable)
{
    TScanTable tb(6);

    tb.InsRecord("a", nullptr);
    tb.InsRecord("b", nullptr);

    TSortTable f;

    ASSERT_NO_THROW(f = tb);
}

TEST(TSortTable, can_get_sort_method)
{
    TSortTable tb;
    tb.SetSortMethod(TSortMethod::INSERT_SORT);
    EXPECT_EQ(TSortMethod::INSERT_SORT, tb.GetSortMethod());
}

TEST(TSortTable, can_set_sort_method)
{
    TSortTable tb;
    tb.SetSortMethod(TSortMethod::INSERT_SORT);
    EXPECT_EQ(TSortMethod::INSERT_SORT, tb.GetSortMethod());
}
