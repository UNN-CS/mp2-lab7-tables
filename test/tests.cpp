#include "gtest.h"
#include "TScanTable.h"
#include "TWord.h"
#include "sorttab.h"
#include "string.h"
#include "balancetree.h"
#include "arrhash.h"
#include "listhash.h"
#include <map>;
#include "treetab.h"

using namespace std;

TEST(TScanTable, cant_insert_is_is_full)
{
	TScanTable t(10);
	for (int i = 0; i < 15; ++i)
		t.InsRecord(to_string(i), nullptr);
	EXPECT_EQ(1, t.IsFull());
	EXPECT_EQ(TabFull, t.GetRetCode());
}

TEST(TScanTable, cant_delete_if_is_empty)
{
	TScanTable t(10);
	string s = "alex";
	t.DelRecord(s);
	EXPECT_EQ(1, t.IsEmpty());
	EXPECT_EQ(TabNoRec, t.GetRetCode());
}

TEST(TScanTable, datacount_is_correct)
{
	TScanTable t(10);
	string s = "alex";
	TWord w("al");
	EXPECT_EQ(0, t.GetDataCount());
	t.InsRecord(s,&w);
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
	PWord words[30];
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
	void sorting(SortMethod sm) {
		SortTable a;
		string s[10];
		for (int i = 0; i < 10; ++i) s[i] = to_string(i);
		TScanTable b(10);
		b.InsRecord("4",NULL);
		b.InsRecord("3", NULL);
		b.InsRecord("6", NULL);
		b.InsRecord("1", NULL);
		b.InsRecord("9", NULL);
		b.InsRecord("0", NULL);
		b.InsRecord("2", NULL);
		b.InsRecord("8", NULL);
		b.InsRecord("5", NULL);
		b.InsRecord("7", NULL);
		a.SetSort(sm);
		a = b;
		a.Reset();
		for (int i = 0; i < 10; ++i) {
			EXPECT_EQ(s[i], a.GetKey());
			a.GoNext();
		}
	}
};

TEST_F(TestSorting, quick_sort_is_correct)
{
	sorting(SortMethod::Quick_Sort);
}

TEST_F(TestSorting, insert_sort_is_correct)
{
	sorting(SortMethod::Insert_Sort);
}

TEST_F(TestSorting, merge_sort_is_correct)
{
	sorting(SortMethod::Merge_Sort);
}

TEST(SortTable, can_create_and_correcrly_insert)
{
	SortTable t;
	t.InsRecord("alex", nullptr);
	t.InsRecord("krok", nullptr);
	t.InsRecord("gooddoog", nullptr);
	t.InsRecord("left541", nullptr);
	t.Reset();
	EXPECT_EQ("alex", t.GetKey());
	t.GoNext();
	t.GoNext();
	EXPECT_EQ("krok", t.GetKey());
}


TEST(SortTable, can_insert_record) {
	SortTable t;
	TWord w("b");
	t.InsRecord("a", &w);
	TWord res = *((PWord)t.FindRecord("a"));
	TWord expected = TWord("b");
	ASSERT_EQ(expected, res);
}

TEST(SortTable, datacount_is_correct_for_Sort_Table) {
	SortTable t;
	t.InsRecord("alex", nullptr);
	t.InsRecord("krok", nullptr);
	EXPECT_EQ(2, t.GetDataCount());
	t.InsRecord("left541", nullptr);
	EXPECT_EQ(3, t.GetDataCount());
	t.InsRecord("alex", nullptr);
	EXPECT_EQ(3, t.GetDataCount());
}

TEST(SortTable, can_correctly_delete) {
	SortTable t;
	TWord w("first");
	t.InsRecord("krok", &w);
	t.InsRecord("alex", &w);
	t.InsRecord("left541",&w);
	t.Reset();
	t.GoNext();
	EXPECT_EQ("krok", t.GetKey());
	t.DelRecord("krok");
	EXPECT_EQ(2, t.GetDataCount());
	EXPECT_EQ("left541", t.GetKey());
}

TEST(SortTable, can_find_elem) {
	SortTable t;
	TWord w1("first");
	TWord w2("second");
	TWord w3("third");
	t.InsRecord("krok", &w1);
	t.InsRecord("alex", &w2);
	t.InsRecord("left541", &w3);
	EXPECT_EQ(&w2, t.FindRecord("alex"));
}

TEST(SortTable, can_correctly_find_after_delete) {
	SortTable t;
	TWord w1("first");
	TWord w2("second");
	TWord w3("third");
	t.InsRecord("krok", &w1);
	t.InsRecord("alex", &w2);
	t.InsRecord("left541", &w3);
	EXPECT_EQ(&w2, t.FindRecord("alex"));
	t.DelRecord("left541");
	EXPECT_EQ(NULL, t.FindRecord("left541"));
	EXPECT_EQ(2, t.GetDataCount());
}

