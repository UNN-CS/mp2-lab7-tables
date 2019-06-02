#include <gtest.h>
#include <string>
#include <iostream>

#include "TBalanceNode.h"
#include "TBalanceTree.h"
#include "TTreeNode.h"
#include "TTreeTable.h"
#include "TArrayHash.h"
#include "TListHash.h"
#include "TSortTable.h"
#include "TTabRecord.h"

TEST(TBalanceNode, Can_Create_TBalanceNode)
{
    ASSERT_NO_THROW(TBalanceNode bn);
}

TEST(TBalanceNode, Can_SetBalance)
{
    TBalanceNode bn;

    ASSERT_NO_THROW(bn.SetBalance(1));
}

TEST(TBalanceNode, Can_GetBalance)
{
    TBalanceNode bn;
    bn.SetBalance(1);

    EXPECT_EQ(bn.GetBalance(), 1);
}

TEST(TBalanceTree, Can_Create_BalanceTree)
{
    ASSERT_NO_THROW(TBalanceTree bt);
}

TEST(TBalanceTree, Can_InsRecord_In_BalanceTree)
{
    TBalanceTree bt;

    ASSERT_NO_THROW(bt.InsRecord("1", nullptr));
}

TEST(TBalanceTree, Cant_InsRecord_With_Existing_Key)
{
    TBalanceTree bt;
    bt.InsRecord("1", nullptr);
    bt.InsRecord("2", nullptr);
    bt.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(bt.InsRecord("2", nullptr));
}

TEST(TBalanceTree, Can_FindRecord_In_BalanceTree)
{
    TBalanceTree bt;
    bt.InsRecord("1", nullptr);
    bt.InsRecord("2", nullptr);
    bt.InsRecord("3", nullptr);

    ASSERT_NO_THROW(bt.FindRecord("2"));
}

TEST(TBalanceTree, Cant_FindRecord_In_Empty_BalanceTree)
{
    TBalanceTree bt;

    ASSERT_ANY_THROW(bt.FindRecord("34"));
}

TEST(TBalanceTree, Cant_FindRecord_When_Key_Doesnot_Exist)
{
    TBalanceTree bt;
    bt.InsRecord("1", nullptr);

    ASSERT_ANY_THROW(bt.FindRecord("2"));
}

TEST(TBalanceTree, BalanceTree_IsEmpty_Returns_True_When_Empty)
{
    TBalanceTree bt;

    EXPECT_TRUE(bt.IsEmpty());
}

TEST(TBalanceTree, BalanceTree_Sorted)
{
    TBalanceTree bt;
    bt.InsRecord("3", nullptr);
    bt.InsRecord("1", nullptr);
    bt.InsRecord("4", nullptr);
    bt.InsRecord("2", nullptr);

    bt.Reset();
    EXPECT_EQ(bt.GetKey(), "1");
    bt.GoNext();
    EXPECT_EQ(bt.GetKey(), "2");
    bt.GoNext();
    EXPECT_EQ(bt.GetKey(), "3");
    bt.GoNext();
    EXPECT_EQ(bt.GetKey(), "4");
    bt.GoNext();

    EXPECT_TRUE(bt.IsTabEnded());
}

TEST(TBalanceTree, Cant_DelRecord_In_Empty_BalanceTree)
{
    TBalanceTree bt;

    ASSERT_ANY_THROW(bt.DelRecord("1"));
}

TEST(TBalanceTree, Cant_DelRecord_When_Key_Doesnot_Exist)
{
    TBalanceTree bt;
    bt.InsRecord("1", nullptr);

    ASSERT_ANY_THROW(bt.DelRecord("2"));
}

TEST(TBalanceTree, Can_DelRecord)
{
    TBalanceTree bt;
    bt.InsRecord("1", nullptr);

    ASSERT_NO_THROW(bt.DelRecord("1"));
}

TEST(TBalanceTree, DelRecord_Delete_Record)
{
    TBalanceTree bt;
    bt.InsRecord("1", nullptr);
    bt.InsRecord("2", nullptr);
    bt.InsRecord("3", nullptr);

    bt.DelRecord("1");
    bt.DelRecord("2");
    bt.DelRecord("3");

    EXPECT_EQ(1, bt.IsEmpty());
}

TEST(TBalanceTree, DelRecord_Works_Correctly)
{
    TBalanceTree bt;
    bt.InsRecord("4", nullptr);
    bt.InsRecord("3", nullptr);
    bt.InsRecord("1", nullptr);
    bt.InsRecord("2", nullptr);

    bt.DelRecord("2");

    bt.Reset();
    EXPECT_EQ(bt.GetKey(), "1");
    bt.GoNext();
    EXPECT_EQ(bt.GetKey(), "3");
    bt.GoNext();
    EXPECT_EQ(bt.GetKey(), "4");
}

