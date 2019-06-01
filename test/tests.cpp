#include <gtest.h>

#include <iostream>
#include <vector>
#include <string>
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"

TEST(TScanTable, can_create_obj)
{
    ASSERT_NO_THROW(TScanTable tmp(4));
}

TEST(TScanTable, can_detect_if_full)
{
    TScanTable tmp(4);
    EXPECT_EQ(0, tmp.IsFull());
}

TEST(TScanTable, can_detect_if_empty)
{
    TScanTable tmp(4);
    EXPECT_EQ(1, tmp.IsEmpty());
}

TEST(TScanTable, can_get_efficienty)
{
    TScanTable tmp(4);
    EXPECT_EQ(0, tmp.GetEfficiency());
}

TEST(TScanTable, can_get_data_count)
{
    TScanTable tmp(4);
    EXPECT_EQ(0, tmp.GetDataCount());
}

TEST(TScanTable, can_insert_record)
{
    TScanTable tmp(4);
    ASSERT_NO_THROW(tmp.InsRecord("w", nullptr));
}

TEST(TScanTable, can_find_value)
{
    TScanTable tmp(4);
    tmp.InsRecord("w", nullptr);
    EXPECT_NE(nullptr, tmp.FindRecord("w"));
}

TEST(TScanTable, can_delete_record)
{
    TScanTable tmp(4);
    tmp.InsRecord("w", nullptr);
    tmp.DelRecord("w");
    EXPECT_EQ(0, tmp.GetDataCount());
}

TEST(TScanTable, can_get_dataCount)
{
    TScanTable tmp(4);
    tmp.InsRecord("h", nullptr);
    EXPECT_EQ(1, tmp.GetDataCount());
}

TEST(TScanTable, can_get_key)
{
    TScanTable tmp(4);
    tmp.InsRecord("w", nullptr);
    EXPECT_EQ("w", tmp.GetKey());
}

TEST(TScanTable, can_get_value_ptr)
{
    TScanTable tmp(3);
    tmp.InsRecord("h", (PTDatValue)32);
    EXPECT_EQ((PTDatValue)32, tmp.GetValuePTR());
}

TEST(TScanTable, can_get_tab_size)
{
    TScanTable tmp(4);
    EXPECT_EQ(4, tmp.GetTabSize());
}

TEST(TScanTable, cant_insert_and_detect_tab_is_full)
{
    TScanTable tmp(2);
    tmp.InsRecord("w", nullptr);
    tmp.InsRecord("z", nullptr);
    ASSERT_ANY_THROW(tmp.InsRecord("v", nullptr));
}

TEST(TScanTable, can_reset)
{
    TScanTable tmp(3);
    tmp.InsRecord("w", nullptr);
    tmp.InsRecord("v", nullptr);
    tmp.GoNext();
    tmp.Reset();
    EXPECT_EQ("w", tmp.GetKey());
}

TEST(TScanTable, can_detect_if_tab_ended)
{
    TScanTable tmp(3);
    EXPECT_EQ(1, tmp.IsTabEnded());
}

TEST(TScanTable, can_go_next)
{
    TScanTable tmp(3);
    tmp.InsRecord("aa", nullptr);
    tmp.InsRecord("b", nullptr);
    tmp.GoNext();
    EXPECT_EQ("b", tmp.GetKey());
}

TEST(TSortTable, can_create_obj)
{
    ASSERT_NO_THROW(TSortTable tmp(2));
}

TEST(TSortTable, can_create_from_tscantable)
{
    TScanTable tmp(6);
    tmp.InsRecord("a", nullptr);
    tmp.InsRecord("b", nullptr);
    ASSERT_NO_THROW(TSortTable f(tmp));
}
TEST(TSortTable, can_go_next)
{
    TScanTable tmp(3);
    tmp.InsRecord("a", nullptr);
    tmp.InsRecord("b", nullptr);
    tmp.GoNext();
    EXPECT_EQ("b", tmp.GetKey());
}

