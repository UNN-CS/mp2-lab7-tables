#include "TBalanceTree.h"
#include "gtest.h"

TEST(TBalanceTree, can_create_table) {
	ASSERT_NO_THROW(TBalanceTree tbt);
}

TEST(TBalanceTree, default_constructor) {
	TBalanceTree tbt;

	EXPECT_EQ(0, tbt.GetDataCount());
	EXPECT_EQ(nullptr, tbt.GetValuePTR());
}

TEST(TBalanceTable, can_insert) {
	PTStudRec tsr = new TStudRec;
	TBalanceTree tbt;
	tbt.InsRecord("4");
	tbt.InsRecord("8");
	tbt.InsRecord("1");
	tbt.InsRecord("6");
    tbt.InsRecord("5", tsr);
	tbt.InsRecord("7");
	tbt.InsRecord("3");
	tbt.InsRecord("2");
	
	EXPECT_EQ(8, tbt.GetDataCount());
	EXPECT_EQ(tsr, tbt.FindRecord("5"));
	EXPECT_EQ(nullptr, tbt.FindRecord("10"));

	tbt.Reset();
	TKey tmp = tbt.GetKey();
	tbt.GoNext();
	for (;!tbt.IsTabEnded();tbt.GoNext())
	{
		EXPECT_EQ(1, tmp < tbt.GetKey());
		tmp = tbt.GetKey();
	}

	for (tbt.Reset();!tbt.IsTabEnded();tbt.GoNext())
	{
		EXPECT_EQ(1, tbt.GetBFct() < 2);
		EXPECT_EQ(1, tbt.GetBFct() > -2);
	}
}

TEST(TBalanceTree, can_delete) {
	PTStudRec tsr = new TStudRec;
	TBalanceTree tbt;
	tbt.InsRecord("4");
	tbt.InsRecord("8");
	tbt.InsRecord("1");
	tbt.InsRecord("6");
	tbt.InsRecord("5", tsr);
	tbt.InsRecord("7");
	tbt.InsRecord("3");
	tbt.InsRecord("2");

	tbt.DelRecord("6");
	EXPECT_EQ(7, tbt.GetDataCount());

	tbt.DelRecord("6");
	EXPECT_EQ(7, tbt.GetDataCount());

	tbt.Reset();
	TKey tmp = tbt.GetKey();
	tbt.GoNext();
	for (;!tbt.IsTabEnded();tbt.GoNext())
	{
		EXPECT_EQ(1, tmp < tbt.GetKey());
		tmp = tbt.GetKey();
	}

	for (tbt.Reset();!tbt.IsTabEnded();tbt.GoNext())
	{
		EXPECT_EQ(1, tbt.GetBFct() < 2);
		EXPECT_EQ(1, tbt.GetBFct() > -2);
	}
}