TEST(TTreeNode, Can_Create_TreeNode)
{
    ASSERT_NO_THROW(TTreeNode ttn);
}

TEST(TTreeNode, Can_GetLeft)
{
    TTreeNode left("", nullptr, nullptr, nullptr);
    TTreeNode node("", nullptr, &left, nullptr);

    EXPECT_EQ(node.GetLeft(), &left);
}

TEST(TTreeNode, Can_GetRight)
{
    TTreeNode right("", nullptr, nullptr, nullptr);
    TTreeNode node("", nullptr, nullptr, &right);

    EXPECT_EQ(node.GetRight(), &right);
}

TEST(TTreeTable, Can_Create_TreeTable) {
    ASSERT_NO_THROW(TTreeTable());
}

TEST(TTreeTable, Can_InsRecord)
{
    TTreeTable tree;

    ASSERT_NO_THROW(tree.InsRecord("1", nullptr));
}

TEST(TTreeTable, Cant_InsRecord_When_Key_Already_Taken)
{
    TTreeTable tree;
    tree.InsRecord("1", nullptr);

    ASSERT_ANY_THROW(tree.InsRecord("1", nullptr));
}

TEST(TTreeTable, Can_FindRecord)
{
    TTreeTable tree;
    tree.InsRecord("1", nullptr);

    EXPECT_EQ(tree.FindRecord("1"), nullptr);
}

TEST(TTreeTable, Cant_Find_Record_When_It_Isnt_In_Table)
{
    TTreeTable tree;

    ASSERT_ANY_THROW(tree.FindRecord("34"));
}

TEST(TTreeTable, Can_DelRecord)
{
    TTreeTable tree;
    tree.InsRecord("1", nullptr);

    ASSERT_NO_THROW(tree.DelRecord("1"));
}

TEST(TTreeTable, Cant_DelRecord_When_It_Isnt_In_Table)
{
    TTreeTable tree;
    tree.InsRecord("1", nullptr);

    ASSERT_ANY_THROW(tree.DelRecord("2"));
}

TEST(TTreeTable, DelRecord_Works_Correctly)
{
    TTreeTable tree;
    tree.InsRecord("1", nullptr);
    tree.InsRecord("2", nullptr);
    tree.InsRecord("3", nullptr);

    tree.DelRecord("1");
    tree.DelRecord("2");
    tree.DelRecord("3");

    EXPECT_TRUE(tree.IsEmpty());
}

TEST(TTreeTable, DelRecord_Works_Correctly2)
{
    TTreeTable tree;
    tree.InsRecord("4", nullptr);
    tree.InsRecord("3", nullptr);
    tree.InsRecord("1", nullptr);
    tree.InsRecord("2", nullptr);

    tree.DelRecord("2");

    tree.Reset();
    EXPECT_EQ(tree.GetKey(), "1");
    tree.GoNext();
    EXPECT_EQ(tree.GetKey(), "3");
    tree.GoNext();
    EXPECT_EQ(tree.GetKey(), "4");
}

TEST(TListHash, Can_Create__ListHash)
{
    ASSERT_NO_THROW(TListHash lh);
}

TEST(TListHash, Cant_Create_ListHash_With_Negative_Size)
{
    ASSERT_ANY_THROW(TListHash lh(-2));
}

TEST(TListHash, Cant_Create_ListHash_With_Too_Large_Size)
{
    ASSERT_ANY_THROW(TListHash lh(TabMaxSize + 1));
}

TEST(TListHash, Can_InsRecord)
{
    TListHash lh;

    ASSERT_NO_THROW(lh.InsRecord("1", nullptr));
}

TEST(TListHash, Cant_InsRecord_When_Is_Full)
{
    TListHash lh(3);
    lh.InsRecord("1", nullptr);
    lh.InsRecord("2", nullptr);
    lh.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(lh.InsRecord("4", nullptr));
}

TEST(TListHash, Cant_InsRecord_When_Key_Exists)
{
    TListHash lh;
    lh.InsRecord("1", nullptr);
    lh.InsRecord("2", nullptr);
    lh.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(lh.InsRecord("3", nullptr));
}

TEST(TListHash, Can_FindRecord)
{
    TListHash lh;
    lh.InsRecord("1", nullptr);

    ASSERT_NO_THROW(lh.FindRecord("1"));
}

TEST(TListHash, Cant_Find_Record_When_Is_Empty)
{
    TListHash lh;

    ASSERT_ANY_THROW(lh.FindRecord("4"));
}

