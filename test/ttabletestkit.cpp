#include <gtest.h>
#include "tscantable.h"
#include "tsorttaable.h"
#include "tword.h"

TEST(TScanTable, can_insert_record) {
    TScanTable t;
    TWord* tw = new TWord("50");
    ASSERT_NO_THROW(t.InsRecord("1", tw));
}

TEST(TScanTable, cant_insert_record_with_existent_key) {
    TScanTable t;
    TWord* tw = new TWord("50");
    TWord* tw1 = new TWord("60");
    t.InsRecord("1", tw);
    ASSERT_ANY_THROW(t.InsRecord("1", tw1));
}

TEST(TScanTable, can_delete_record) {
    TScanTable t;
    TWord* tw = new TWord("50");
    t.InsRecord("1", tw);
    ASSERT_NO_THROW(t.DelRecord("1"));
}

TEST(TScanTable, cant_insert_record_in_full_table) {
    TScanTable t(1);
    TWord* tw = new TWord("50");
    t.InsRecord("1", tw);
    ASSERT_ANY_THROW(t.InsRecord("2", tw));

}

TEST(TScanTable, cant_delete_nonexistent_record) {
    TScanTable t;
    ASSERT_ANY_THROW(t.DelRecord("1"));
}

TEST(TScanTable, can_find_record) {
    TScanTable t;
    TWord* tw = new TWord("50");
    t.InsRecord("1", tw);
    EXPECT_EQ(std::string("50"), ((TWord*)t.FindRecord("1"))->GetWord());
}

TEST(TScanTable, find_record_return_nullptr_with_nonexistent_record) {
    TScanTable t;
    EXPECT_EQ(t.FindRecord("1"), nullptr);
}

TEST(TScanTable, cant_find_record_after_delete) {
    TScanTable t;
    TWord* tw = new TWord("50");
    t.InsRecord("1", tw);
    t.DelRecord("1");
    EXPECT_EQ(t.FindRecord("1"), nullptr);
}