TEST(TSortTable, can_assign_from_tscantable)
{
    TScanTable tmp(6);
    tmp.InsRecord("a", nullptr);
    tmp.InsRecord("b", nullptr);
    TSortTable f;
    ASSERT_NO_THROW(f = tmp);
}

TEST(TSortTable, can_get_sort_method)
{
    TSortTable tmp;
    tmp.SetSortMethod(TSortMethod::INSERT_SORT);
    EXPECT_EQ(TSortMethod::INSERT_SORT, tmp.GetSortMethod());
}

TEST(TSortTable, can_set_sort_method)
{
    TSortTable tmp;
    tmp.SetSortMethod(TSortMethod::INSERT_SORT);
    EXPECT_EQ(TSortMethod::INSERT_SORT, tmp.GetSortMethod());
}

class SortTestTSortTable: public ::testing::Test
{
    protected:
    void check_sort(TSortMethod sm)
    {
        TSortTable b(0);
        string s[] = {"1", "2", "3", "4", "5", "6"};
        b.SetSortMethod(sm);
        TScanTable a(6);
        a.InsRecord("1", nullptr);
        a.InsRecord("3", nullptr);
        a.InsRecord("5", nullptr);
        a.InsRecord("6", nullptr);
        a.InsRecord("4", nullptr);
        a.InsRecord("2", nullptr);
        b = a;
        b.Reset();
        for (int i = 0; i < 6; ++i)
        {
            EXPECT_TRUE(s[i] == b.GetKey());
            b.GoNext();
        }
    }
};

TEST_F(SortTestTSortTable, quick_sort_is_correct)
{
    check_sort(TSortMethod::QUICK_SORT);
}

TEST_F(SortTestTSortTable, merge_sort_is_correct)
{
    check_sort(TSortMethod::MERGE_SORT);
}

TEST_F(SortTestTSortTable, insert_sort_is_correct)
{
    check_sort(TSortMethod::INSERT_SORT);
}

TEST(TSortTable, can_find_value)
{
    string str;
    PTDatValue b = PTDatValue(&str);
    TScanTable t1(6);
    t1.InsRecord("tmp", nullptr);
    t1.InsRecord("tss", b);
    TSortTable t2(0);
    t2 = t1;
    EXPECT_NE(nullptr, t2.FindRecord("tss"));
}

TEST(TSortTable, cant_find_missing_value)
{
    TScanTable tmp(6);
    tmp.InsRecord("b", nullptr);
    tmp.InsRecord("c", nullptr);
    TSortTable f(0);
    f = tmp;
    EXPECT_EQ(nullptr, f.FindRecord("os"));
}

TEST(TSortTable, can_insert)
{
    TSortTable tmp(2);
    ASSERT_NO_THROW(tmp.InsRecord("hh", nullptr));
}

TEST(TSortTable, cant_insert_if_full)
{
    TScanTable tmp(2);
    tmp.InsRecord("aa", nullptr);
    tmp.InsRecord("b", nullptr);
    TSortTable f(0);
    f = tmp;
    ASSERT_ANY_THROW(f.InsRecord("y", nullptr));
}

TEST(TSortTable, can_delete_record)
{
    TScanTable tmp(2);
    tmp.InsRecord("ss", nullptr);
    tmp.InsRecord("aa", nullptr);
    TSortTable f(0);
    f = tmp;
    f.DelRecord("aa");
    EXPECT_EQ(nullptr, f.FindRecord("aa"));
}

TEST(TTreeTable, can_create_obj)
{
    ASSERT_NO_THROW(TTreeTable tmp);
}

TEST(TTreeTable, can_insert_record)
{
    TTreeTable tmp;
    ASSERT_NO_THROW(tmp.InsRecord("ff", nullptr));
}

TEST(TTreeTable, can_find_record)
{
    TTreeTable tmp;
    tmp.InsRecord("z", nullptr);
    tmp.InsRecord("y", (PTDatValue)30);
    EXPECT_NE(nullptr, tmp.FindRecord("y"));
}