TEST(TListHash, Cant_FindRecord_When_Key_Doesnot_Exists)
{
    TListHash lh;
    lh.InsRecord("1", nullptr);
    lh.InsRecord("2", nullptr);
    lh.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(lh.FindRecord("4"));
}

TEST(TListHash, Can_DelRecord)
{
    TListHash lh;
    lh.InsRecord("1", nullptr);

    ASSERT_NO_THROW(lh.DelRecord("1"));
}

TEST(TListHash, Cant_DelRecord_When_Is_Empty)
{
    TListHash lh;

    ASSERT_ANY_THROW(lh.DelRecord("4"));
}

TEST(TListHash, Cant_DelRecord_When_Key_Doenot_Exists)
{
    TListHash lh;
    lh.InsRecord("1", nullptr);
    lh.InsRecord("2", nullptr);
    lh.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(lh.DelRecord("4"));
}

TEST(TListHash, DelRecord_Works_Correctly)
{
    TListHash lh;
    lh.InsRecord("1", nullptr);
    lh.InsRecord("2", nullptr);
    lh.InsRecord("3", nullptr);

    lh.DelRecord("1");
    lh.DelRecord("2");
    lh.DelRecord("3");

    EXPECT_EQ(1, lh.IsEmpty());
}


TEST(TArrayHash, Can_Create_ArrayHash)
{
    ASSERT_NO_THROW(TArrayHash ah);
}

TEST(TArrayHash, Cant_Create_ArrayHash_With_Negative_Size)
{
    ASSERT_ANY_THROW(TArrayHash ah(-2));
}

TEST(TArrayHash, Cant_Create_ArrayHash_With_Too_Large_Size)
{
    ASSERT_ANY_THROW(TArrayHash ah(TabMaxSize + 1));
}

TEST(TArrayHash, Cant_Create_ArrayHash_With_Step_Less_One)
{
    ASSERT_ANY_THROW(TArrayHash ah(2, 0));
}

TEST(TArrayHash, Cant_Create_ArrayHash_With_Too_Large_Step)
{
    ASSERT_ANY_THROW(TArrayHash ah(2, 3));
}

TEST(TArrayHash, Can_FindRecord)
{
    TArrayHash ah;
    ah.InsRecord("1", nullptr);

    ASSERT_NO_THROW(ah.FindRecord("1"));
}

TEST(TArrayHash, Cant_FindRecord_When_Is_Empty)
{
    TArrayHash ah;

    ASSERT_ANY_THROW(ah.FindRecord("1"));
}

TEST(TArrayHash, Cant_FindRecord_If_Key_Doesnot_Exists)
{
    TArrayHash ah;
    ah.InsRecord("1", nullptr);
    ah.InsRecord("2", nullptr);
    ah.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(ah.FindRecord("4"));
}

TEST(TArrayHash, Can_InsRecord)
{
    TArrayHash ah;

    ASSERT_NO_THROW(ah.InsRecord("1", nullptr));
}

TEST(TArrayHash, Cant_InsRecord_When_Is_Full)
{
    TArrayHash ah(3, 1);
    ah.InsRecord("1", nullptr);
    ah.InsRecord("2", nullptr);
    ah.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(ah.InsRecord("4", nullptr));
}

TEST(TArrayHash, Cant_InsRecord_When_Key_Exists)
{
    TArrayHash ah;
    ah.InsRecord("1", nullptr);
    ah.InsRecord("2", nullptr);
    ah.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(ah.InsRecord("3", nullptr));
}

TEST(TArrayHash, Can_DelRecord)
{
    TArrayHash ah;
    ah.InsRecord("1", nullptr);

    ASSERT_NO_THROW(ah.DelRecord("1"));
}

TEST(TArrayHash, Cant_DelRecord_When_Is_Empty)
{
    TArrayHash ah;

    ASSERT_ANY_THROW(ah.DelRecord("1"));
}

TEST(TArrayHash, Cant_DelRecord_If_Key_Doesnot_Exists)
{
    TArrayHash ah;
    ah.InsRecord("1", nullptr);
    ah.InsRecord("2", nullptr);
    ah.InsRecord("3", nullptr);

    ASSERT_ANY_THROW(ah.DelRecord("4"));
}

TEST(TArrayHash, DelRecord_Works_Correctly)
{
    TArrayHash ah;
    ah.InsRecord("1", nullptr);
    ah.InsRecord("2", nullptr);
    ah.InsRecord("3", nullptr);

    ah.DelRecord("1");
    ah.DelRecord("2");
    ah.DelRecord("3");

    EXPECT_TRUE(ah.IsEmpty());
}


TEST(TSortTable, Can_Create_Sort_Table)
{
    ASSERT_NO_THROW(TSortTable());
}

TEST(TSortTable, Cant_Create_Sort_Table_With_Negative_Size) {
    ASSERT_ANY_THROW(TSortTable(-10));
}

