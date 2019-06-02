#include <gtest.h>
#include "tscantable.h"
#include "tsorttaable.h"
#include "ttreenode.h"
#include "ttreetable.h"
#include "tbalancenode.h"
#include "tbalancetree.h"
#include "tarrayhash.h"
#include "tlisthash.h"
#include "tword.h"

TEST(TScanTable, can_insert_record) {
    TScanTable t;
    TWord* tw = new TWord("What");
    ASSERT_NO_THROW(t.InsRecord("1", tw));
    delete tw;
}

TEST(TScanTable, cant_insert_record_with_existent_key) {
    TScanTable t;
    TWord* tw = new TWord("is");
    TWord* tw1 = new TWord("love?");
    t.InsRecord("1", tw);
    ASSERT_ANY_THROW(t.InsRecord("1", tw1));
    delete tw;
    delete tw1;
}

TEST(TScanTable, can_delete_record) {
    TScanTable t;
    TWord* tw = new TWord("baby");
    t.InsRecord("1", tw);
    ASSERT_NO_THROW(t.DelRecord("1"));
    delete tw;
}

TEST(TScanTable, cant_insert_record_in_full_table) {
    TScanTable t(1);
    TWord* tw = new TWord("don't");
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
    TWord* tw = new TWord("hurt");
    t.InsRecord("1", tw);
    EXPECT_TRUE(tw == ((TWord*)t.FindRecord("1")));
    delete tw;
}

TEST(TScanTable, find_record_return_nullptr_with_nonexistent_record) {
    TScanTable t;
    EXPECT_EQ(t.FindRecord("1"), nullptr);
}