TEST(TSortTable, cant_find_if_it_is_not_exist)
{
	SortTable a;
	TWord w1("first");
	TWord w2("second");
	a.InsRecord("a", &w1);
	a.InsRecord("b", &w2);
	EXPECT_EQ(nullptr, a.FindRecord("c"));
}

TEST(TreeTable, correctly_is_empty)
{
	TreeTable t;
	EXPECT_EQ(1, t.IsEmpty());
	t.InsRecord("lex", NULL);
	EXPECT_EQ(0, t.IsEmpty());
}

TEST(TreeTable, correctly_is_full)
{
	TreeTable t;
	t.InsRecord("lex", NULL);
	t.InsRecord("rt", NULL);
	EXPECT_EQ(0, t.IsFull());
}

TEST(TreeTable, can_insert_and_find_record)
{
	TreeTable b;
	TWord w[] = {"0", "1","2","3","4","5","6","7","8","9" };
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
	EXPECT_EQ(&w[6],b.FindRecord("2"));
	EXPECT_NE(&w[6], b.FindRecord("4"));
}

TEST(TreeTable, can_do_go_next_correctly)
{
	TreeTable b;
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

class TreeTab :public ::testing::Test
{
protected:
	void Assert(int tmp)
	{
		TreeTable b;
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
		switch (tmp) {
		case 1:
			ASSERT_NO_THROW(cout << b;);
			break;
		case 2:
			ASSERT_NO_THROW(b.Draw(););
			break;
		case 3:
			ASSERT_NO_THROW(b.Show());
			break;
		}
	}
};

TEST_F(TreeTab, can_cout_table1)
{
	Assert(1);
}

TEST_F(TreeTab, can_cout_table2)
{
	Assert(2);
}

TEST_F(TreeTab, can_cout_table3)
{
	Assert(3);
}
TEST(TreeTable, try_to_check_get_efficiency)
{
	TreeTable b;
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
	b.FindRecord("8");
	EXPECT_EQ(1,b.GetEfficiency() < 5);
}

TEST(TreeTable, checking_efficiency_to_know_about_non_balance_of_tree)
{
	TreeTable a;
	TWord w("t");
	for (int i = 0; i < 10; ++i) a.InsRecord(to_string(i), &w);
	for (int i = 6; i < 10; ++i)
	{
		string tmp = to_string(i);
		a.FindRecord(tmp);
		EXPECT_EQ(1, a.GetEfficiency() > 5);
	}
}

TEST(TreeTable, datacount_after_delete_is_correct)
{
	TreeTable b;
	TWord w[] = { "0", "1","2","3","4","5","6","7","8","9" };
	b.InsRecord("4", &w[0]);
	b.InsRecord("3", &w[1]);
	b.InsRecord("6", &w[2]);
	EXPECT_EQ(3, b.GetDataCount());
	b.DelRecord("7");
	EXPECT_EQ(3, b.GetDataCount());
	b.DelRecord("4");
	EXPECT_EQ(2, b.GetDataCount());
}

TEST(BalanceTree, can_insert)
{
	BalanceTree a;
	ASSERT_NO_THROW(a.InsRecord("a", nullptr));
}

TEST(BalanceTree, can_find_in_tree)
{
	BalanceTree a;
	TWord w("t");
	a.InsRecord("a", nullptr);
	a.InsRecord("b", nullptr);
	a.InsRecord("d", &w);
	a.InsRecord("c", nullptr);
	EXPECT_EQ(&w, a.FindRecord("d"));
}

TEST(BalanceTree, datacount_is_correctly)
{
	BalanceTree a;
	TWord w("t");
	a.InsRecord("a", nullptr);
	a.InsRecord("b", nullptr);
	a.InsRecord("d", &w);
	a.InsRecord("c", nullptr);
	EXPECT_EQ(4, a.GetDataCount());
}

TEST(BalanceTree, isempty_ans_isfull_is_correctly)
{
	BalanceTree a;
	TWord w("t");
	EXPECT_EQ(1, a.IsEmpty());
	a.InsRecord("a", nullptr);
	a.InsRecord("b", nullptr);
	a.InsRecord("d", &w);
	a.InsRecord("c", nullptr);
	EXPECT_EQ(0, a.IsEmpty());
	EXPECT_EQ(0, a.IsFull());
}

TEST(BalanceTree, reset_is_correct)
{
	BalanceTree a;
	TWord w("t");
	a.InsRecord("a", &w);
	a.InsRecord("b", &w);
	a.InsRecord("d", &w);
	a.InsRecord("c", nullptr);
	a.Reset();
	EXPECT_EQ("a", a.GetKey());
}

TEST(BalanceTree, go_next_and_GetValuePtr_is_correct)
{
	BalanceTree a;
	TWord w("t");
	a.InsRecord("3", &w);
	a.InsRecord("4", &w);
	a.InsRecord("1", &w);
	a.InsRecord("2", nullptr);
	a.Reset();
	a.GoNext();
	EXPECT_EQ("2", a.GetKey());
	a.GoNext();
	EXPECT_EQ("3", a.GetKey());
}

TEST(BalanceTree, checking_efficiency_to_know_about_balance_of_tree)
{
	BalanceTree a;
	TWord w("t");
	for (int i = 0; i < 10; ++i) a.InsRecord(to_string(i), &w);
	for (int i = 0; i < 10; ++i)
	{
		string tmp = to_string(i);
		a.FindRecord(tmp);
		EXPECT_EQ(1, a.GetEfficiency() <= 4);
	}
}

TEST(ArrayHash, can_insert_record)
{
	ArrayHash t;
	ASSERT_NO_THROW(t.InsRecord("1",nullptr));
	EXPECT_EQ(1, t.GetDataCount());
}

TEST(ArrayHash, can_insert_ans_delete_together)
{
	ArrayHash t(10,3);
	TWord w("alex");
	t.InsRecord("1", NULL);
	t.InsRecord("3", NULL);
	t.InsRecord("2", &w);
	EXPECT_EQ(3, t.GetDataCount());
	t.DelRecord("4");
	EXPECT_EQ(3, t.GetDataCount());
	//PWord(t.FindRecord("2"))->Print();
	t.DelRecord("2");
	EXPECT_EQ(2, t.GetDataCount());
}

TEST(ArrayHash, born_collision_when_use_non_correct_size_and_step)
{
	ArrayHash t(4,2);
	TWord w("alex");
	t.InsRecord("0", &w);
	t.InsRecord("3", &w);
	t.InsRecord("4", &w);
	t.Reset();
	EXPECT_EQ("0", t.GetKey());
	t.InsRecord("8", &w);
	t.Reset();
	EXPECT_EQ("8", t.GetKey());
	EXPECT_EQ(3, t.GetDataCount());
}

TEST(ArrayHash, no_collision_when_use_mutually_prime_numbers)
{
	ArrayHash t(4, 3);
	TWord w("alex");
	t.InsRecord("0", &w);
	t.InsRecord("3", &w);
	t.InsRecord("4", &w);
	t.Reset();
	EXPECT_EQ("0", t.GetKey());
	t.InsRecord("8", &w);
	t.Reset();
	EXPECT_EQ("0", t.GetKey());
	EXPECT_EQ(4, t.GetDataCount());
}


TEST(ListHash, go_next_works_correctly)
{
	map<string, bool> m;
	ListHash a(3);
	a.InsRecord("h", nullptr);
	a.InsRecord("ojp", nullptr);
	a.InsRecord("tdrj", nullptr);
	a.InsRecord("q", nullptr);
	a.InsRecord("pjii", nullptr);
	a.InsRecord("xtc", nullptr);
	a.InsRecord("ukb j", nullptr);
	for (a.Reset(); !a.IsTabEnded(); a.GoNext())
		m[a.GetKey()] = 1;
	EXPECT_TRUE(m["h"]);
	EXPECT_TRUE(m["ojp"]);
	EXPECT_TRUE(m["tdrj"]);
	EXPECT_TRUE(m["q"]);
	EXPECT_TRUE(m["pjii"]);
	EXPECT_TRUE(m["xtc"]);
	EXPECT_TRUE(m["ukb j"]);
	EXPECT_EQ(7u, m.size());
}

TEST(ListHash, can_insert_and_delete_many_records)
{
	ListHash t(10);
	TWord w("hi");
	for (int i = 0; i < 100; ++i) t.InsRecord(to_string(i), &w);
	ASSERT_NO_THROW(cout << t;);
	EXPECT_EQ(100, t.GetDataCount());
	for (int i = 0; i < 100; ++i) t.DelRecord(to_string(i));
	ASSERT_NO_THROW(cout << t;);
	EXPECT_EQ(0,t.GetDataCount());
}

TEST(ListHash, can_find_record)
{
	ListHash t(5);
	TWord w("54234235");
	t.InsRecord("e", nullptr);
	t.InsRecord("`", nullptr);
	t.InsRecord("=", &w);
	t.InsRecord("/", nullptr);
	EXPECT_EQ(&w, t.FindRecord("="));
	t.DelRecord("=");
	EXPECT_EQ(NULL, t.FindRecord("="));
}
