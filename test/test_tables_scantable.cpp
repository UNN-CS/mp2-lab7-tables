#include "../include/tscantable.h"
#include "../gtest/gtest.h"
#include "../include/tdatacom.h"


TEST(TScanTable, Can_Build_Scan_Table) {
    ASSERT_NO_THROW(TScanTable tb(12312));
}

TEST(TScanTable, Can_Insert_Record) {
    TScanTable tb(5);

    tb.InsRecord("1", nullptr);

    EXPECT_EQ(tb.GetRetCode(), TabOK);
}

TEST(TScanTable, Can_Del_Record) {
    TScanTable tb(1);

    tb.InsRecord("1", nullptr);
    tb.DelRecord("1");

    EXPECT_EQ(tb.GetRetCode(), TabOK);
}

TEST(TScanTable, Can_Find_Record) {
    TScanTable tb(1);

    tb.InsRecord("1", nullptr);

    EXPECT_EQ(tb.FindRecord("1"), nullptr);
}
