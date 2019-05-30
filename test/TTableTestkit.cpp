#include <gtest.h>

#include <iostream>
#include <vector>
#include <map>
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"

TEST(TScanTable, can_create_object)
{
    ASSERT_NO_THROW(TScanTable a(6));
}

TEST(TScanTable, can_use_is_full)
{
    TScanTable a(6);
    EXPECT_EQ(0, a.IsFull());
}

TEST(TScanTable, can_use_is_empty)
{
    TScanTable a(6);
    EXPECT_EQ(1, a.IsEmpty());
}

TEST(TScanTable, can_get_efficienty)
{
    TScanTable a(6);
    EXPECT_EQ(0, a.GetEfficiency());
}

TEST(TScanTable, can_get_data_count)
{
    TScanTable a(6);
    EXPECT_EQ(0, a.GetDataCount());
}

TEST(TScanTable, can_insert_value)
{
    TScanTable a(6);
    ASSERT_NO_THROW(a.InsRecord("h", nullptr));
}

TEST(TScanTable, can_find_value)
{
    TScanTable a(6);
    a.InsRecord("h", nullptr);
    EXPECT_NE(nullptr, a.FindRecord("h"));
}

TEST(TScanTable, can_delete_record)
{
    TScanTable a(6);
    a.InsRecord("h", nullptr);
    a.DelRecord("h");
    EXPECT_EQ(0, a.GetDataCount());
}

TEST(TScanTable, data_count_can_be_increased)
{
    TScanTable a(6);
    a.InsRecord("h", nullptr);
    EXPECT_EQ(1, a.GetDataCount());
}

TEST(TScanTable, can_get_key)
{
    TScanTable a(6);
    a.InsRecord("h", nullptr);
    EXPECT_EQ("h", a.GetKey());
}

TEST(TScanTable, can_get_value_ptr)
{
    TScanTable a(6);
    a.InsRecord("h", (PTDatValue)87);
    EXPECT_EQ((PTDatValue)87, a.GetValuePTR());
}

TEST(TScanTable, can_get_tab_size)
{
    TScanTable a(6);
    EXPECT_EQ(6, a.GetTabSize());
}

TEST(TScanTable, cant_add_then_tab_is_full)
{
    TScanTable a(3);
    a.InsRecord("h", nullptr);
    a.InsRecord("yu", nullptr);
    a.InsRecord("k", nullptr);
    ASSERT_ANY_THROW(a.InsRecord("u", nullptr));
}

TEST(TScanTable, can_reset)
{
    TScanTable a(6);
    a.InsRecord("h", nullptr);
    a.InsRecord("yu", nullptr);
    a.GoNext();
    a.Reset();
    EXPECT_EQ("h", a.GetKey());
}

TEST(TScanTable, can_check_if_tab_ended)
{
    TScanTable a(6);
    EXPECT_EQ(1, a.IsTabEnded());
}

TEST(TScanTable, can_go_next)
{
    TScanTable a(6);
    a.InsRecord("yu", nullptr);
    a.InsRecord("h", nullptr);
    a.GoNext();
    EXPECT_EQ("h", a.GetKey());
}

TEST(TSortTable, can_create_object)
{
    ASSERT_NO_THROW(TSortTable a(2));
}

TEST(TSortTable, can_create_from_tscantable)
{
    TScanTable a(6);
    a.InsRecord("yu", nullptr);
    a.InsRecord("h", nullptr);
    ASSERT_NO_THROW(TSortTable b(a));
}

TEST(TSortTable, can_assign_from_tscantable)
{
    TScanTable a(6);
    a.InsRecord("yu", nullptr);
    a.InsRecord("h", nullptr);
    TSortTable b;
    ASSERT_NO_THROW(b = a);
}

TEST(TSortTable, can_get_sort_method)
{
    TSortTable b;
    EXPECT_EQ(TSortMethod::QUIQ_SORT, b.GetSortMethod());
}

TEST(TSortTable, can_set_sort_method)
{
    TSortTable b;
    b.SetSortMethod(TSortMethod::INSERT_SORT);
    EXPECT_EQ(TSortMethod::INSERT_SORT, b.GetSortMethod());
}