TEST(TSortTable, Cant_Create_Sort_Table_With_Too_Large_Size) {
    ASSERT_ANY_THROW(TSortTable(TabMaxSize + 1));
}

TEST(TSortTable, Can_Create_Sort_Table_From_Scan_Table) {
    TScanTable st(1);
    st.InsRecord("iv", nullptr);

    ASSERT_NO_THROW(TSortTable sort(st));
}

TEST(TSortTable, Can_SetSortMethod) {
    TSortTable sort;

    ASSERT_NO_THROW(sort.SetSortMethod(INSERT_SORT););
}

TEST(TSortTable, Can_GetSortMethod) {
    TSortTable sort;
    TSortMethod sm = MERGE_SORT;
    sort.SetSortMethod(sm);

    EXPECT_EQ(sm, sort.GetSortMethod());
}

TEST(TSortTable, Can_Assign_Sort_Table_From_Scan_Table) {
    TScanTable st(1);
    st.InsRecord("iv", nullptr);
    TSortTable sort;
    sort.SetSortMethod(INSERT_SORT);

    ASSERT_NO_THROW(sort = st);
}

TEST(TSortTable, Create_Sort_Table_From_Scan_Table) {
    TScanTable st(5);
    std::string s[] = { "a", "b", "c", "d", "e" };
    st.InsRecord("c", nullptr);
    st.InsRecord("e", nullptr);
    st.InsRecord("d", nullptr);
    st.InsRecord("b", nullptr);
    st.InsRecord("a", nullptr);
    TSortTable sort;
    sort.SetSortMethod(INSERT_SORT);
    sort = st;
    sort.Reset();
    for (int i = 0; i < 5; i++) {
        EXPECT_TRUE(s[i] == sort.GetKey());
        sort.GoNext();
    }
}

TEST(TSortTable, Correct_Merge_Sort_Of_Table) {
    TScanTable st(5);
    std::string s[] = { "a", "b", "c", "d", "e" };
    st.InsRecord("c", nullptr);
    st.InsRecord("e", nullptr);
    st.InsRecord("d", nullptr);
    st.InsRecord("b", nullptr);
    st.InsRecord("a", nullptr);
    TSortTable sort;
    sort.SetSortMethod(MERGE_SORT);
    sort = st;
    sort.Reset();
    for (int i = 0; i < 5; i++) {
        EXPECT_TRUE(s[i] == sort.GetKey());
        sort.GoNext();
    }
}

TEST(TSortTable, Correct_Quiq_Sort_Of_Table) {
    TScanTable st(5);
    std::string s[] = { "a", "b", "c", "d", "e" };
    st.InsRecord("c", nullptr);
    st.InsRecord("e", nullptr);
    st.InsRecord("d", nullptr);
    st.InsRecord("b", nullptr);
    st.InsRecord("a", nullptr);
    TSortTable sort;
    sort.SetSortMethod(QUIQ_SORT);
    sort = st;
    sort.Reset();
    for (int i = 0; i < 5; i++) {
        EXPECT_TRUE(s[i] == sort.GetKey());
        sort.GoNext();
    }
}

TEST(TSortTable, Can_InsRecord) {
    TSortTable sort;
    sort.SetSortMethod(INSERT_SORT);

    ASSERT_NO_THROW(sort.InsRecord("c", nullptr));
}

TEST(TSortTable, Cant_InsRecord_When_Key_Exists) {
    TSortTable sort;
    sort.SetSortMethod(INSERT_SORT);
    sort.InsRecord("c", nullptr);

    ASSERT_ANY_THROW(sort.InsRecord("c", nullptr));
}

TEST(TSortTable, Can_FindRecord) {
    TSortTable sort;
    sort.InsRecord("a", PTDatValue(1));

    EXPECT_EQ(sort.FindRecord("a"), PTDatValue(1));
}

TEST(TSortTable, Cant_FindRecord_When_It_Isnt_In_Table) {
    TSortTable sort;
    sort.InsRecord("a", PTDatValue(1));

    ASSERT_ANY_THROW(sort.FindRecord("b"));
}

TEST(TSortTable, Can_DelRecord) {
    TSortTable sort;
    sort.InsRecord("a", nullptr);

    ASSERT_NO_THROW(sort.DelRecord("a"));
}

TEST(TSortTable, Cant_DelRecord_When_No_Record) {
    TSortTable sort;
    sort.InsRecord("b", nullptr);

    ASSERT_ANY_THROW(sort.DelRecord("a"));
}

TEST(TSortTable, Cant_DelRecord_When_Is_Empty) {
    TSortTable sort;

    ASSERT_ANY_THROW(sort.DelRecord("a"));
}