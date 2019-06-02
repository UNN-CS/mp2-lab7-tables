#include <gtest.h>
#include "TArrayHash.h"


TEST(TArrayHash, can_create_default)
{
	TArrayHash *tab;

	ASSERT_NO_THROW(tab = new TArrayHash());
}

TEST(TArrayHash, can_create_with_incorrect_size)
{
	TArrayHash *tab;

	ASSERT_ANY_THROW(tab = new TArrayHash(-1));
}

TEST(TArrayHash, can_create_with_step_larger_size)
{
	TArrayHash *tab;

	ASSERT_ANY_THROW(tab = new TArrayHash(10, 15));
}

TEST(TArrayHash, can_create_with_incorrect_step)
{
	TArrayHash *tab;

	ASSERT_ANY_THROW(tab = new TArrayHash(10, 1));
}

TEST(TArrayHash, can_ins_rec)
{
	TArrayHash tab(10, 3);
    PTDatValue t1 = new TTabRecord();

	tab.InsRecord("Kurakin", t1);

	EXPECT_EQ(tab.FindRecord("Kurakin"), t1);
}

TEST(TArrayHash, can_not_ins_rec_if_tab_full)
{
	TArrayHash tab(3, 2);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();
    PTDatValue t3 = new TTabRecord();

	tab.InsRecord("Sazanov", t1);
	tab.InsRecord("Kurakin", t2);
	tab.InsRecord("Babushkin", t3);
	tab.InsRecord("Sadikov", t3);

	EXPECT_EQ(tab.FindRecord("Sadikov"), nullptr);
}

TEST(TArrayHash, check_empty_after_del_all_rec)
{
	TArrayHash tab(5, 2);
    PTDatValue t1 = new TTabRecord();

	tab.InsRecord("Sazanov", t1);
	tab.InsRecord("Kurakin", t1);
	tab.InsRecord("Babushkin", t1);
	tab.InsRecord("Sadikov", t1);
	tab.InsRecord("Sokolyuk", t1);

	tab.DelRecord("Sazanov");
	tab.DelRecord("Kurakin");
	tab.DelRecord("Babushkin");
	tab.DelRecord("Sadikov");
	tab.DelRecord("Sokolyuk");

	EXPECT_EQ(true, tab.IsEmpty());
}

TEST(TArrayHash, check_full_after_ins_all_rec)
{
	TArrayHash tab(5, 2);
    PTDatValue t1 = new TTabRecord();

	tab.InsRecord("Sazanov", t1);
	tab.InsRecord("Kurakin", t1);
	tab.InsRecord("Babushkin", t1);
	tab.InsRecord("Sadikov", t1);
	tab.InsRecord("Sokolyuk", t1);

	EXPECT_EQ(true, tab.IsFull());
}

TEST(TArrayHash, check_ended_tab)
{
	TArrayHash tab(5, 2);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("Sazanov", t1);
	tab.InsRecord("Kurakin", t2);
	tab.InsRecord("Babushkin", t1);
	tab.InsRecord("Sadikov", t2);
	tab.InsRecord("Sokolyuk", t2);

	tab.Reset();
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();
	tab.GoNext();

	EXPECT_EQ(tab.IsTabEnded(), true);
}
