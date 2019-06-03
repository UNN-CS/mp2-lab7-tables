#include "gtest.h"
#include "tscantable.h"
#include "tsorttable.h"
#include "string.h"
#include "tbalancetree.h"
#include "tarrayhash.h"
#include "tlisthash.h"
#include <map>;
#include "ttreetable.h"
#include "TWord.h"

using namespace std;

TEST(TScanTable, cant_delete_if_is_empty)
{
	TScanTable t(10);
	string s = "Adddef";
	t.DelRecord(s);
	EXPECT_EQ(1, t.IsEmpty());
}

TEST(TScanTable, datacount_is_correct)
{
	TScanTable t(10);
	string s = "Adddef";
	TWord w("al");
	EXPECT_EQ(0, t.GetDataCount());
	t.InsRecord(s, &w);
	t.InsRecord("1", nullptr);
	EXPECT_EQ(2, t.GetDataCount());
	t.InsRecord(s, nullptr);
	EXPECT_EQ(2, t.GetDataCount());
}

TEST(TScanTable, can_reset_and_do_go_next)
{
	TScanTable t(10);
	t.InsRecord("1", nullptr);
	t.InsRecord("2", nullptr);
	t.InsRecord("3", nullptr);
	t.Reset();
	t.GoNext();
	EXPECT_EQ("2", t.GetKey());
}

TEST(TScanTable, can_correctly_do_checking_of_fullness_1)
{
	TScanTable t(10);
	EXPECT_EQ(0, t.IsFull());
}

TEST(TScanTable, can_correctly_do_checking_of_fullness_2)
{
	TScanTable t(10);
	for (int i = 0; i < 10; ++i)
		t.InsRecord(to_string(i), nullptr);
	EXPECT_EQ(1, t.IsFull());
}

TEST(TScanTable, can_find_in_table)
{
	TScanTable t;
	int n = 10;
	TWord * w = new TWord[n];
	for (int i = 0; i < n; ++i) {
		w[i] = to_string(i);
		t.InsRecord(to_string(i), &w[i]);
	}
	EXPECT_EQ(&w[6], t.FindRecord("6"));
}

TEST(TScanTable, can_insert_and_after_delete) {
	TScanTable t;
	TWord* words[30];
	for (int i = 0; i < 30; ++i) {
		t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
	}
	for (int i = 0; i < 30; ++i) {
		t.DelRecord(std::to_string(i));
		delete words[i];
	}
	ASSERT_EQ(0, t.GetDataCount());
}

class TestSorting : public ::testing::Test
{
protected:
	void sorting(TSortMethod sm) {
		TSortTable a;
		string s[10];
		for (int i = 0; i < 10; ++i) s[i] = to_string(i);
		TScanTable b(10);
		b.InsRecord("4", NULL);
		b.InsRecord("3", NULL);
		b.InsRecord("6", NULL);
		b.InsRecord("1", NULL);
		b.InsRecord("9", NULL);
		b.InsRecord("0", NULL);
		b.InsRecord("2", NULL);
		b.InsRecord("8", NULL);
		b.InsRecord("5", NULL);
		b.InsRecord("7", NULL);
		a.SetSortMethod(sm);
		a = b;
		a.Reset();
		for (int i = 0; i < 10; ++i) {
			EXPECT_EQ(s[i], a.GetKey());
			a.GoNext();
		}
	}
};

TEST(TSortTable, can_insert_record) {
	TSortTable t;
	TWord w("b");
	t.InsRecord("a", &w);    TWord res = *((PTWord)t.FindRecord("a"));
	TWord expected = TWord("b");
	ASSERT_EQ(expected, res);
}

TEST(SortTable, can_insert_record) {
	TSortTable t;
	TWord w("b");
	t.InsRecord("a", &w);
	TWord res = *((TWord*)t.FindRecord("a"));
	TWord expected = TWord("b");
	ASSERT_EQ(expected, res);
}

TEST(SortTable, can_find_elem) {
	TSortTable t;
	TWord w1("first");
	TWord w2("second");
	TWord w3("third");
	t.InsRecord("krok", &w1);
	t.InsRecord("alex", &w2);
	t.InsRecord("left541", &w3);
	EXPECT_EQ(&w2, t.FindRecord("alex"));
}

TEST(SortTable, can_correctly_find_after_delete) {
	TSortTable t;
	TWord w1("first");
	TWord w2("second");
	TWord w3("third");
	t.InsRecord("Adsdf", &w1);
	t.InsRecord("AAA", &w2);
	t.InsRecord("DDsa", &w3);
	EXPECT_EQ(&w2, t.FindRecord("AAA"));
	t.DelRecord("DDsa");
	EXPECT_EQ(NULL, t.FindRecord("DDsa"));
	EXPECT_EQ(2, t.GetDataCount());
}

TEST(TSortTable, cant_find_if_it_is_not_exist)
{
	TSortTable a;
	TWord w1("first");
	TWord w2("second");
	a.InsRecord("a", &w1);
	a.InsRecord("b", &w2);
	EXPECT_EQ(nullptr, a.FindRecord("c"));
}

TEST(TreeTable, correctly_is_empty)
{
	TTreeTable t;
	EXPECT_EQ(1, t.IsEmpty());
	t.InsRecord("lex", NULL);
	EXPECT_EQ(0, t.IsEmpty());
}

TEST(TreeTable, correctly_is_full)
{
	TTreeTable t;
	t.InsRecord("lex", NULL);
	t.InsRecord("rt", NULL);
	EXPECT_EQ(0, t.IsFull());
}

TEST(TreeTable, can_insert_and_find_record)
{
	TTreeTable b;
	TWord w[] = { "0", "1","2","3","4","5","6","7","8","9" };
	b.InsRecord("4", &w[0]);
	b.InsRecord("3", &w[1]);
	b.InsRecord("6", &w[2]);
	b.InsRecord("1", &w[3]);
	b.InsRecord("9", &w[4]);
	b.InsRecord("0", &w[5]);
	b.InsRecord("2", &w[6]);
	b.InsRecord("8", &w[7]);
	b.InsRecord("5", &w[8]);
	b.InsRecord("7", &w[9]);
	EXPECT_EQ(&w[6], b.FindRecord("2"));
	EXPECT_NE(&w[6], b.FindRecord("4"));
}

TEST(TreeTable, can_do_go_next_correctly)
{
	TTreeTable b;
	TWord w[] = { "0", "1","2","3","4","5","6","7","8","9" };
	b.InsRecord("4", &w[0]);
	b.InsRecord("3", &w[1]);
	b.InsRecord("6", &w[2]);
	b.InsRecord("1", &w[3]);
	b.InsRecord("9", &w[4]);
	b.InsRecord("0", &w[5]);
	b.InsRecord("2", &w[6]);
	b.InsRecord("8", &w[7]);
	b.InsRecord("5", &w[8]);
	b.InsRecord("7", &w[9]);
	b.Reset();
	b.GoNext();
	b.GoNext();
	EXPECT_EQ("2", b.GetKey());
	b.GoNext();
	EXPECT_EQ("3", b.GetKey());
	b.GoNext();
	b.GoNext();
	EXPECT_EQ("5", b.GetKey());
}
