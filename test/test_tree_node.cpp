#include "TTreeNode.h"
#include "gtest.h"

TEST(TTreeNode, can_create_node) {
	ASSERT_NO_THROW(TTreeNode tn);
}

TEST(TTreeNode, parameterized_constructor) {
	TTreeNode tn1;
	EXPECT_EQ("", tn1.GetKey());
	EXPECT_EQ(nullptr, tn1.GetValuePTR());
	EXPECT_EQ(nullptr, tn1.GetLeft());
	EXPECT_EQ(nullptr, tn1.GetRight());

	PTStudRec tsr = new TStudRec;
	PTTreeNode l = new TTreeNode;
	PTTreeNode r = new TTreeNode;
	TTreeNode tn2("node", tsr, l, r);
	
	EXPECT_EQ("node", tn2.GetKey());
	EXPECT_EQ(tsr, tn2.GetValuePTR());
	EXPECT_EQ(l, tn2.GetLeft());
	EXPECT_EQ(r, tn2.GetRight());
}