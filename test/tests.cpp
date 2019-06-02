#include <gtest.h>

#include "tword.h"
#include "sorttab.h"
#include "treetab.h"
#include "baltree.h"
#include "arrhash.h"
#include "listhash.h"


TEST(TScanTable, can_ins_first_record)
{
    TScanTable t(5);
    TWord * w = new TWord("check");

    t.InsRecord("one", w);

    EXPECT_EQ("one", t.GetKey(FIRST_POS));
}

TEST(TScanTable, can_ins_second_record)
{
    TScanTable t(5);
    TWord * w = new TWord("check");

    t.InsRecord("one", w);
    t.InsRecord("two", w);
    t.GoNext();

    EXPECT_EQ("two", t.GetKey());
}

TEST(TScanTable, cant_ins_if_full)
{
    TScanTable t(2);
    TWord * w = new TWord("check");

    t.InsRecord("one", w);
    t.InsRecord("two", w);
    t.InsRecord("three", w);

    EXPECT_EQ(TabFull, t.GetRetCode());
}

TEST(TScanTable, cant_ins_if_have_rec)
{
    TScanTable t(3);
    TWord * w = new TWord("check");

    t.InsRecord("one", w);
    t.InsRecord("two", w);
    t.InsRecord("two", w);

    EXPECT_EQ(TabRecDbl, t.GetRetCode());
}

TEST(TScanTable, can_find_record)
{
    TScanTable t(5);
    TWord * w1 = new TWord("check1");
    TWord * w2 = new TWord("check2");
    TWord * w3 = new TWord("check3");

    t.InsRecord("one", w1);
    t.InsRecord("two", w2);
    t.InsRecord("three", w3);
    TWord* r = (TWord*)t.FindRecord("two");

    EXPECT_EQ("check2", r->GetWord());
}

TEST(TScanTable, cant_find_record)
{
    TScanTable t(5);
    TWord * w1 = new TWord("check1");
    TWord * w2 = new TWord("check2");
    TWord * w3 = new TWord("check3");

    t.InsRecord("one", w1);
    t.InsRecord("two", w2);
    t.InsRecord("three", w3);
    TWord* r = (TWord*)t.FindRecord("four");

    EXPECT_EQ(nullptr, r);
}

TEST(TScanTable, can_del_record)
{
    TScanTable t(5);
    TWord * w1 = new TWord("check1");
    TWord * w2 = new TWord("check2");
    TWord * w3 = new TWord("check3");

    t.InsRecord("one", w1);
    t.InsRecord("two", w2);
    t.InsRecord("three", w3);

    t.DelRecord("one");

    EXPECT_EQ("two", t.GetKey(FIRST_POS));
}

TEST(TScanTable, cant_del_if_empty)
{
    TScanTable t(5);

    t.DelRecord("one");

    EXPECT_EQ(TabEmpty, t.GetRetCode());
}

TEST(TScanTable, cant_del_if_no_rec)
{
    TScanTable t(5);
    TWord * w1 = new TWord("check1");
    TWord * w2 = new TWord("check2");
    TWord * w3 = new TWord("check3");

    t.InsRecord("one", w1);
    t.InsRecord("two", w2);
    t.InsRecord("three", w3);

    t.DelRecord("four");

    EXPECT_EQ(TabNoRec, t.GetRetCode());
}

TEST(TSortTable, can_sort_insert)
{
    TScanTable t(5);

    TWord * w = new TWord("check");

    t.InsRecord("b", w);
    t.InsRecord("a", w);
    t.InsRecord("c", w);
    t.InsRecord("e", w);
    t.InsRecord("d", w);

    TSortTable ts;
    ts.SetSortMethod(INSERT_SORT);

    ts = t;

    EXPECT_EQ("a", ts.GetKey());
    ts.GoNext();
    EXPECT_EQ("b", ts.GetKey());
    ts.GoNext();
    EXPECT_EQ("c", ts.GetKey());
    ts.GoNext();
    EXPECT_EQ("d", ts.GetKey());
    ts.GoNext();
    EXPECT_EQ("e", ts.GetKey());       
}