TEST(TScanTable, cant_find_record_after_delete) {
    TScanTable t;
    TWord* tw = new TWord("me");
    t.InsRecord("1", tw);
    t.DelRecord("1");
    EXPECT_EQ(t.FindRecord("1"), nullptr);
    delete tw;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TEST(TSortTable, can_insert_record) {
    TSortTable t;
    TWord* tw = new TWord("don't");
    ASSERT_NO_THROW(t.InsRecord("1", tw));
    delete tw;
}

TEST(TSortTable, cant_insert_record_with_existent_key) {
    TSortTable t;
    TWord* tw = new TWord("hurt");
    TWord* tw1 = new TWord("me");
    t.InsRecord("1", tw);
    ASSERT_ANY_THROW(t.InsRecord("1", tw1));
    delete tw;
    delete tw1;
}

TEST(TSortTable, can_delete_record) {
    TSortTable t;
    TWord* tw = new TWord("no");
    t.InsRecord("1", tw);
    ASSERT_NO_THROW(t.DelRecord("1"));
    delete tw;
}

TEST(TSortTable, cant_insert_record_in_full_table) {
    TSortTable t(1);
    TWord* tw = new TWord("more");
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


TEST(TTreeNode, can_create_node) {
    TWord tw("Never");
    ASSERT_NO_THROW(TTreeNode t("5", &tw));
}

TEST(TTreeNode, can_get_left_node) {
    TWord tw("gonna");
    TTreeNode t1("1", &tw);
    TTreeNode t2("2", &tw, &t1, nullptr);
    ASSERT_NO_THROW(t2.GetLeft());
    EXPECT_EQ("2", t2.GetKey());
}

TEST(TTreeNode, can_get_right_node) {
    TWord tw("give");
    TTreeNode t1("1", &tw);
    TTreeNode t2("2", &tw, nullptr, &t1);
    ASSERT_NO_THROW(t2.GetRight());
    EXPECT_EQ("2", t2.GetKey());
}

TEST(TTreeNode, can_get_copy) {
    TWord tw("you");
    TTreeNode t1("1", &tw);
    TTreeNode t2("2", &tw, nullptr, &t1);
    ASSERT_NO_THROW(PTTreeNode t3 = (PTTreeNode)t2.GetCopy());
}

TEST(TTreeNode, get_copy_has_its_own_memory) {
    TWord tw("up");
    TTreeNode t1("1", &tw);
    TTreeNode t2("2", &tw, nullptr, &t1);
    PTTreeNode t3 = (PTTreeNode)t2.GetCopy();
    t3->SetKey("3");
    EXPECT_EQ("2", t2.GetKey());
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TEST(TTreeTable, can_insert_record) {
    TTreeTable t;
    TWord tw("Never");
    ASSERT_NO_THROW(t.InsRecord("1", &tw));
}

TEST(TTreeTable, cant_insert_record_with_existent_key) {
    TTreeTable t;
    TWord tw("gonna");
    TWord tw1("let");
    t.InsRecord("1", &tw);
    ASSERT_ANY_THROW(t.InsRecord("1", &tw1));
}

TEST(TTreeTable, can_delete_record) {
    TTreeTable t;
    TWord tw("you");
    t.InsRecord("1", &tw);
    ASSERT_NO_THROW(t.DelRecord("1"));
}

TEST(TTreeTable, cant_delete_nonexistent_record) {
    TTreeTable t;
    ASSERT_ANY_THROW(t.DelRecord("1"));
}

TEST(TTreeTable, can_find_record) {
    TTreeTable t;
    TWord tw("down");
    TWord tw1("Never");
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.InsRecord("2", &tw1);
    EXPECT_TRUE(tw1 == *((TWord*)t.FindRecord("2")));
}

TEST(TTreeTable, cant_find_record_with_nonexistent_record) {
    TTreeTable t;
    TWord tw("gonna");
    TWord tw1("run");
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.InsRecord("2", &tw1);
    EXPECT_EQ(nullptr, t.FindRecord("5"));
}

TEST(TTreeTable, cant_find_record_after_delete) {
    TTreeTable t;
    TWord tw("around");
    TWord tw1("And");
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.InsRecord("2", &tw1);
    t.DelRecord("2");
    EXPECT_EQ(nullptr, t.FindRecord("2"));
}

TEST(TTreeTable, reset_works_correct) {
    TTreeTable t;
    TWord tw("desert");
    TWord tw1("you");
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.InsRecord("2", &tw1);
    t.Reset();
    EXPECT_EQ("1", t.GetKey());
}

TEST(TTreeTable, can_go_next) {
    TTreeTable t;
    TWord tw("~~~~~~");
    TWord tw1("Somebody");
    t.InsRecord("2", &tw1);
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.Reset();
    t.GoNext();
    EXPECT_EQ("2", t.GetKey());
    t.GoNext();
    EXPECT_EQ("4", t.GetKey());
}

TEST(TTreeTable, is_list_ended_works_correct) {
    TTreeTable t;
    TWord tw("once");
    TWord tw1("told");
    t.InsRecord("2", &tw1);
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.Reset();
    t.GoNext();
    EXPECT_EQ("2", t.GetKey());
    t.GoNext();
    EXPECT_EQ("4", t.GetKey());
    EXPECT_EQ(0, t.IsTabEnded());
    t.GoNext();
    EXPECT_EQ(1, t.IsTabEnded());
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TEST(TArrayHash, can_insert_record) {
    TArrayHash t;
    TWord tw("me");
    ASSERT_NO_THROW(t.InsRecord("1", &tw));
}

TEST(TArrayHash, cant_insert_record_with_existent_key) {
    TArrayHash t;
    TWord tw("The");
    TWord tw1("world");
    t.InsRecord("1", &tw);
    ASSERT_ANY_THROW(t.InsRecord("1", &tw1));
}

TEST(TArrayHash, can_delete_record) {
    TArrayHash t;
    TWord tw("is");
    t.InsRecord("1", &tw);
    ASSERT_NO_THROW(t.DelRecord("1"));
}

TEST(TArrayHash, cant_delete_nonexistent_record) {
    TArrayHash t;
    ASSERT_ANY_THROW(t.DelRecord("1"));
}

TEST(TArrayHash, can_find_record) {
    TArrayHash t;
    TWord tw("gonna");
    TWord tw1("roll");
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.InsRecord("2", &tw1);
    EXPECT_TRUE(tw1 == *((TWord*)t.FindRecord("2")));
}

TEST(TArrayHash, cant_find_record_with_nonexistent_record) {
    TArrayHash t;
    TWord tw("me");
    TWord tw1("I");
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.InsRecord("2", &tw1);
    EXPECT_EQ(nullptr, t.FindRecord("5"));
}

TEST(TArrayHash, cant_find_record_after_delete) {
    TArrayHash t;
    TWord tw("ain't");
    TWord tw1("the");
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.InsRecord("2", &tw1);
    t.DelRecord("2");
    EXPECT_EQ(nullptr, t.FindRecord("2"));
}

TEST(TArrayHash, reset_works_correct) {
    TArrayHash t;
    TWord tw("sharpest");
    TWord tw1("tool");
    t.InsRecord("23", &tw);
    t.InsRecord("0C", &tw);
    t.InsRecord("2", &tw1);
    t.Reset();
    EXPECT_EQ("2", t.GetKey());
}

TEST(TArrayHash, can_go_next) {
    TArrayHash t;
    TWord tw("in");
    TWord tw1("the");
    t.InsRecord("23", &tw1);
    t.InsRecord("0C", &tw);
    t.InsRecord("2", &tw);
    t.Reset();
    t.GoNext();
    EXPECT_EQ("23", t.GetKey());
    t.GoNext();
    EXPECT_EQ("0C", t.GetKey());
}

TEST(TArrayHash, is_tab_ended_works_correct) {
    TArrayHash t;
    TWord tw("shed");
    TWord tw1("She");
    t.InsRecord("23", &tw1);
    t.InsRecord("0C", &tw);
    t.InsRecord("2", &tw);
    t.Reset();
    t.GoNext();
    t.GoNext();
    EXPECT_EQ(0, t.IsTabEnded());
    t.GoNext();
    EXPECT_EQ(1, t.IsTabEnded());
}

TEST(TArrayHash, is_full_works_correct) {
    TArrayHash t(3);
    TWord tw("was");
    TWord tw1("looking");
    t.InsRecord("23", &tw1);
    t.InsRecord("0C", &tw);
    EXPECT_EQ(0, t.IsFull());
    t.InsRecord("2", &tw);
    EXPECT_EQ(1, t.IsFull());
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TEST(TListHash, can_insert_record) {
    TListHash t;
    TWord tw("kind");
    ASSERT_NO_THROW(t.InsRecord("1", &tw));
}

TEST(TListHash, cant_insert_record_with_existent_key) {
    TListHash t;
    TWord tw("of");
    TWord tw1("dumb");
    t.InsRecord("1", &tw);
    ASSERT_ANY_THROW(t.InsRecord("1", &tw1));
}

TEST(TListHash, can_delete_record) {
    TListHash t;
    TWord tw("with");
    t.InsRecord("1", &tw);
    ASSERT_NO_THROW(t.DelRecord("1"));
}

TEST(TListHash, cant_delete_nonexistent_record) {
    TListHash t;
    ASSERT_ANY_THROW(t.DelRecord("1"));
}

TEST(TListHash, can_find_record) {
    TListHash t;
    TWord tw("her");
    TWord tw1("finger");
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.InsRecord("2", &tw1);
    EXPECT_TRUE(tw1 == *((TWord*)t.FindRecord("2")));
}

TEST(TListHash, cant_find_record_with_nonexistent_record) {
    TListHash t;
    TWord tw("and");
    TWord tw1("her");
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.InsRecord("2", &tw1);
    EXPECT_EQ(nullptr, t.FindRecord("5"));
}

TEST(TListHash, cant_find_record_after_delete) {
    TListHash t;
    TWord tw("thumb");
    TWord tw1("In");
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.InsRecord("2", &tw1);
    t.DelRecord("2");
    EXPECT_EQ(nullptr, t.FindRecord("2"));
}

TEST(TListHash, reset_works_correct) {
    TListHash t;
    TWord tw("the");
    TWord tw1("shape");
    t.InsRecord("23", &tw);
    t.InsRecord("0C", &tw);
    t.InsRecord("4", &tw1);
    t.Reset();
    EXPECT_EQ("23", t.GetKey());
}

TEST(TListHash, can_go_next) {
    TListHash t;
    TWord tw("of an");
    TWord tw1("'L' on");
    t.InsRecord("23", &tw1);
    t.InsRecord("0C", &tw);
    t.InsRecord("2", &tw);
    t.Reset();
    t.GoNext();
    EXPECT_EQ("23", t.GetKey());
    t.GoNext();
    EXPECT_EQ("0C", t.GetKey());
}

TEST(TListHash, is_tab_ended_works_correct) {
    TListHash t;
    TWord tw("her");
    TWord tw1("forehead");
    t.InsRecord("23", &tw1);
    t.InsRecord("0C", &tw);
    t.InsRecord("2", &tw);
    t.Reset();
    t.GoNext();
    t.GoNext();
    EXPECT_EQ(0, t.IsTabEnded());
    t.GoNext();
    EXPECT_EQ(1, t.IsTabEnded());
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TEST(TBalanceTree, can_insert_record) {
    TBalanceTree t;
    TWord tw("East");
    ASSERT_NO_THROW(t.InsRecord("1", &tw));
}

TEST(TBalanceTree, cant_insert_record_with_existent_key) {
    TBalanceTree t;
    TWord tw("is");
    TWord tw1("up");
    t.InsRecord("1", &tw);
    ASSERT_ANY_THROW(t.InsRecord("1", &tw1));
}

TEST(TBalanceTree, can_find_record) {
    TBalanceTree t;
    TWord tw("I'm");
    TWord tw1("fearless");
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.InsRecord("2", &tw1);
    EXPECT_TRUE(tw1 == *((TWord*)t.FindRecord("2")));
}

TEST(TBalanceTree, cant_find_record_with_nonexistent_record) {
    TBalanceTree t;
    TWord tw("when");
    TWord tw1("I");
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.InsRecord("2", &tw1);
    EXPECT_EQ(nullptr, t.FindRecord("5"));
}


TEST(TBalanceTree, reset_works_correct) {
    TBalanceTree t;
    TWord tw("here");
    TWord tw1("this");
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.InsRecord("2", &tw1);
    t.Reset();
    EXPECT_EQ("1", t.GetKey());
}

TEST(TBalanceTree, can_go_next) {
    TBalanceTree t;
    TWord tw("on");
    TWord tw1("the");
    t.InsRecord("2", &tw1);
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.Reset();
    t.GoNext();
    EXPECT_EQ("2", t.GetKey());
    t.GoNext();
    EXPECT_EQ("4", t.GetKey());
}

TEST(TBalanceTree, is_list_ended_works_correct) {
    TBalanceTree t;
    TWord tw("low");
    TWord tw1("East is up...");
    t.InsRecord("2", &tw1);
    t.InsRecord("4", &tw);
    t.InsRecord("1", &tw);
    t.Reset();
    t.GoNext();
    EXPECT_EQ("2", t.GetKey());
    t.GoNext();
    EXPECT_EQ("4", t.GetKey());
    EXPECT_EQ(0, t.IsTabEnded());
    t.GoNext();
    EXPECT_EQ(1, t.IsTabEnded());
}
