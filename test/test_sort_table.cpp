#include "TSortTable.h"
#include "gtest.h"

TEST(TSortTable, default_constructor) {
	ASSERT_NO_THROW(TSortTable tsorttable);
}

TEST(TSortTable, converting_constructor) {
	TScanTable tst;
	tst.InsRecord("91", NULL);
	tst.InsRecord("82", NULL);
	tst.InsRecord("73", NULL);
	tst.InsRecord("64", NULL);
	tst.InsRecord("55", NULL);
	tst.InsRecord("46", NULL);
	tst.InsRecord("37", NULL);
	tst.InsRecord("28", NULL);

	TSortTable tsorttable(tst);
	EXPECT_EQ(8, tsorttable.GetDataCount());
	EXPECT_NE(&tst, &tsorttable);
}

/*TEST(TSortTable, assign_operator) {
	TScanTable tst;
	tst.InsRecord("91", NULL);
	tst.InsRecord("82", NULL);
	tst.InsRecord("73", NULL);
	tst.InsRecord("64", NULL);
	tst.InsRecord("55", NULL);
	tst.InsRecord("46", NULL);
	tst.InsRecord("37", NULL);
	tst.InsRecord("28", NULL);

	TSortTable tsorttable;
	ASSERT_NO_THROW(tsorttable = tst);
	EXPECT_EQ(8, tsorttable.GetDataCount());
	EXPECT_NE(&tst, &tsorttable);
}*/

TEST(TSortTable, insert_sort) {
	TScanTable tst;
	tst.InsRecord("4", NULL);
	tst.InsRecord("8", NULL);
	tst.InsRecord("1", NULL);
	tst.InsRecord("6", NULL);
	tst.InsRecord("5", NULL);
	tst.InsRecord("7", NULL);
	tst.InsRecord("3", NULL);
	tst.InsRecord("2", NULL);

	TSortTable tsorttable(tst);
	tsorttable.SetSortMethod(INSERT_SORT);
	tsorttable.Reset();
	TKey tmp = tsorttable.GetKey();
	tsorttable.GoNext();
	for (;!tsorttable.IsTabEnded();tsorttable.GoNext())
		EXPECT_EQ(1, tmp<tsorttable.GetKey());
}

TEST(TSortTable, merge_sort) {
	TScanTable tst;
	tst.InsRecord("4", NULL);
	tst.InsRecord("8", NULL);
	tst.InsRecord("1", NULL);
	tst.InsRecord("6", NULL);
	tst.InsRecord("5", NULL);
	tst.InsRecord("7", NULL);
	tst.InsRecord("3", NULL);
	tst.InsRecord("2", NULL);

	TSortTable tsorttable(tst);
	tsorttable.SetSortMethod(MERGE_SORT);
	tsorttable.Reset();
	TKey tmp = tsorttable.GetKey();
	tsorttable.GoNext();
	for (;!tsorttable.IsTabEnded();tsorttable.GoNext())
		EXPECT_EQ(1, tmp < tsorttable.GetKey());
}

TEST(TSortTable, quick_sort) {
	TScanTable tst;
	tst.InsRecord("4", NULL);
	tst.InsRecord("8", NULL);
	tst.InsRecord("1", NULL);
	tst.InsRecord("6", NULL);
	tst.InsRecord("5", NULL);
	tst.InsRecord("7", NULL);
	tst.InsRecord("3", NULL);
	tst.InsRecord("2", NULL);

	TSortTable tsorttable(tst);
	tsorttable.SetSortMethod(QUIQ_SORT);
	tsorttable.Reset();
	TKey tmp = tsorttable.GetKey();
	tsorttable.GoNext();
	for (;!tsorttable.IsTabEnded();tsorttable.GoNext())
		EXPECT_EQ(1, tmp < tsorttable.GetKey());
}

TEST(TSortTable, can_find_record) {
	PTStudRec ptsr = new TStudRec;
	TScanTable tst;
	tst.InsRecord("4", NULL);
	tst.InsRecord("8", NULL);
	tst.InsRecord("1", NULL);
	tst.InsRecord("6", ptsr);
	tst.InsRecord("5", NULL);
	tst.InsRecord("7", NULL);
	tst.InsRecord("3", NULL);
	tst.InsRecord("2", NULL);

	TSortTable tsorttable(tst);

	EXPECT_EQ(ptsr, tsorttable.FindRecord("6"));
	EXPECT_EQ(nullptr, tsorttable.FindRecord("10"));
}

TEST(TSortTable, can_insert_record) {
	PTStudRec ptsr = new TStudRec;
	TScanTable tst;
	tst.InsRecord("4", NULL);
	tst.InsRecord("8", NULL);
	tst.InsRecord("1", NULL);
	tst.InsRecord("5", NULL);
	tst.InsRecord("7", NULL);
	tst.InsRecord("3", NULL);
	tst.InsRecord("2", NULL);

	TSortTable tsortt(tst);
	EXPECT_EQ(7, tsortt.GetDataCount());
	tsortt.InsRecord("6", ptsr);

	EXPECT_EQ(8, tsortt.GetDataCount());

	tsortt.Reset();
	TKey tmp = tsortt.GetKey();
	tsortt.GoNext();
	for (;!tsortt.IsTabEnded();tsortt.GoNext()) {
		EXPECT_EQ(1, tmp < tsortt.GetKey());
		tmp = tsortt.GetKey();
	}

	EXPECT_EQ(ptsr, tsortt.FindRecord("6"));
}

TEST(TSortTable, can_del_record) {
	PTStudRec ptsr = new TStudRec;
	TScanTable tst;
	tst.InsRecord("4", NULL);
	tst.InsRecord("8", NULL);
	tst.InsRecord("1", NULL);
	tst.InsRecord("5", NULL);
	tst.InsRecord("7", NULL);
	tst.InsRecord("3", NULL);
	tst.InsRecord("2", ptsr);

	TSortTable tsortt(tst);
	EXPECT_EQ(7, tsortt.GetDataCount());
	tsortt.DelRecord("6");
	EXPECT_EQ(7, tsortt.GetDataCount());

	tsortt.DelRecord("2");
	EXPECT_EQ(6, tsortt.GetDataCount());
	EXPECT_EQ(nullptr, tsortt.FindRecord("2"));

	tsortt.Reset();
	TKey tmp = tsortt.GetKey();
	tsortt.GoNext();
	for (;!tsortt.IsTabEnded();tsortt.GoNext()) {
		EXPECT_EQ(1, tmp < tsortt.GetKey());
		tmp = tsortt.GetKey();
	}
}