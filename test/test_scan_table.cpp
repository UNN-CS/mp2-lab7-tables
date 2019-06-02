#include "TScanTable.h"
#include "gtest.h"

TEST(TScanTable, created_table_is_empty) {
	TScanTable tst;

	EXPECT_EQ(1, tst.IsEmpty());
	EXPECT_EQ(0, tst.GetDataCount());
}

TEST(TScanTable, can_insert_record) {
	TScanTable tst;
	tst.InsRecord("1",NULL);

	EXPECT_EQ(0, tst.IsEmpty());
	EXPECT_EQ(1, tst.GetDataCount());
}

TEST(TScanTable, can_del_record) {
	TScanTable tst;
	tst.InsRecord("1", NULL);
	tst.InsRecord("2", NULL);
	tst.DelRecord("2");

	EXPECT_EQ(0, tst.IsFull());
	EXPECT_EQ(1, tst.GetDataCount());
	EXPECT_EQ(NULL, tst.FindRecord("2"));
}

TEST(TScanTable, can_find_record) {
	PTStudRec ptsr = new TStudRec;
	TScanTable tst;
	tst.InsRecord("1", NULL);
	tst.InsRecord("2", ptsr);
	tst.InsRecord("3", NULL);

	EXPECT_NE(nullptr, tst.FindRecord("2"));
}

TEST(TScanTable, can_set_current_record) {
	PTStudRec ptsr = new TStudRec;
	TScanTable tst;
	tst.InsRecord("1", NULL);
	tst.InsRecord("2", ptsr);
	tst.InsRecord("3", NULL);

	tst.SetCurrentPos(1);
	EXPECT_EQ("2", tst.GetKey(CURRENT_POS));
	EXPECT_EQ(ptsr, tst.GetValuePTR(CURRENT_POS));
}

TEST(TScanTable, can_get_key_and_ptrvalue) {
	PTStudRec ptsr = new TStudRec;
	TScanTable tst;
	tst.InsRecord("1", NULL);
	tst.InsRecord("2", NULL);
	tst.InsRecord("3", ptsr);

	EXPECT_EQ("1", tst.GetKey(FIRST_POS));
	EXPECT_EQ(NULL, tst.GetValuePTR(FIRST_POS));
	EXPECT_EQ("3", tst.GetKey(LAST_POS));
	EXPECT_EQ(ptsr, tst.GetValuePTR(LAST_POS));
}