TEST(TTreeTable, can_delete_record)
{
    TTreeTable tmp;
    tmp.InsRecord("x", (PTDatValue)13);
    tmp.InsRecord("z", nullptr);
    tmp.DelRecord("z");
    EXPECT_NE(nullptr, tmp.FindRecord("x"));
    EXPECT_EQ(nullptr, tmp.FindRecord("z"));
}

TEST(TTreeTable, can_reset)
{
    TTreeTable tmp;
    tmp.InsRecord("y", nullptr);
    tmp.InsRecord("z", nullptr);
    tmp.DelRecord("y");
    ASSERT_NO_THROW(tmp.Reset());
}

TEST(TTreeTable, can_go_next)
{
    TTreeTable tmp;
    tmp.InsRecord("a", nullptr);
    tmp.InsRecord("b", nullptr);
    tmp.InsRecord("c", nullptr);
    tmp.Reset();
    tmp.GoNext();
    EXPECT_TRUE(tmp.GetKey() == "b");
}

TEST(TTreeTable, can_detect_if_ended)
{
    TTreeTable tmp;
    tmp.InsRecord("a", nullptr);
    tmp.InsRecord("b", nullptr);
    tmp.InsRecord("c", nullptr);
    tmp.DelRecord("a");
    tmp.Reset();
    tmp.GoNext();
    tmp.GoNext();
    EXPECT_TRUE(tmp.IsTabEnded());
}

TEST(TBalanceTree, can_insert)
{
    TBalanceTree tmp;
    ASSERT_NO_THROW(tmp.InsRecord("a", nullptr));
}

TEST(TBalanceTree, can_find)
{
    TBalanceTree tmp;
    tmp.InsRecord("a", PTDatValue(12));
    EXPECT_NE(nullptr, tmp.FindRecord("a"));
}

TEST(TBalanceTree, can_delete)
{
    TBalanceTree tmp;
    tmp.InsRecord("c", nullptr);
    tmp.DelRecord("c");
    EXPECT_EQ(nullptr, tmp.FindRecord("c"));
}

TEST(TBalanceTree, can_find_many_records)
{
    TBalanceTree tmp;
    tmp.InsRecord("f", nullptr);
    tmp.InsRecord("b", nullptr);
    tmp.InsRecord("c", (PTDatValue)12);
    tmp.InsRecord("d", (PTDatValue)11);
    tmp.InsRecord("e", nullptr);
    tmp.DelRecord("f");
    EXPECT_NE(nullptr, tmp.FindRecord("c"));
    EXPECT_NE(nullptr, tmp.FindRecord("d"));
}

TEST(TBalanceTree, delete_many_records)
{
    TBalanceTree tmp;
    tmp.InsRecord("a", PTDatValue(12));
    tmp.InsRecord("d", PTDatValue(11));
    tmp.InsRecord("s", PTDatValue(14));
    tmp.DelRecord("a");
    tmp.InsRecord("a", PTDatValue(14));
    tmp.DelRecord("c");
    tmp.DelRecord("d");
    EXPECT_EQ(nullptr, tmp.FindRecord("d"));
    EXPECT_NE(nullptr, tmp.FindRecord("a"));
    EXPECT_NE(nullptr, tmp.FindRecord("s"));
}

TEST(TBalanceTree, insert_many_records)
{
    TBalanceTree tmp;
    tmp.InsRecord("x1", PTDatValue(4));
    tmp.InsRecord("x2", PTDatValue(4));
    tmp.InsRecord("x3", PTDatValue(4));
    tmp.InsRecord("x4", PTDatValue(4));
    EXPECT_NE(nullptr, tmp.FindRecord("x1"));
    EXPECT_NE(nullptr, tmp.FindRecord("x2"));
    EXPECT_NE(nullptr, tmp.FindRecord("x3"));
    EXPECT_NE(nullptr, tmp.FindRecord("x4"));
}