class SortTestTSortTable: public ::testing::Test
{
    protected:
    void check_sort(TSortMethod sm)
    {
        TSortTable b(0);
        string s[] = {"a", "g", "ger", "ju", "kl", "nn", "pkn", "qw", "u", "uy"};
        b.SetSortMethod(sm);
        TScanTable a(10);
        a.InsRecord("u", nullptr);
        a.InsRecord("uy", nullptr);
        a.InsRecord("ger", nullptr);
        a.InsRecord("pkn", nullptr);
        a.InsRecord("qw", nullptr);
        a.InsRecord("nn", nullptr);
        a.InsRecord("ju", nullptr);
        a.InsRecord("a", nullptr);
        a.InsRecord("kl", nullptr);
        a.InsRecord("g", nullptr);
        b = a;
        b.Reset();
        for (int i = 0; i < 10; ++i)
        {
            EXPECT_TRUE(s[i] == b.GetKey());
            b.GoNext();
        }
    }
};

TEST_F(SortTestTSortTable, quick_sort_is_correct)
{
    check_sort(TSortMethod::QUIQ_SORT);
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
    TScanTable a(6);
    a.InsRecord("yu", nullptr);
    a.InsRecord("h", nullptr);
    TSortTable b(0);
    b = a;
    EXPECT_NE(nullptr, b.FindRecord("yu"));
}

TEST(TSortTable, cant_find_if_it_is_not_exist)
{
    TScanTable a(6);
    a.InsRecord("yu", nullptr);
    a.InsRecord("h", nullptr);
    TSortTable b(0);
    b = a;
    EXPECT_EQ(nullptr, b.FindRecord("oii"));
}

TEST(TSortTable, can_insert)
{
    TScanTable a(6);
    a.InsRecord("yu", nullptr);
    a.InsRecord("h", nullptr);
    TSortTable b(0);
    b = a;
    b.InsRecord("y", nullptr);
    EXPECT_NE(nullptr, b.FindRecord("y"));
}

TEST(TSortTable, cant_insert_if_full)
{
    TScanTable a(2);
    a.InsRecord("yu", nullptr);
    a.InsRecord("h", nullptr);
    TSortTable b(0);
    b = a;
    ASSERT_ANY_THROW(b.InsRecord("y", nullptr));
}

TEST(TSortTable, can_delete)
{
    TScanTable a(2);
    a.InsRecord("yu", nullptr);
    a.InsRecord("h", nullptr);
    TSortTable b(0);
    b = a;
    b.DelRecord("yu");
    EXPECT_EQ(nullptr, b.FindRecord("yu"));
}

TEST(TTreeTable, can_create_object)
{
    ASSERT_NO_THROW(TTreeTable a);
}

TEST(TTreeTable, can_insert_record)
{
    TTreeTable a;
    ASSERT_NO_THROW(a.InsRecord("h", nullptr));
}

TEST(TTreeTable, can_find_record)
{
    TTreeTable a;
    a.InsRecord("h", nullptr);
    a.InsRecord("y", nullptr);
    EXPECT_NE(nullptr, a.FindRecord("y"));
}

TEST(TTreeTable, can_delete_record)
{
    TTreeTable a;
    a.InsRecord("h", nullptr);
    a.InsRecord("y", nullptr);
    a.InsRecord("c", nullptr);
    a.DelRecord("h");
    EXPECT_NE(nullptr, a.FindRecord("c"));
    EXPECT_NE(nullptr, a.FindRecord("y"));
    EXPECT_EQ(nullptr, a.FindRecord("h"));
}

TEST(TTreeTable, can_reset)
{
    TTreeTable a;
    a.InsRecord("h", nullptr);
    a.InsRecord("y", nullptr);
    a.InsRecord("c", nullptr);
    a.DelRecord("h");
    ASSERT_NO_THROW(a.Reset());
}

TEST(TTreeTable, can_go_next)
{
    TTreeTable a;
    a.InsRecord("h", nullptr);
    a.InsRecord("y", nullptr);
    a.InsRecord("c", nullptr);
    a.DelRecord("h");
    a.Reset();
    a.GoNext();
    EXPECT_TRUE(a.GetKey() == "y");
}

TEST(TTreeTable, can_check_if_ended)
{
    TTreeTable a;
    a.InsRecord("h", nullptr);
    a.InsRecord("y", nullptr);
    a.InsRecord("c", nullptr);
    a.DelRecord("h");
    a.Reset();
    a.GoNext();
    a.GoNext();
    EXPECT_TRUE(a.IsTabEnded());
}

TEST(TBalanceTree, can_insert)
{
    TBalanceTree a;
    ASSERT_NO_THROW(a.InsRecord("a", nullptr));
}

TEST(TBalanceTree, can_find)
{
    TBalanceTree a;
    a.InsRecord("a", nullptr);
    EXPECT_NE(nullptr, a.FindRecord("a"));
}

