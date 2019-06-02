#include "TListHash.h"
#include "gtest.h"

TEST(TListHash, can_create_table) {
	ASSERT_NO_THROW(TListHash tlh(5));
}

TEST(TListHash, can_insert_record_v1) {
	PTStudRec tsr = new TStudRec;
	TListHash tlh(8);
	tlh.InsRecord("4");
	tlh.InsRecord("8");
	tlh.InsRecord("1");
	tlh.InsRecord("6");
	tlh.InsRecord("5", tsr);
	tlh.InsRecord("7");
	tlh.InsRecord("3");

	EXPECT_EQ(7, tlh.GetDataCount());
	EXPECT_EQ(nullptr, tlh.FindRecord("6"));
	EXPECT_EQ(nullptr, tlh.FindRecord("10"));
	EXPECT_EQ(tsr, tlh.FindRecord("5"));

	tlh.InsRecord("11", tsr);
	EXPECT_EQ(8, tlh.GetDataCount());
	EXPECT_EQ(tsr, tlh.FindRecord("11"));
}

TEST(TListHash, can_delete_record) {
	PTStudRec tsr = new TStudRec;
	TListHash tlh(8);
	tlh.InsRecord("4");
	tlh.InsRecord("8");
	tlh.InsRecord("1");
	tlh.InsRecord("6");
	tlh.InsRecord("5", tsr);
	tlh.InsRecord("7");
	tlh.InsRecord("3");

	EXPECT_EQ(7, tlh.GetDataCount());

	tlh.DelRecord("5");
	EXPECT_EQ(6, tlh.GetDataCount());

	tlh.DelRecord("5");
	EXPECT_EQ(6, tlh.GetDataCount());

	EXPECT_EQ(0, tlh.IsEmpty());
}

TEST(TListHash, can_insert_record_v2) {
	PTStudRec tsr = new TStudRec;
	TListHash tlh(3);
	tlh.InsRecord("4");
	tlh.InsRecord("8");
	tlh.InsRecord("1");

	tlh.InsRecord("5", tsr);
	EXPECT_EQ(4, tlh.GetDataCount());
	EXPECT_EQ(tsr, tlh.FindRecord("5"));
}

TEST(TListHash, can_delete_record_v2) {
	PTStudRec tsr = new TStudRec;
	TListHash tlh(3);
	tlh.InsRecord("4");
	tlh.InsRecord("8");
	tlh.InsRecord("1");
	tlh.InsRecord("6");
	tlh.InsRecord("5", tsr);
	tlh.InsRecord("7");
	tlh.InsRecord("3");

	EXPECT_EQ(7, tlh.GetDataCount());
	EXPECT_EQ(tsr, tlh.FindRecord("5"));
	
	tlh.DelRecord("5");
	EXPECT_EQ(6, tlh.GetDataCount());
	EXPECT_EQ(nullptr, tlh.FindRecord("5"));
}

TEST(TListHash, iterator) {
	PTStudRec tsr = new TStudRec;
	TListHash tlh(8);
	tlh.InsRecord("4");
	tlh.InsRecord("8");
	tlh.InsRecord("1");
	tlh.InsRecord("6");
	tlh.InsRecord("5", tsr);
	tlh.InsRecord("7");
	tlh.InsRecord("3");
	tlh.InsRecord("2");

	int i = 0;
	for (tlh.Reset();!tlh.IsTabEnded();tlh.GoNext(), i++);
	EXPECT_EQ(8, i);
}