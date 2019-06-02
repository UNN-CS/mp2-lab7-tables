#include "TBalanceNode.h"
#include "gtest.h"

TEST(TBalanceNode, can_create_node) {
	ASSERT_NO_THROW(TBalanceNode tbn);
}

TEST(TBalanceNode, parameterized_constructor) {
	TBalanceNode tbn1;
	EXPECT_EQ("", tbn1.GetKey());
	EXPECT_EQ(nullptr, tbn1.GetValuePTR());
	EXPECT_EQ(nullptr, tbn1.GetLeft());
	EXPECT_EQ(nullptr, tbn1.GetRight());
	EXPECT_EQ(BalOk, tbn1.GetBalance());

	PTStudRec tsr = new TStudRec;
	PTBalanceNode l = new TBalanceNode;
	PTBalanceNode r = new TBalanceNode;
	TBalanceNode tbn2("node", tsr, l, r,1);

	EXPECT_EQ("node", tbn2.GetKey());
	EXPECT_EQ(tsr, tbn2.GetValuePTR());
	EXPECT_EQ(l, tbn2.GetLeft());
	EXPECT_EQ(r, tbn2.GetRight());
	EXPECT_EQ(1, tbn2.GetBalance());
}