TEST(TSortTable, can_sort_quick)
{
    TScanTable t(5);

    TWord * w = new TWord("check");

    t.InsRecord("b", w);
    t.InsRecord("a", w);
    t.InsRecord("c", w);
    t.InsRecord("e", w);
    t.InsRecord("d", w);

    TSortTable ts;
    ts.SetSortMethod(QUICK_SORT);

    ts = t;

    EXPECT_EQ("a", ts.GetKey());
    ts.GoNext();
    EXPECT_EQ("b", ts.GetKey());
    ts.GoNext();
    EXPECT_EQ("c", ts.GetKey());
    ts.GoNext();
    EXPECT_EQ("d", ts.GetKey());
    ts.GoNext();
    EXPECT_EQ("e", ts.GetKey());
}

TEST(TSortTable, can_sort_merge)
{
    TScanTable t(5);

    TWord * w = new TWord("check");

    t.InsRecord("b", w);
    t.InsRecord("a", w);
    t.InsRecord("c", w);
    t.InsRecord("e", w);
    t.InsRecord("d", w);

    TSortTable ts;
    ts.SetSortMethod(MERGE_SORT);

    ts = t;

    EXPECT_EQ("a", ts.GetKey());
    ts.GoNext();
    EXPECT_EQ("b", ts.GetKey());
    ts.GoNext();
    EXPECT_EQ("c", ts.GetKey());
    ts.GoNext();
    EXPECT_EQ("d", ts.GetKey());
    ts.GoNext();
    EXPECT_EQ("e", ts.GetKey());
}

TEST(TSortTable, can_find_record)
{
    TScanTable t(5);

    TWord * w = new TWord("check");
    TWord * w1 = new TWord("e");

    t.InsRecord("b", w);
    t.InsRecord("a", w);
    t.InsRecord("c", w);
    t.InsRecord("e", w1);
    t.InsRecord("d", w);

    TSortTable ts;
    ts.SetSortMethod(MERGE_SORT);

    ts = t;
    PTDatValue p = ts.FindRecord("e");

    EXPECT_EQ("e", ((TWord*)p)->GetWord());
}

TEST(TSortTable, can_ins_record)
{
    TSortTable t(5);

    TWord * w = new TWord("check");

    t.InsRecord("b", w);
    t.InsRecord("a", w);
    t.InsRecord("c", w);
    t.InsRecord("e", w);
    t.InsRecord("d", w);

    EXPECT_EQ("a", t.GetKey(FIRST_POS));
}

TEST(TSortTable, can_del_record)
{
    TSortTable t(5);

    TWord * w = new TWord("check");

    t.InsRecord("b", w);
    t.InsRecord("a", w);
    t.InsRecord("c", w);
    t.InsRecord("e", w);
    t.InsRecord("d", w);

    t.DelRecord("e");

    EXPECT_EQ("d", t.GetKey(LAST_POS));
}

TEST(TTreeTable, can_ins_record)
{
    TTreeTable t;
    TWord * w = new TWord("check");

    t.InsRecord("b", w);
    t.InsRecord("a", w);
    t.InsRecord("c", w);

    t.Reset();

    EXPECT_EQ("a", t.GetKey());
}

TEST(TTreeTable, can_go_next)
{
    TTreeTable t;
    TWord * w = new TWord("check");

    t.InsRecord("b", w);
    t.InsRecord("a", w);
    t.InsRecord("c", w);

    t.Reset();

    EXPECT_EQ("a", t.GetKey());
    t.GoNext();
    EXPECT_EQ("b", t.GetKey());
    t.GoNext();
    EXPECT_EQ("c", t.GetKey());
}

TEST(TTreeTable, can_find_record)
{
    TTreeTable t;
    TWord * w = new TWord("check");
    TWord * w1 = new TWord("aga");

    t.InsRecord("b", w1);
    t.InsRecord("a", w);
    t.InsRecord("c", w);

    PTDatValue tmp = t.FindRecord("b");

    EXPECT_EQ("aga", ((TWord*)tmp)->GetWord());
}

TEST(TTreeTable, can_del_record_if_right_empty)
{
    TTreeTable t;
    TWord * w = new TWord("check");

    t.InsRecord("c", w);
    t.InsRecord("b", w);
    t.InsRecord("a", w);
    t.InsRecord("d", w);

    t.DelRecord("b");
    t.Reset();
    t.GoNext();

    EXPECT_EQ("c", t.GetKey());
}

TEST(TTreeTable, can_del_record_if_left_empty)
{
    TTreeTable t;
    TWord * w = new TWord("check");

    t.InsRecord("b", w);
    t.InsRecord("a", w);
    t.InsRecord("c", w);
    t.InsRecord("d", w);

    t.DelRecord("c");
    t.Reset();
    t.GoNext();
    t.GoNext();

    EXPECT_EQ("d", t.GetKey());
}

