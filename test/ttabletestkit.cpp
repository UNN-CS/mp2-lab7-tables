#include <gtest.h>
#include "tscantable.h"
#include "tsorttaable.h"
#include "tword.h"

TEST(TScanTable, can_insert_record) {
    TScanTable t;
    TWord* tw = new TWord("50");
    ASSERT_NO_THROW(t.InsRecord("1", tw));
    delete tw;
}

TEST(TScanTable, cant_insert_record_with_existent_key) {
    TScanTable t;
    TWord* tw = new TWord("50");
    TWord* tw1 = new TWord("60");
    t.InsRecord("1", tw);
    ASSERT_ANY_THROW(t.InsRecord("1", tw1));
    delete tw;
    delete tw1;
}

TEST(TScanTable, can_delete_record) {
    TScanTable t;
    TWord* tw = new TWord("50");
    t.InsRecord("1", tw);
    ASSERT_NO_THROW(t.DelRecord("1"));
    delete tw;
}

TEST(TScanTable, cant_insert_record_in_full_table) {
    TScanTable t(1);
    TWord* tw = new TWord("50");
    t.InsRecord("1", tw);
    ASSERT_ANY_THROW(t.InsRecord("2", tw));
    delete tw;
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
    delete tw;
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
    delete tw;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TEST(TSortTable, can_insert_record) {
    TSortTable t;
    TWord* tw = new TWord("50");
    t.InsRecord("1", tw);
    //ASSERT_NO_THROW(t.InsRecord("1", tw));
    delete tw;
}

TEST(TSortTable, cant_insert_record_with_existent_key) {
    TSortTable t;
    TWord* tw = new TWord("50");
    TWord* tw1 = new TWord("60");
    t.InsRecord("1", tw);
    ASSERT_ANY_THROW(t.InsRecord("1", tw1));
    delete tw;
    delete tw1;
}

TEST(TSortTable, can_delete_record) {
    TSortTable t;
    TWord* tw = new TWord("50");
    t.InsRecord("1", tw);
    ASSERT_NO_THROW(t.DelRecord("1"));
    delete tw;
}

TEST(TSortTable, cant_insert_record_in_full_table) {
    TSortTable t(1);
    TWord* tw = new TWord("50");
    t.InsRecord("1", tw);
    ASSERT_ANY_THROW(t.InsRecord("2", tw));
    delete tw;
}

TEST(TSortTable, cant_delete_nonexistent_record) {
    TSortTable t;
    ASSERT_ANY_THROW(t.DelRecord("1"));
}

TEST(TSortTable, can_find_record) {
    TSortTable t;
    TWord* tw1 = new TWord("20");
    TWord* tw2 = new TWord("30");
    TWord* tw3 = new TWord("40");
    TWord* tw4 = new TWord("50");
    TWord* tw5 = new TWord("60");
    t.InsRecord("5", tw5);
    t.InsRecord("3", tw3);
    t.InsRecord("4", tw4);
    t.InsRecord("1", tw1);
    t.InsRecord("2", tw2);
    EXPECT_EQ(std::string("30"), ((TWord*)t.FindRecord("2"))->GetWord());
    delete tw1;
    delete tw2;
    delete tw3;
    delete tw4;
    delete tw5;
}

TEST(TSortTable, find_record_return_nullptr_with_nonexistent_record) {
    TSortTable t;
    EXPECT_EQ(t.FindRecord("1"), nullptr);
}

TEST(TSortTable, cant_find_record_after_delete) {
    TSortTable t;
    TWord* tw = new TWord("50");
    t.InsRecord("1", tw);
    t.DelRecord("1");
    EXPECT_EQ(t.FindRecord("1"), nullptr);
    delete tw;
}

TEST(TSortTable, can_cast_scantable_to_sorttable) {
    TSortTable t;
    TScanTable t1;
    TWord* tw = new TWord("50");
    t1.InsRecord("1", tw);
    ASSERT_NO_THROW(t = t1);
    EXPECT_EQ(std::string("50"), ((TWord*)t.FindRecord("1"))->GetWord());
    delete tw;
}

TEST(TSortTable, insert_sort_works_correct) {
    TSortTable t;
    t.SetSortMethod(INSERT_SORT);
    TWord* tw = new TWord("20");
    t.InsRecord("5", tw);
    t.InsRecord("4", tw);
    t.InsRecord("6", tw);
    t.InsRecord("3", tw);
    t.InsRecord("2", tw);
    t.InsRecord("1", tw);
    EXPECT_EQ("1 2 3 4 5 6 ", t.KeysToStr());
    delete tw;
}

TEST(TSortTable, merge_sort_works_correct) {
    TSortTable t;
    t.SetSortMethod(MERGE_SORT);
    TWord* tw = new TWord("20");
    t.InsRecord("5", tw);
    t.InsRecord("4", tw);
    t.InsRecord("6", tw);
    t.InsRecord("3", tw);
    t.InsRecord("2", tw);
    t.InsRecord("1", tw);
    EXPECT_EQ("1 2 3 4 5 6 ", t.KeysToStr());
    delete tw;
}

TEST(TSortTable, quick_sort_works_correct) {
    TSortTable t;
    t.SetSortMethod(QUICK_SORT);
   TWord* tw = new TWord("20");
    t.InsRecord("5", tw);
    t.InsRecord("4", tw);
    t.InsRecord("6", tw);
    t.InsRecord("3", tw);
    t.InsRecord("2", tw);
    t.InsRecord("1", tw);
    EXPECT_EQ("1 2 3 4 5 6 ", t.KeysToStr());
    delete tw;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
