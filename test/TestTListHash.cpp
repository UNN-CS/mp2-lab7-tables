#include <gtest.h>
#include "TListHash.h"

TEST(TListHash, can_create_default)
{
	TListHash *tab;

	ASSERT_NO_THROW(tab = new TListHash());
}

TEST(TListHash, can_not_create_with_negative_size)
{
	TListHash *tab;

	ASSERT_ANY_THROW(tab = new TListHash(-5));
}

TEST(TListHash, can_create)
{
	TListHash *tab;

	ASSERT_NO_THROW(tab = new TListHash(5));
}

TEST(TListHash, can_insert_record)
{
	TListHash tab(5);
    PTDatValue t1 = new TTabRecord();

	tab.InsRecord("Petrov", t1);

	EXPECT_EQ(tab.FindRecord("Petrov"), t1);
}

TEST(TListHash, can_insert_record_dbl)
{
	TListHash tab(5);
    PTDatValue t1 = new TTabRecord();

	tab.InsRecord("Petrov", t1);
	tab.InsRecord("Petrov", t1);

	EXPECT_EQ(TabRecDbl, tab.GetRetCode());
}

TEST(TListHash, can_find_record)
{
	TListHash tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("Petrov", t1);
	tab.InsRecord("Ivanov", t2);

	EXPECT_EQ(tab.FindRecord("Petrov"), t1);
}

TEST(TListHash, can_delete_record)
{
	TListHash tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("Petrov", t1);
	tab.InsRecord("Ivanov", t2);

	tab.DelRecord("Petrov");

	EXPECT_EQ(tab.FindRecord("Petrov"), nullptr);
}

TEST(TListHash, check_tab_empty_after_del)
{
	TListHash tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("Petrov", t1);
	tab.InsRecord("Ivanov", t2);
	tab.InsRecord("Vetrov", t1);
	tab.InsRecord("Pupkin", t2);

	tab.DelRecord("Vetrov");
	tab.DelRecord("Ivanov");
	tab.DelRecord("Petrov");
	tab.DelRecord("Pupkin");

	EXPECT_EQ(true, tab.IsEmpty());
}

TEST(TListHash, check_ended_tab)
{
	TListHash tab(5);
    PTDatValue t1 = new TTabRecord();
    PTDatValue t2 = new TTabRecord();

	tab.InsRecord("Petrov", t1);
	tab.InsRecord("Ivanov", t2);
	tab.InsRecord("Vetrov", t1);
	tab.InsRecord("Pupkin", t2);
	tab.InsRecord("Sorin", t2);

	tab.Reset();//Petrov
	tab.GoNext();//Ivanov
	tab.GoNext();//Vetrov
	tab.GoNext();//Pupkin
	tab.GoNext();
	tab.GoNext();

	EXPECT_EQ(tab.IsTabEnded(), true);

}