TEST(TBalanceTree, can_delete)
{
    TBalanceTree a;
    a.InsRecord("a", nullptr);
    a.DelRecord("a");
    EXPECT_EQ(nullptr, a.FindRecord("a"));
}

TEST(TBalanceTree, can_find_much)
{
    TBalanceTree a;
    a.InsRecord("a", nullptr);
    a.InsRecord("b", nullptr);
    a.InsRecord("c", nullptr);
    a.InsRecord("d", nullptr);
    a.InsRecord("e", nullptr);
    a.DelRecord("a");
    EXPECT_NE(nullptr, a.FindRecord("d"));
}

TEST(TBalanceTree, difficult_delete)
{
    TBalanceTree a;
    a.InsRecord("a", nullptr);
    a.InsRecord("b", nullptr);
    a.InsRecord("c", nullptr);
    a.InsRecord("d", nullptr);
    a.InsRecord("e", nullptr);
    a.DelRecord("a");
    a.InsRecord("a", nullptr);
    a.DelRecord("c");
    a.DelRecord("d");
    EXPECT_EQ(nullptr, a.FindRecord("d"));
    EXPECT_NE(nullptr, a.FindRecord("a"));
    EXPECT_EQ(nullptr, a.FindRecord("c"));
    EXPECT_NE(nullptr, a.FindRecord("e"));
    EXPECT_NE(nullptr, a.FindRecord("b"));
}

TEST(TBalanceTree, difficult_insert)
{
    TBalanceTree a;
    a.InsRecord("a", nullptr);
    a.InsRecord("b", nullptr);
    a.InsRecord("c", nullptr);
    a.InsRecord("d", nullptr);
    a.InsRecord("e", nullptr);
    a.DelRecord("c");
    a.InsRecord("c", nullptr);
    a.InsRecord("w", nullptr);
    EXPECT_NE(nullptr, a.FindRecord("b"));
    EXPECT_NE(nullptr, a.FindRecord("d"));
    EXPECT_NE(nullptr, a.FindRecord("a"));
    EXPECT_NE(nullptr, a.FindRecord("c"));
    EXPECT_NE(nullptr, a.FindRecord("w"));
    EXPECT_NE(nullptr, a.FindRecord("e"));
}

TEST(TBalanceTree, one_more_delete)
{
    TBalanceTree a;
    a.InsRecord("c", nullptr);
    a.InsRecord("b", nullptr);
    a.InsRecord("a", nullptr);
    a.InsRecord("d", nullptr);
    a.DelRecord("c");
    a.InsRecord("w", nullptr);
    a.InsRecord("e", nullptr);
    a.InsRecord("c", nullptr);
    EXPECT_NE(nullptr, a.FindRecord("d"));
    EXPECT_NE(nullptr, a.FindRecord("a"));
    EXPECT_NE(nullptr, a.FindRecord("c"));
    EXPECT_NE(nullptr, a.FindRecord("w"));
    EXPECT_NE(nullptr, a.FindRecord("b"));
    EXPECT_NE(nullptr, a.FindRecord("e"));
}

TEST(TBalanceTree, delete_with_rebalancing)
{
    TBalanceTree a;
    a.InsRecord("c", nullptr);
    a.InsRecord("b", nullptr);
    a.InsRecord("f", nullptr);
    a.InsRecord("a", nullptr);
    a.InsRecord("e", nullptr);
    a.InsRecord("g", nullptr);
    a.InsRecord("d", nullptr);
    a.InsRecord("h", nullptr);
    a.DelRecord("a");
    a.DelRecord("c");
    EXPECT_EQ(nullptr, a.FindRecord("a"));
    EXPECT_NE(nullptr, a.FindRecord("b"));
    EXPECT_EQ(nullptr, a.FindRecord("c"));
    EXPECT_NE(nullptr, a.FindRecord("d"));
    EXPECT_NE(nullptr, a.FindRecord("e"));
    EXPECT_NE(nullptr, a.FindRecord("f"));
    EXPECT_NE(nullptr, a.FindRecord("g"));
    EXPECT_NE(nullptr, a.FindRecord("h"));
}

TEST(TArrayHash, can_insert)
{
    TArrayHash a(7, 3);
    ASSERT_NO_THROW(a.InsRecord("h", nullptr));
}

TEST(TArrayHash, can_find)
{
    TArrayHash a(7, 3);
    a.InsRecord("h", nullptr);
    EXPECT_NE(nullptr, a.FindRecord("h"));
}

TEST(TArrayHash, can_delete)
{
    TArrayHash a(7, 3);
    a.InsRecord("h", nullptr);
    a.DelRecord("h");
    EXPECT_EQ(nullptr, a.FindRecord("h"));
}