TEST(TBalanceTree, delete_with_rebalancing)
{
    TBalanceTree tmp;
    tmp.InsRecord("1", PTDatValue(1));
    tmp.InsRecord("2", PTDatValue(1));
    tmp.InsRecord("3", PTDatValue(1));
    tmp.DelRecord("1");
    EXPECT_NE(nullptr, tmp.FindRecord("2"));
    EXPECT_EQ(nullptr, tmp.FindRecord("1"));
    EXPECT_NE(nullptr, tmp.FindRecord("3"));
}

TEST(TArrayHash, can_create_obj)
{
    ASSERT_NO_THROW(TArrayHash tmp(6, 3));
}

TEST(TArrayHash, can_insert)
{
    TArrayHash tmp(10, 3);
    ASSERT_NO_THROW(tmp.InsRecord("sss", PTDatValue(111)));
}

TEST(TArrayHash, can_find)
{
    TArrayHash tmp(11, 3);
    tmp.InsRecord("f", PTDatValue(14));
    EXPECT_NE(nullptr, tmp.FindRecord("f"));
}

TEST(TArrayHash, can_delete)
{
    TArrayHash tmp(11, 3);
    tmp.InsRecord("h", nullptr);
    tmp.DelRecord("h");
    EXPECT_EQ(nullptr, tmp.FindRecord("h"));
}

TEST(TArrayHash, cant_find_missing_record)
{
    TArrayHash tmp(12, 3);
    tmp.InsRecord("h", nullptr);
    tmp.InsRecord("ss", nullptr);
    tmp.InsRecord("23", nullptr);
    tmp.InsRecord("qdf", nullptr);
    tmp.InsRecord("i", nullptr);
    tmp.InsRecord("c", nullptr);
    tmp.InsRecord("bj", nullptr);
    EXPECT_EQ(nullptr, tmp.FindRecord("p"));
}

TEST(TArrayHash, cant_insert_if_full)
{
    TArrayHash tmp(7, 3);
    tmp.InsRecord("h", nullptr);
    tmp.InsRecord("ff", nullptr);
    tmp.InsRecord("sda", nullptr);
    tmp.InsRecord("q", nullptr);
    tmp.InsRecord("czx", nullptr);
    tmp.InsRecord("xxx", nullptr);
    tmp.InsRecord("zz j1", nullptr);
    ASSERT_ANY_THROW(tmp.InsRecord("px", nullptr));
}

TEST(TListHash, can_create_obj)
{
    ASSERT_NO_THROW(TListHash tmp(5));
}

TEST(TListHash, can_insert)
{
    TListHash tmp(5);
    ASSERT_NO_THROW(tmp.InsRecord("s", nullptr));
}

TEST(TListHash, can_find)
{
    TListHash tmp(5);
    tmp.InsRecord("s", PTDatValue(144));
    EXPECT_NE(nullptr, tmp.FindRecord("s"));

}

TEST(TListHash, can_delete)
{
    TListHash tmp(5);
    tmp.InsRecord("s", nullptr);
    tmp.DelRecord("s");
    EXPECT_EQ(nullptr, tmp.FindRecord("s"));
}

TEST(TListHash, can_insert_many)
{
    TListHash tmp(3);
    tmp.InsRecord("1", PTDatValue(4));
    tmp.InsRecord("2", PTDatValue(4));
    tmp.InsRecord("3", PTDatValue(4));
    tmp.InsRecord("4", PTDatValue(4));
    tmp.InsRecord("5", PTDatValue(4));
    tmp.InsRecord("6", PTDatValue(4));
    tmp.DelRecord("1");
    EXPECT_NE(nullptr, tmp.FindRecord("5"));
    EXPECT_NE(nullptr, tmp.FindRecord("2"));
    EXPECT_NE(nullptr, tmp.FindRecord("3"));
    EXPECT_NE(nullptr, tmp.FindRecord("4"));
    EXPECT_NE(nullptr, tmp.FindRecord("6"));
    EXPECT_EQ(nullptr, tmp.FindRecord("1"));
    EXPECT_EQ(nullptr, tmp.FindRecord("f"));
}
