#include <gtest.h>
#include <iostream>
#include <vector>
#include <map>
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"

TEST(TScanTable, Can_Create)
{
    ASSERT_NO_THROW(TScanTable tab(4));
}

TEST(TScanTable, Can_Insert)
{
    TScanTable tab(4);
    ASSERT_NO_THROW(tab.InsRecord("Word", nullptr));
}

TEST(TScanTable, Cant_Add_in_Full_Table)
{
    TScanTable table(2);
    table.InsRecord("Where", nullptr);
    table.InsRecord("is", nullptr);
    ASSERT_ANY_THROW(table.InsRecord("Perry", nullptr));
}

TEST(TScanTable, Can_Find)
{
    TScanTable table(4);
    table.InsRecord("mushroom", nullptr);
    EXPECT_NE(nullptr, table.FindRecord("mushroom"));
}

TEST(TScanTable, Can_Delete)
{
    TScanTable table(4);
    table.InsRecord("mistake", nullptr);
    table.DelRecord("mistake");
    EXPECT_EQ(0, table.GetDataCount());
}

TEST(TScanTable, Cant_Find_After_Delete)
{
    TScanTable t;
    TScanTable table(4);
    table.InsRecord("mushroom", nullptr);
    table.DelRecord("mushroom");
    EXPECT_EQ(t.FindRecord("mushroom"), nullptr);
}
//------------------------------------------------
TEST(TSortTable, Can_Create)
{
    ASSERT_NO_THROW(TSortTable table(2));
}

TEST(TSortTable, Can_Create_From_TScanTable)
{
    TScanTable table(4);
    table.InsRecord("Hold", nullptr);
    table.InsRecord("the", nullptr);
    table.InsRecord("door", nullptr);
    ASSERT_NO_THROW(TSortTable sorttable(table, QUIQ_SORT));
}

TEST(TSortTable, can_assign_from_tscantable)
{
    TScanTable table(4);
    table.InsRecord("Hold", nullptr);
    table.InsRecord("the", nullptr);
    table.InsRecord("door", nullptr);
    TSortTable tab;
    ASSERT_NO_THROW(tab = table);
}

TEST(TSortTable, Can_Find)
{
    TScanTable table(4);
    table.InsRecord("Hold", nullptr);
    table.InsRecord("the", nullptr);
    table.InsRecord("door", nullptr);
    TSortTable tab(0);
    tab = table;
    EXPECT_NE(nullptr, tab.FindRecord("door"));
}

TEST(TSortTable, Can_Insert)
{
    TScanTable table(4);
    table.InsRecord("Wind", nullptr);
    table.InsRecord("of", nullptr);
    TSortTable tab(0);
    tab = table;
    tab.InsRecord("change", nullptr);
    EXPECT_NE(nullptr, tab.FindRecord("change"));
}

TEST(TSortTable, Cant_Insert_in_Full)
{
    TScanTable table(2);
    table.InsRecord("Hello", nullptr);
    table.InsRecord("World", nullptr);
    TSortTable tab(0);
    tab = table;
    ASSERT_ANY_THROW(tab.InsRecord("f", nullptr));
}

TEST(TSortTable, Can_Delete)
{
    TScanTable table(2);
    table.InsRecord("Jon", nullptr);
    table.InsRecord("Snow", nullptr);
    TSortTable tab(0);
    tab = table;
    tab.DelRecord("Snow");
    EXPECT_EQ(nullptr, tab.FindRecord("Snow"));
}
//---------------------------------------------
TEST(TTreeTable, Can_Create)
{
    ASSERT_NO_THROW(TTreeTable tree);
}

TEST(TTreeTable, Can_Insert)
{
    TTreeTable tree;
    ASSERT_NO_THROW(tree.InsRecord("hi", nullptr));
}

TEST(TTreeTable, Can_Find)
{
    TTreeTable tree;
    tree.InsRecord("Pretty", nullptr);
    tree.InsRecord("woman", nullptr);
    EXPECT_NE(nullptr, tree.FindRecord("woman"));
}

TEST(TTreeTable, Can_Delete)
{
    TTreeTable tree;
    tree.InsRecord("You", nullptr);
    tree.InsRecord("know", nullptr);
    tree.InsRecord("nothing", nullptr);
    tree.DelRecord("You");
    EXPECT_NE(nullptr, tree.FindRecord("know"));
    EXPECT_NE(nullptr, tree.FindRecord("nothing"));
    EXPECT_EQ(nullptr, tree.FindRecord("You"));
}
//------------------------------------------------
TEST(TBalanceTree, Can_Insert)
{
    TBalanceTree tree;
    ASSERT_NO_THROW(tree.InsRecord("hi", nullptr));
}

TEST(TBalanceTree, Can_Find)
{
    TBalanceTree tree;
    tree.InsRecord("Zhulik", nullptr);
    EXPECT_NE(nullptr, tree.FindRecord("Zhulik"));
}

TEST(TBalanceTree, Can_Delete)
{
    TBalanceTree tree;
    tree.InsRecord("rrr", nullptr);
    tree.DelRecord("rrr");
    EXPECT_EQ(nullptr, tree.FindRecord("rrr"));
}
//-----------------------------------------------
TEST(TArrayHash, Can_Insert)
{
    TArrayHash ah(7, 3);
    ASSERT_NO_THROW(ah.InsRecord("bye", nullptr));
}

TEST(TArrayHash, Can_Find)
{
    TArrayHash ah(7, 3);
    ah.InsRecord("socks", nullptr);
    EXPECT_NE(nullptr, ah.FindRecord("socks"));
}

TEST(TArrayHash, Can_Delete)
{
    TArrayHash ah(7, 3);
    ah.InsRecord("rrr", nullptr);
    ah.DelRecord("rrr");
    EXPECT_EQ(nullptr, ah.FindRecord("rrr"));
}
//---------------------------------------------
TEST(TListHash, Can_Insert)
{
    TListHash lh(5);
    ASSERT_NO_THROW(lh.InsRecord("well", nullptr));
}

TEST(TListHash, Can_Find)
{
    TListHash lh(5);
    lh.InsRecord("tired", nullptr);
    EXPECT_NE(nullptr, lh.FindRecord("tired"));

}

TEST(TListHash, Can_Delete)
{
    TListHash lh(5);
    lh.InsRecord("done", nullptr);
    lh.DelRecord("done");
    EXPECT_EQ(nullptr, lh.FindRecord("done"));
}