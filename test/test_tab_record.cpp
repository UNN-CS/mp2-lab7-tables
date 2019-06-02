#include "TTabRecord.h"
#include "gtest.h"

int TStudRec::marks_number = 4;

TEST(TTabRecord, can_create_tab_record) {
	
	ASSERT_NO_THROW(TTabRecord tr);
}

TEST(TTabRecord, can_get_key) {
	TTabRecord tr1, tr2("tr2_key");

	EXPECT_EQ("", tr1.GetKey());
	EXPECT_EQ("tr2_key", tr2.GetKey());
}

TEST(TTabRecord, can_set_key) {
	TTabRecord tr;
	tr.SetKey("tr_key");

	EXPECT_EQ("tr_key", tr.GetKey());
}

TEST(TTabRecord, can_get_value_ptr) {
	PTStudRec ptsr = new TStudRec;
	TTabRecord tr1, tr2("tr2_key", ptsr);

	EXPECT_EQ(NULL, tr1.GetValuePTR());
	EXPECT_EQ(ptsr, tr2.GetValuePTR());
}

TEST(TTabRecord, can_set_value_ptr) {
	PTStudRec ptsr = new TStudRec;
	TTabRecord tr2("tr2_key");
	tr2.SetValuePtr(ptsr);

	EXPECT_EQ(ptsr, tr2.GetValuePTR());
}

TEST(TTabRecord, compare_operators) {
	TTabRecord tr1("a1"), tr2("b2"), tr3("a1");

	EXPECT_EQ(0, tr1 == tr2);
	EXPECT_EQ(1, tr1 == tr3);
	EXPECT_EQ(1, tr1 < tr2);
}