TEST(TArrayHash, cant_find_wrong_record)
{
    TArrayHash a(7, 3);
    a.InsRecord("h", nullptr);
    a.InsRecord("ojp", nullptr);
    a.InsRecord("tdrj", nullptr);
    a.InsRecord("q", nullptr);
    a.InsRecord("pjii", nullptr);
    a.InsRecord("xtc", nullptr);
    a.InsRecord("ukb j", nullptr);
    EXPECT_EQ(nullptr, a.FindRecord("p"));
}

TEST(TArrayHash, cant_insert_if_full)
{
    TArrayHash a(7, 3);
    a.InsRecord("h", nullptr);
    a.InsRecord("ojp", nullptr);
    a.InsRecord("tdrj", nullptr);
    a.InsRecord("q", nullptr);
    a.InsRecord("pjii", nullptr);
    a.InsRecord("xtc", nullptr);
    a.InsRecord("ukb j", nullptr);
    ASSERT_ANY_THROW(a.InsRecord("p", nullptr));
}

TEST(TArrayHash, iterators_works_correctly)
{
    map<string, bool> m;
    TArrayHash a(7, 3);
    a.InsRecord("h", nullptr);
    a.InsRecord("ojp", nullptr);
    a.InsRecord("tdrj", nullptr);
    for (a.Reset(); !a.IsTabEnded(); a.GoNext())
        m[a.GetKey()] = 1;
    EXPECT_TRUE(m["h"]);
    EXPECT_TRUE(m["ojp"]);
    EXPECT_TRUE(m["tdrj"]);
    EXPECT_EQ(3u, m.size());
}

TEST(TListHash, can_insert)
{
    TListHash a(5);
    ASSERT_NO_THROW(a.InsRecord("h", nullptr));
}

TEST(TListHash, can_find)
{
    TListHash a(5);
    a.InsRecord("h", nullptr);
    EXPECT_NE(nullptr, a.FindRecord("h"));

}

TEST(TListHash, can_delete)
{
    TListHash a(5);
    a.InsRecord("h", nullptr);
    a.DelRecord("h");
    EXPECT_EQ(nullptr, a.FindRecord("h"));
}

TEST(TListHash, can_insert_many)
{
    TListHash a(3);
    a.InsRecord("h", nullptr);
    a.InsRecord("ojp", nullptr);
    a.InsRecord("tdrj", nullptr);
    a.InsRecord("q", nullptr);
    a.InsRecord("pjii", nullptr);
    a.InsRecord("xtc", nullptr);
    a.InsRecord("ukb j", nullptr);
    a.DelRecord("h");
    EXPECT_NE(nullptr, a.FindRecord("q"));
    EXPECT_NE(nullptr, a.FindRecord("pjii"));
    EXPECT_NE(nullptr, a.FindRecord("xtc"));
    EXPECT_NE(nullptr, a.FindRecord("ojp"));
    EXPECT_NE(nullptr, a.FindRecord("tdrj"));
    EXPECT_EQ(nullptr, a.FindRecord("h"));
    EXPECT_EQ(nullptr, a.FindRecord("uy"));
}

TEST(TListHash, iterators_works_correctly)
{
    map<string, bool> m;
    TListHash a(3);
    a.InsRecord("h", nullptr);
    a.InsRecord("ojp", nullptr);
    a.InsRecord("tdrj", nullptr);
    a.InsRecord("q", nullptr);
    a.InsRecord("pjii", nullptr);
    a.InsRecord("xtc", nullptr);
    a.InsRecord("ukb j", nullptr);
    for (a.Reset(); !a.IsTabEnded(); a.GoNext())
        m[a.GetKey()] = 1;
    EXPECT_TRUE(m["h"]);
    EXPECT_TRUE(m["ojp"]);
    EXPECT_TRUE(m["tdrj"]);
    EXPECT_TRUE(m["q"]);
    EXPECT_TRUE(m["pjii"]);
    EXPECT_TRUE(m["xtc"]);
    EXPECT_TRUE(m["ukb j"]);
    EXPECT_EQ(7u, m.size());
}

TEST(TListHash, iterators_works_correctly_on_wide_array)
{
    map<string, bool> m;
    TListHash a(37);
    a.InsRecord("h", nullptr);
    a.InsRecord("q", nullptr);
    for (a.Reset(); !a.IsTabEnded(); a.GoNext())
        m[a.GetKey()] = 1;
    EXPECT_TRUE(m["h"]);
    EXPECT_TRUE(m["q"]);
    EXPECT_EQ(2u, m.size());
}
