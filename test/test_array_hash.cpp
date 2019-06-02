#include "TArrayHash.h"
#include "gtest.h"

TEST(TArrayHash, can_create_table) {
	ASSERT_NO_THROW(TArrayHash tah(5));
}

TEST(TArrayHash, can_insert_record_v1) {
	PTStudRec tsr = new TStudRec;
	TArrayHash tah(8);
	tah.InsRecord("4");
	tah.InsRecord("8");
	tah.InsRecord("1");
	tah.InsRecord("6");
	tah.InsRecord("5", tsr);
	tah.InsRecord("7");
	tah.InsRecord("3");

	EXPECT_EQ(7, tah.GetDataCount());
	EXPECT_EQ(nullptr, tah.FindRecord("6"));
	EXPECT_EQ(nullptr, tah.FindRecord("10"));
	EXPECT_EQ(tsr, tah.FindRecord("5"));
	EXPECT_EQ(0, tah.IsFull());

	tah.InsRecord("11",tsr);
	EXPECT_EQ(8, tah.GetDataCount());
	EXPECT_EQ(1, tah.IsFull());
	EXPECT_EQ(tsr, tah.FindRecord("11"));
}

TEST(TArrayHash, can_delete_record) {
	PTStudRec tsr = new TStudRec;
	TArrayHash tah(8);
	tah.InsRecord("4");
	tah.InsRecord("8");
	tah.InsRecord("1");
	tah.InsRecord("6");
	tah.InsRecord("5", tsr);
	tah.InsRecord("7");
	tah.InsRecord("3");

	EXPECT_EQ(7, tah.GetDataCount());
	
	tah.DelRecord("5");
	EXPECT_EQ(6, tah.GetDataCount());

	tah.DelRecord("5");
	EXPECT_EQ(6, tah.GetDataCount());

	EXPECT_EQ(0, tah.IsEmpty());
}

TEST(TArrayHash, can_insert_record_v2) {
	PTStudRec tsr = new TStudRec;
	TArrayHash tah(3);
	tah.InsRecord("4");
	tah.InsRecord("8", tsr);
	tah.InsRecord("1");

	tah.InsRecord("5", tsr);
	EXPECT_EQ(3, tah.GetDataCount());
	EXPECT_EQ(nullptr, tah.FindRecord("5"));

	tah.DelRecord("8");
	tah.InsRecord("5", tsr);
	EXPECT_EQ(3, tah.GetDataCount());
	EXPECT_EQ(tsr, tah.FindRecord("5"));
}


TEST(TArrayHash, iterator) {
	PTStudRec tsr = new TStudRec;
	TArrayHash tah(8);
	tah.InsRecord("4");
	tah.InsRecord("8");
	tah.InsRecord("1");
	tah.InsRecord("6");
	tah.InsRecord("5", tsr);
	tah.InsRecord("7");
	tah.InsRecord("3");
	tah.InsRecord("2");
	
	int i = 0;
	for (tah.Reset();!tah.IsTabEnded();tah.GoNext(), i++);
	EXPECT_EQ(8, i);
}


