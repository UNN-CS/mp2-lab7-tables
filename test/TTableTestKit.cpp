#include <gtest.h>
#include <iostream>
#include <vector>
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"

TEST(TScanTable, Can_Create)
{
	ASSERT_NO_THROW(TScanTable tab(10));
}

TEST(TScanTable, Can_Insert)
{
	TScanTable tab(10);
	ASSERT_NO_THROW(tab.InsRecord("Ta-dam", nullptr));
}


TEST(TScanTable, Correct_Delete)
{
	TScanTable tab(10);
	tab.InsRecord("Ta-dam", nullptr);
	tab.DelRecord("Ta-dam");
	EXPECT_EQ(0, tab.GetDataCount());
}

TEST(TSortTable, Can_Create)
{
	ASSERT_NO_THROW(TSortTable tab(10));
}

TEST(TSortTable, Correct_Insert)
{
	TScanTable tab(10);
	tab.InsRecord("Oh", nullptr);
	tab.InsRecord("Here we go again", nullptr);
	EXPECT_NE(nullptr, tab.FindRecord("Oh"));
}

TEST(TSortTable, Correct_Delete)
{
	TScanTable tab(10);
	tab.InsRecord("One", nullptr);
	tab.InsRecord("Two", nullptr);
	tab.DelRecord("Two");
	EXPECT_EQ(nullptr, tab.FindRecord("Two"));
}

TEST(TTreeTable, Can_Create)
{
	ASSERT_NO_THROW(TTreeTable tree);
}

TEST(TTreeTable, Can_Insert)
{
	TTreeTable tree;
	ASSERT_NO_THROW(tree.InsRecord("Tryam", nullptr));
}

TEST(TTreeTable, Correct_Delete)
{
	TTreeTable tree;
	tree.InsRecord("TADAM", nullptr);
	tree.InsRecord("PAM PAM", nullptr);
	tree.DelRecord("TADAM");
	EXPECT_EQ(nullptr, tree.FindRecord("TADAM"));
}

TEST(TBalanceTree, Can_Create)
{
	ASSERT_NO_THROW(TBalanceTree tree);
}

TEST(TBalanceTree, Can_Insert)
{
	TBalanceTree tree;
	ASSERT_NO_THROW(tree.InsRecord("A", nullptr));
}

TEST(TBalanceTree, Correct_Delete)
{
	TBalanceTree tree;
	tree.InsRecord("AA", nullptr);
	tree.DelRecord("AA");
	EXPECT_EQ(nullptr, tree.FindRecord("AA"));
}

TEST(TArrayHash, Can_Create)
{
	TArrayHash arr(5, 3);
	ASSERT_NO_THROW(TArrayHash arr(5, 3););
}


TEST(TArrayHash, Can_Insert)
{
	TArrayHash arr(5, 3);
	ASSERT_NO_THROW(arr.InsRecord("Tessssst", nullptr));
}

TEST(TArrayHash, Can_Delete)
{
	TArrayHash arr(5, 3);
	arr.InsRecord("Tessssst", nullptr);
	arr.DelRecord("Tessssst");
	EXPECT_EQ(nullptr, arr.FindRecord("Tessssst"));
}

TEST(TListHash, Can_Create)
{
	TListHash list(5);
	ASSERT_NO_THROW(TListHash list(5););
}


TEST(TListHash, Can_Insert)
{
	TListHash list(5);
	ASSERT_NO_THROW(list.InsRecord("well", nullptr));
}

TEST(TListHash, Can_Delete)
{
	TListHash list(5);
	list.InsRecord("end", nullptr);
	list.DelRecord("end");
	EXPECT_EQ(nullptr, list.FindRecord("end"));
}