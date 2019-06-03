#include <gtest.h>
#include "TScanTable.h"

TEST(TScanTable, can_create)
{
	TScanTable *tab;

	ASSERT_NO_THROW(tab = new TScanTable(25));
}

TEST(TScanTable, can_create_with_negative_lenght)
{
	TScanTable *tab;

	ASSERT_NO_THROW(tab = new TScanTable(-25));
}

TEST(TScanTable, can_check_full_fasle)
{
	TScanTable tab(5);

	EXPECT_EQ(0, tab.IsFull());
}

TEST(TScanTable, can_check_full_true)
{
	TScanTable tab(5);
	for (int i = 0; i < 5; i++)
	{
		tab.InsRecord("", (PTDatValue)i);
	}
	EXPECT_EQ(1, tab.IsFull());
}

TEST(TScanTable, can_find_record)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("2", t2);
	tab.InsRecord("3", t3);

	EXPECT_EQ(t2, tab.FindRecord("2"));
}

TEST(TScanTable, can_find_nonexistent_record)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("2", t2);
	tab.InsRecord("3", t3);

	EXPECT_EQ(nullptr, tab.FindRecord("5"));
}

TEST(TScanTable, can_delete_record_check_DataCount)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("2", t2);
	tab.InsRecord("3", t3);

	tab.DelRecord("2");

	EXPECT_EQ(2, tab.GetDataCount());
}

TEST(TScanTable, can_insert_record_check_DataCount)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("3", t2);

	tab.InsRecord("2");

	EXPECT_EQ(3, tab.GetDataCount());
}

TEST(TScanTable, can_check_empty_true)
{
	TScanTable tab(5);

	EXPECT_EQ(1, tab.IsEmpty());
}

TEST(TScanTable, can_check_empty_false)
{
	TScanTable tab(5);
	for (int i = 0; i < 5; i++)
	{
		tab.InsRecord("", new TTabRecord());
	}
	EXPECT_EQ(0, tab.IsEmpty());
}

TEST(TScanTable, can_get_key_first_pos)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("2", t2);

	EXPECT_EQ("1", tab.GetKey(FIRST_POS));
}

TEST(TScanTable, can_get_key_last_pos)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("2", t2);

	EXPECT_EQ("2", tab.GetKey(LAST_POS));
}

TEST(TScanTable, can_get_key_current_pos)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

	tab.InsRecord("1", t1);
	tab.InsRecord("2", t2);
	tab.InsRecord("3", t3);

	tab.SetCurrentPos(1);
	EXPECT_EQ("2", tab.GetKey(CURRENT_POS));
}

TEST(TScanTable, can_get_key)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();

	tab.InsRecord("1", t1);

	EXPECT_EQ("1", tab.GetKey());
}

TEST(TScanTable, can_get_value)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();

	tab.InsRecord("1", t1);

	EXPECT_EQ(t1, tab.GetValuePTR());
}

TEST(TScanTable, can_get_value_first_pos)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);

	EXPECT_EQ(t1, tab.GetValuePTR(FIRST_POS));
}

TEST(TScanTable, can_get_value_last_pos)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);

	EXPECT_EQ(t3, tab.GetValuePTR(LAST_POS));
}

TEST(TScanTable, can_get_value_current_pos)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);
	tab.SetCurrentPos(1);

	EXPECT_EQ(t2, tab.GetValuePTR(CURRENT_POS));
}

TEST(TScanTable, can_get_size)
{
	TScanTable tab(5);

	EXPECT_EQ(5, tab.GetTabSize());
}

TEST(TScanTable, can_reset)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);
	tab.SetCurrentPos(1);

	tab.Reset();

	EXPECT_EQ(0, tab.GetCurrentPos());
}

TEST(TScanTable, can_go_next)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);

	tab.GoNext();

	EXPECT_EQ(1, tab.GetCurrentPos());
}

TEST(TScanTable, can_go_next_if_table_is_end)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();

	tab.GoNext();

	EXPECT_EQ(3, tab.GetCurrentPos());
}

TEST(TScanTable, can_check_end_tab_true)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();

	EXPECT_EQ(1, tab.IsTabEnded());
}

TEST(TScanTable, can_check_end_tab_return_false)
{
	TScanTable tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

    tab.InsRecord("1", t1);
    tab.InsRecord("2", t2);
    tab.InsRecord("3", t3);
	tab.GoNext();

	EXPECT_EQ(0, tab.IsTabEnded());
}