TEST(TTreeTable, can_del_record)
{
    TTreeTable t;
    TWord * w = new TWord("check");

    t.InsRecord("b", w);
    t.InsRecord("a", w);
    t.InsRecord("f", w);
    t.InsRecord("g", w);
    t.InsRecord("d", w);
    t.InsRecord("e", w);
    t.InsRecord("c", w);

    t.DelRecord("f");
    t.Reset();
    t.GoNext();
    t.GoNext();
    t.GoNext();
    t.GoNext();

    EXPECT_EQ("e", t.GetKey());
}

TEST(TBalanceTree, can_insert_record_left)
{
    TBalanceTree t;

    TWord *w = new TWord("check");

    t.InsRecord("b", w);
    t.InsRecord("a", w);

    t.Reset();

    EXPECT_EQ("a", t.GetKey());
}

TEST(TBalanceTree, can_insert_record_right)
{
    TBalanceTree t;

    TWord *w = new TWord("check");

    t.InsRecord("a", w);
    t.InsRecord("b", w);

    t.Reset();
    t.GoNext();

    EXPECT_EQ("b", t.GetKey());
}

TEST(TBalanceTree, can_insert_record_balance)
{
    TBalanceTree t;

    TWord *w = new TWord("check");

    t.InsRecord("e", w);
    t.InsRecord("f", w);
    t.InsRecord("c", w);
    t.InsRecord("d", w);
    t.InsRecord("b", w);
    t.InsRecord("a", w);
    
    t.Reset();
    t.GoNext();
    t.GoNext();

    EXPECT_EQ("c", t.GetKey());
}

TEST(TArrayHash, can_ins_record)
{
    TArrayHash t(10, 3);
    TWord *w = new TWord("check");

    t.InsRecord("a", w);

    TWord* tmp = (TWord*)t.FindRecord("a");

    EXPECT_EQ("check", tmp->GetWord());
}

TEST(TArrayHash, can_ins_max_record)
{
    TArrayHash t(5, 1);
    TWord *w = new TWord("check");

    t.InsRecord("a", w);
    t.InsRecord("b", w);
    t.InsRecord("c", w);
    t.InsRecord("d", w);
    t.InsRecord("e", w);

    TWord* tmp = (TWord*)t.FindRecord("a");

    EXPECT_EQ("check", tmp->GetWord());
}

TEST(TArrayHash, can_find_record)
{
    TArrayHash t(10, 3);
    TWord *w = new TWord("check");

    t.InsRecord("a", w);
    t.InsRecord("b", w);
    t.InsRecord("c", w);
    t.InsRecord("d", w);
    t.InsRecord("e", w);

    TWord* tmp = (TWord*)t.FindRecord("d");

    EXPECT_EQ("check", tmp->GetWord());
}

TEST(TArrayHash, can_find_record_if_tab_full)
{
    TArrayHash t(10, 3);
    TWord *w = new TWord("check");

    t.InsRecord("a", w);
    t.InsRecord("b", w);
    t.InsRecord("c", w);
    t.InsRecord("d", w);
    t.InsRecord("e", w);
    t.InsRecord("u", w);
    t.InsRecord("i", w);
    t.InsRecord("o", w);
    t.InsRecord("p", w);
    t.InsRecord("l", w);

    TWord* tmp = (TWord*)t.FindRecord("d");

    EXPECT_EQ("check", tmp->GetWord());
}

TEST(TArrayHash, can_del_record)
{
    TArrayHash t;
    TWord *w = new TWord("check");

    t.InsRecord("d", w);
    t.DelRecord("d");

    EXPECT_EQ(nullptr, t.FindRecord("d"));
}

TEST(TListHash, can_ins_record_and_find)
{
    TListHash t;
    TWord *w = new TWord("check");


    t.InsRecord("a", w);

    TWord *tmp = (TWord*)t.FindRecord("a");

    EXPECT_EQ("check", tmp->GetWord());
}

TEST(TListHash, can_del_record)
{
    TListHash t;
    TWord *w = new TWord("check");

    t.InsRecord("d", w);
    t.DelRecord("d");

    EXPECT_EQ(nullptr, t.FindRecord("d"));
}















