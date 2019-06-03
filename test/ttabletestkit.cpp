#include <gtest.h>

#include "tword.h"
#include "tsorttable.h"
#include "ttreetable.h"
#include "tbalancetree.h"
#include "tarrayhash.h"
#include "tlisthash.h"

TEST(TScanTable, Can_Ins_Record)
{
    TScanTable t(2);
    TWord* w = new TWord("word");
    t.InsRecord("1", w);

    EXPECT_EQ("1", t.GetKey(FIRST_POS));
}

TEST(TScanTable, Can_Find_Existent_Record)
{
    TScanTable t(4);
    TWord* w1 = new TWord("word1");
    TWord* w2 = new TWord("word2");
    TWord* w3 = new TWord("word3");
    t.InsRecord("1", w1);
    t.InsRecord("2", w2);
    t.InsRecord("3", w3);
    TWord* r = (TWord*)t.FindRecord("2");

    EXPECT_EQ("word2", r->GetWord());
}

TEST(TScanTable, Cant_Find_Non_Existent_Record)
{
    TScanTable t(4);
    TWord* w1 = new TWord("word1");
    TWord* w2 = new TWord("word2");
    TWord* w3 = new TWord("word3");
    t.InsRecord("1", w1);
    t.InsRecord("2", w2);
    t.InsRecord("3", w3);
    TWord* r = (TWord*)t.FindRecord("4");

    EXPECT_EQ(nullptr, r);
}

TEST(TScanTable, Can_Del_Record)
{
    TScanTable t(4);
    TWord* w1 = new TWord("word1");
    TWord* w2 = new TWord("word2");
    TWord* w3 = new TWord("word3");
    t.InsRecord("1", w1);
    t.InsRecord("2", w2);
    t.InsRecord("3", w3);
    t.DelRecord("1");

    EXPECT_EQ("2", t.GetKey(FIRST_POS));
}

TEST(TSortTable, Can_Find_Existent_Record)
{
    TScanTable t(6);
    TWord* w1 = new TWord("word1");
    TWord* w2 = new TWord("word2");
    t.InsRecord("b", w1);
    t.InsRecord("a", w1);
    t.InsRecord("c", w1);
    t.InsRecord("e", w2);
    t.InsRecord("d", w1);
    TSortTable ts;
    ts.SetSortMethod(MERGE_SORT);
    ts = t;
    PTDatValue p = ts.FindRecord("e");

    EXPECT_EQ("word2", ((TWord*)p)->GetWord());
}

TEST(TSortTable, Can_Ins_Record)
{
    TSortTable t(6);
    TWord* w = new TWord("word");
    t.InsRecord("b", w);
    t.InsRecord("a", w);
    t.InsRecord("c", w);
    t.InsRecord("e", w);
    t.InsRecord("d", w);

    EXPECT_EQ("a", t.GetKey(FIRST_POS));
}

TEST(TSortTable, Can_Del_Record)
{
    TSortTable t(6);
    TWord* w = new TWord("word");
    t.InsRecord("b", w);
    t.InsRecord("a", w);
    t.InsRecord("c", w);
    t.InsRecord("e", w);
    t.InsRecord("d", w);
    t.DelRecord("e");

    EXPECT_EQ("d", t.GetKey(LAST_POS));
}

TEST(TTreeTable, Can_Ins_Record)
{
    TTreeTable t;
    TWord* w = new TWord("word");
    t.InsRecord("b", w);
    t.InsRecord("a", w);
    t.InsRecord("c", w);
    t.Reset();

    EXPECT_EQ("a", t.GetKey());
}

TEST(TTreeTable, Can_Find_Existent_Record)
{
    TTreeTable t;
    TWord* w1 = new TWord("word1");
    TWord* w2 = new TWord("word2");
    t.InsRecord("b", w2);
    t.InsRecord("a", w1);
    t.InsRecord("c", w1);
    PTDatValue tmp = t.FindRecord("b");

    EXPECT_EQ("word2", ((TWord*)tmp)->GetWord());
}

TEST(TTreeTable, Can_Del_Record)
{
    TTreeTable t;
    TWord* w = new TWord("check");
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

TEST(TBalanceTree, Can_Insert_Record_Balance)
{
    TBalanceTree t;
    TWord* w = new TWord("word");
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

TEST(TArrayHash, Can_Ins_Record)
{
    TArrayHash t(10, 3);
    TWord* w = new TWord("word");
    t.InsRecord("a", w);
    TWord* tmp = (TWord*)t.FindRecord("a");

    EXPECT_EQ("word", tmp->GetWord());
}

TEST(TArrayHash, Can_Find_Existent_Record)
{
    TArrayHash t(10, 3);
    TWord* w = new TWord("word");
    t.InsRecord("a", w);
    t.InsRecord("b", w);
    t.InsRecord("c", w);
    t.InsRecord("d", w);
    t.InsRecord("e", w);
    TWord* tmp = (TWord*)t.FindRecord("d");

    EXPECT_EQ("word", tmp->GetWord());
}

TEST(TArrayHash, Can_Del_Record)
{
    TArrayHash t;
    TWord* w = new TWord("word");
    t.InsRecord("d", w);
    t.DelRecord("d");

    EXPECT_EQ(nullptr, t.FindRecord("d"));
}

TEST(TListHash, Can_Ins_Record_And_Find)
{
    TListHash t;
    TWord* w = new TWord("word");
    t.InsRecord("a", w);
    TWord* tmp = (TWord*)t.FindRecord("a");

    EXPECT_EQ("word", tmp->GetWord());
}

TEST(TListHash, Can_Del_Record)
{
    TListHash t;
    TWord* w = new TWord("word");
    t.InsRecord("d", w);
    t.DelRecord("d");

    EXPECT_EQ(nullptr, t.FindRecord("d"));
}
