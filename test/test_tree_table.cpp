#include "TTreeTable.h"
#include "gtest.h"

TEST(TTreeTable, can_create_table) {
	ASSERT_NO_THROW(TTreeTable ttt);
}

TEST(TTreeTable, default_constructor) {
	TTreeTable ttt;

	EXPECT_EQ(0, ttt.GetDataCount());
	EXPECT_EQ(nullptr, ttt.GetValuePTR());
}

TEST(TTreeTable, can_insert) {
	PTStudRec tsr = new TStudRec;
	TTreeTable ttt;
	ttt.InsRecord("4");
	ttt.InsRecord("8");
	ttt.InsRecord("1");
	ttt.InsRecord("6");
	ttt.InsRecord("5", tsr);
	ttt.InsRecord("7");
	ttt.InsRecord("3");
	ttt.InsRecord("2");

	EXPECT_EQ(8, ttt.GetDataCount());
	EXPECT_EQ(tsr, ttt.FindRecord("5"));
	EXPECT_EQ(nullptr, ttt.FindRecord("10"));

	ttt.Reset();
	TKey tmp = ttt.GetKey();
	ttt.GoNext();
	for (;!ttt.IsTabEnded();ttt.GoNext())
	{
		EXPECT_EQ(1, tmp < ttt.GetKey());
		tmp = ttt.GetKey();
	}
}

TEST(TTreeTable, can_delete) {
	PTStudRec tsr = new TStudRec;
	TTreeTable ttt;
	ttt.InsRecord("4");
	ttt.InsRecord("8");
	ttt.InsRecord("1");
	ttt.InsRecord("6");
	ttt.InsRecord("5", tsr);
	ttt.InsRecord("7");
	ttt.InsRecord("3");
	ttt.InsRecord("2");

	ttt.DelRecord("6");
	EXPECT_EQ(7, ttt.GetDataCount());
	
	ttt.DelRecord("6");
	EXPECT_EQ(7, ttt.GetDataCount());

	ttt.Reset();
	TKey tmp = ttt.GetKey();
	ttt.GoNext();
	for (;!ttt.IsTabEnded();ttt.GoNext())
	{
		EXPECT_EQ(1, tmp < ttt.GetKey());
		tmp = ttt.GetKey();
	}
}