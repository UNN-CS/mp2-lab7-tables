#include <gtest.h>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "word.h"
#include "sorttable.h"
#include "treetable.h"
#include "balancetree.h"
#include "arrayhash.h"
#include "listhash.h"

TEST(TScanTable, can_insert_record) {
    TScanTable t;
    TWord w("b");
    t.InsRecord("a", &w);    TWord res = *((PTWord)t.FindRecord("a"));
    TWord expected = TWord("b");
    ASSERT_EQ(expected, res);
}

TEST(TScanTable, can_delete_record) {
    TScanTable t;
    TWord w("b");
    t.InsRecord("a", &w);
    t.DelRecord("a");    PTWord res = (PTWord)t.FindRecord("a");
    ASSERT_EQ(nullptr, res);
}

TEST(TScanTable, can_handle_deletion_of_absent_key) {
    TScanTable t;
    TWord w1("a");
    t.InsRecord("1", &w1);
    TWord w2("b");
    t.InsRecord("2", &w2);
    TWord w3("c");
    t.InsRecord("3", &w3);
    t.DelRecord("1");
    int dc = t.GetDataCount();
    t.DelRecord("4");
    ASSERT_EQ(t.GetDataCount(), dc);
}

TEST(TScanTable, can_insert_50_times) {
    TScanTable t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TScanTable, can_insert_50_times_reversed) {
    TScanTable t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    for (int i = number_of_words - 1; i >= 0; --i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TScanTable, can_insert_50_times_shuffled) {
    TScanTable t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    std::vector <int> order;
    for (int i = 0; i < number_of_words; ++i)
        order.push_back(i);
    std::mt19937 g(10231235);
    std::shuffle(order.begin(), order.end(), g);
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(order[i]), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TScanTable, can_insert_500_times_shuffled) {
    TScanTable t;
    const int number_of_words = 500;
    PTWord words[number_of_words];
    std::vector <int> order;
    for (int i = 0; i < number_of_words; ++i)
        order.push_back(i);
    std::mt19937 g(10231236);
    std::shuffle(order.begin(), order.end(), g);
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(order[i]), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TScanTable, cannot_insert_501st_element) {
    TScanTable t;
    const int number_of_words = 500;
    PTWord words[number_of_words + 1];
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    ASSERT_ANY_THROW(t.InsRecord(std::to_string(500), words[500] = new TWord("word_" + std::to_string(500))));
    for (int i = 0; i < number_of_words + 1; ++i) {
        delete words[i];
    }
}

TEST(TSortTable, can_insert_record) {
    TSortTable t;
    TWord w("b");
    t.InsRecord("a", &w);    TWord res = *((PTWord)t.FindRecord("a"));
    TWord expected = TWord("b");
    ASSERT_EQ(expected, res);
}

TEST(TSortTable, can_delete_record) {
    TSortTable t;
    TWord w("b");
    t.InsRecord("a", &w);
    t.DelRecord("a");    PTWord res = (PTWord)t.FindRecord("a");
    ASSERT_EQ(nullptr, res);
}

TEST(TSortTable, can_create_from_ScanTable_using_insert_sort) {
    TScanTable t;
    TWord w5("word5");
    t.InsRecord("e", &w5);
    TWord w4("word4");
    t.InsRecord("d", &w4);
    TWord w3("word3");
    t.InsRecord("c", &w3);
    TWord w1("word1");
    t.InsRecord("a", &w1);
    TWord w2("word2");
    t.InsRecord("b", &w2);
    TSortTable t1(t, INSERT_SORT);
    std::stringstream ss;
    t1.Print(ss);
    std::string expected = "a word1\n"
                           "b word2\n"
                           "c word3\n"
                           "d word4\n"
                           "e word5\n";
    ASSERT_EQ(expected, ss.str());
}

TEST(TSortTable, can_create_from_ScanTable_using_quick_sort) {
    TScanTable t;
    TWord w5("word5");
    t.InsRecord("e", &w5);
    TWord w4("word4");
    t.InsRecord("d", &w4);
    TWord w3("word3");
    t.InsRecord("c", &w3);
    TWord w1("word1");
    t.InsRecord("a", &w1);
    TWord w2("word2");
    t.InsRecord("b", &w2);
    TSortTable t1(t, QUICK_SORT);
    std::stringstream ss;
    t1.Print(ss);
    std::string expected = "a word1\n"
                           "b word2\n"
                           "c word3\n"
                           "d word4\n"
                           "e word5\n";
    ASSERT_EQ(expected, ss.str());
}

TEST(TSortTable, can_create_from_ScanTable_using_merge_sort) {
    TScanTable t;
    TWord w5("word5");
    t.InsRecord("e", &w5);
    TWord w4("word4");
    t.InsRecord("d", &w4);
    TWord w3("word3");
    t.InsRecord("c", &w3);
    TWord w1("word1");
    t.InsRecord("a", &w1);
    TWord w2("word2");
    t.InsRecord("b", &w2);
    TSortTable t1(t, MERGE_SORT);
    std::stringstream ss;
    t1.Print(ss);
    std::string expected = "a word1\n"
                           "b word2\n"
                           "c word3\n"
                           "d word4\n"
                           "e word5\n";
    ASSERT_EQ(expected, ss.str());
}

TEST(TSortTable, can_insert_records) {
    TSortTable t;
    TWord w5("word5");
    t.InsRecord("e", &w5);
    TWord w4("word4");
    t.InsRecord("d", &w4);
    TWord w3("word3");
    t.InsRecord("c", &w3);
    TWord w1("word1");
    t.InsRecord("a", &w1);
    TWord w2("word2");
    t.InsRecord("b", &w2);
    std::stringstream ss;
    t.Print(ss);
    std::string expected = "a word1\n"
                           "b word2\n"
                           "c word3\n"
                           "d word4\n"
                           "e word5\n";
    ASSERT_EQ(expected, ss.str());
}

TEST(TSortTable, can_delete_records) {
    TScanTable t1;
    TSortTable t(t1);
    TWord w5("word5");
    t.InsRecord("e", &w5);
    TWord w4("word4");
    t.InsRecord("d", &w4);
    TWord w3("word3");
    t.InsRecord("c", &w3);
    TWord w1("word1");
    t.InsRecord("a", &w1);
    TWord w2("word2");
    t.InsRecord("b", &w2);
    t.DelRecord("c");
    t.DelRecord("d");
    std::stringstream ss;
    t.Print(ss);
    std::string expected = "a word1\n"
                           "b word2\n"
                           "e word5\n";
    ASSERT_EQ(expected, ss.str());
}

TEST(TSortTable, can_handle_deletion_of_absent_key) {
    TSortTable t;
    TWord w1("a");
    t.InsRecord("1", &w1);
    TWord w2("b");
    t.InsRecord("2", &w2);
    TWord w3("c");
    t.InsRecord("3", &w3);
    t.DelRecord("1");
    int dc = t.GetDataCount();
    t.DelRecord("4");
    ASSERT_EQ(t.GetDataCount(), dc);
}

TEST(TSortTable, can_insert_50_times) {
    TSortTable t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TSortTable, can_insert_50_times_reversed) {
    TSortTable t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    for (int i = number_of_words - 1; i >= 0; --i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TSortTable, can_insert_50_times_shuffled) {
    TSortTable t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    std::vector <int> order;
    for (int i = 0; i < number_of_words; ++i)
        order.push_back(i);
    std::mt19937 g(10231235);
    std::shuffle(order.begin(), order.end(), g);
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(order[i]), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TSortTable, can_insert_500_times_shuffled) {
    TSortTable t;
    const int number_of_words = 500;
    PTWord words[number_of_words];
    std::vector <int> order;
    for (int i = 0; i < number_of_words; ++i)
        order.push_back(i);
    std::mt19937 g(10231236);
    std::shuffle(order.begin(), order.end(), g);
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(order[i]), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TSortTable, cannot_insert_501st_element) {
    TSortTable t;
    const int number_of_words = 500;
    PTWord words[number_of_words + 1];
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    ASSERT_ANY_THROW(t.InsRecord(std::to_string(500), words[500] = new TWord("word_" + std::to_string(500))));
    for (int i = 0; i < number_of_words + 1; ++i) {
        delete words[i];
    }
}

TEST(TTreeTable, can_insert_records) {
    TTreeTable t;
    TWord w("lulu");
    t.InsRecord("lu", &w);    TWord res = *((PTWord)t.FindRecord("lu"));
    TWord expected = TWord("lulu");
    ASSERT_EQ(expected, res);
}

TEST(TTreeTable, can_delete_records) {
    TTreeTable t;
    TWord w("lulu");
    t.Print();
    t.InsRecord("lu", &w);
    t.Print();
    t.DelRecord("lu");
    t.Print();    PTWord res = (PTWord)t.FindRecord("lu");
    ASSERT_EQ(nullptr, res);
}

TEST(TTreeTable, can_insert_records2) {
    TTreeTable t;
    TWord w1("a");
    t.InsRecord("1", &w1);
    TWord w2("b");
    t.InsRecord("2", &w2);
    TWord w3("c");
    t.InsRecord("3", &w3);    TWord res = *((PTWord)t.FindRecord("2"));
    TWord expected = TWord("b");
    ASSERT_EQ(expected, res);
}

TEST(TTreeTable, can_delete_records2) {
    TTreeTable t;
    TWord w1("a");
    t.InsRecord("1", &w1);
    TWord w2("b");
    t.InsRecord("2", &w2);
    TWord w3("c");
    t.InsRecord("3", &w3);
    t.DelRecord("1");
    t.DelRecord("2");
    t.DelRecord("3");    PTWord res = (PTWord)t.FindRecord("1");
    ASSERT_EQ(nullptr, res);
}

TEST(TTreeTable, can_handle_deletion_of_absent_key) {
    TTreeTable t;
    TWord w1("a");
    t.InsRecord("1", &w1);
    TWord w2("b");
    t.InsRecord("2", &w2);
    TWord w3("c");
    t.InsRecord("3", &w3);
    t.DelRecord("1");
    int dc = t.GetDataCount();
    t.DelRecord("4");
    ASSERT_EQ(t.GetDataCount(), dc);
}

TEST(TTreeTable, can_insert_50_times) {
    TTreeTable t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TTreeTable, can_insert_50_times_reversed) {
    TTreeTable t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    for (int i = number_of_words - 1; i >= 0; --i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TTreeTable, can_insert_50_times_shuffled) {
    TTreeTable t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    std::vector <int> order;
    for (int i = 0; i < number_of_words; ++i)
        order.push_back(i);
    std::mt19937 g(10231235);
    std::shuffle(order.begin(), order.end(), g);
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(order[i]), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TTreeTable, can_insert_500_times_shuffled) {
    TTreeTable t;
    const int number_of_words = 500;
    PTWord words[number_of_words];
    std::vector <int> order;
    for (int i = 0; i < number_of_words; ++i)
        order.push_back(i);
    std::mt19937 g(10231236);
    std::shuffle(order.begin(), order.end(), g);
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(order[i]), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TBalanceTree, can_insert_records) {
    TBalanceTree t;
    TWord w("lulu");
    t.InsRecord("lu", &w);    TWord res = *((PTWord)t.FindRecord("lu"));
    TWord expected = TWord("lulu");
    ASSERT_EQ(expected, res);
}

TEST(TBalanceTree, can_insert_records2) {
    TBalanceTree t;
    TWord w1("a");
    t.InsRecord("1", &w1);
    TWord w2("b");
    t.InsRecord("2", &w2);
    TWord w3("c");
    t.InsRecord("3", &w3);    TWord res = *((PTWord)t.FindRecord("2"));
    TWord expected = TWord("b");
    ASSERT_EQ(expected, res);
}

TEST(TBalanceTree, can_insert_50_times) {
    TBalanceTree t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        delete words[i];
    }
    t.Print();
    ASSERT_EQ(50, t.GetDataCount());
}

TEST(TBalanceTree, can_insert_50_times_reversed) {
    TBalanceTree t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    for (int i = number_of_words - 1; i >= 0; --i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        delete words[i];
    }
    t.Print();
    ASSERT_EQ(50, t.GetDataCount());
}

TEST(TBalanceTree, can_insert_50_times_shuffled) {
    TBalanceTree t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    std::vector <int> order;
    for (int i = 0; i < number_of_words; ++i)
        order.push_back(i);
    std::mt19937 g(10231235);
    std::shuffle(order.begin(), order.end(), g);
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(order[i]), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        delete words[i];
    }
    ASSERT_EQ(50, t.GetDataCount());
}

TEST(TBalanceTree, can_insert_500_times_shuffled) {
    TBalanceTree t;
    const int number_of_words = 500;
    PTWord words[number_of_words];
    std::vector <int> order;
    for (int i = 0; i < number_of_words; ++i)
        order.push_back(i);
    std::mt19937 g(10231236);
    std::shuffle(order.begin(), order.end(), g);
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(order[i]), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        delete words[i];
    }
    ASSERT_EQ(500, t.GetDataCount());
}

TEST(TArrayHash, can_insert_records) {
    TArrayHash t;
    TWord w1("a");
    t.InsRecord("1", &w1);
    TWord w2("b");
    t.InsRecord("11", &w2);    TWord res = *((PTWord)t.FindRecord("11"));
    TWord expected = TWord("b");
    ASSERT_EQ(expected, res);
}

TEST(TArrayHash, can_handle_find_of_absent_key) {
    TArrayHash t;
    TWord w1("a");
    t.InsRecord("1", &w1);
    TWord w2("b");
    t.InsRecord("11", &w2);    PTWord res = (PTWord)t.FindRecord("2");
    ASSERT_EQ(nullptr, res);
}

TEST(TArrayHash, can_delete_records2) {
    TArrayHash t;
    TWord w1("a");
    t.InsRecord("1", &w1);
    TWord w2("b");
    t.InsRecord("2", &w2);
    TWord w3("c");
    t.InsRecord("3", &w3);
    t.DelRecord("1");
    t.DelRecord("2");
    t.DelRecord("3");    PTWord res = (PTWord)t.FindRecord("1");
    ASSERT_EQ(nullptr, res);
}

TEST(TArrayHash, can_handle_deletion_of_absent_key) {
    TArrayHash t;
    TWord w1("a");
    t.InsRecord("1", &w1);
    TWord w2("b");
    t.InsRecord("2", &w2);
    TWord w3("c");
    t.InsRecord("3", &w3);
    t.DelRecord("1");
    int dc = t.GetDataCount();
    t.DelRecord("4");
    ASSERT_EQ(t.GetDataCount(), dc);
}

TEST(TArrayHash, can_insert_50_times) {
    TArrayHash t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TArrayHash, can_insert_50_times_reversed) {
    TArrayHash t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    for (int i = number_of_words - 1; i >= 0; --i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TArrayHash, can_insert_50_times_shuffled) {
    TArrayHash t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    std::vector <int> order;
    for (int i = 0; i < number_of_words; ++i)
        order.push_back(i);
    std::mt19937 g(10231235);
    std::shuffle(order.begin(), order.end(), g);
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(order[i]), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TArrayHash, can_insert_500_times_shuffled) {
    TArrayHash t;
    const int number_of_words = 500;
    PTWord words[number_of_words];
    std::vector <int> order;
    for (int i = 0; i < number_of_words; ++i)
        order.push_back(i);
    std::mt19937 g(10231236);
    std::shuffle(order.begin(), order.end(), g);
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(order[i]), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TArrayHash, cannot_insert_501st_element) {
    TArrayHash t;
    const int number_of_words = 500;
    PTWord words[number_of_words + 1];
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    ASSERT_ANY_THROW(t.InsRecord(std::to_string(500), words[500] = new TWord("word_" + std::to_string(500))));
    for (int i = 0; i < number_of_words + 1; ++i) {
        delete words[i];
    }
}

TEST(TListHash, can_insert_records) {
    TListHash t;
    TWord w1("a");
    t.InsRecord("1", &w1);
    TWord w2("b");
    t.InsRecord("11", &w2);    TWord res = *((PTWord)t.FindRecord("11"));
    TWord expected = TWord("b");
    ASSERT_EQ(expected, res);
}

TEST(TListHash, can_handle_find_of_absent_key) {
    TListHash t;
    TWord w1("a");
    t.InsRecord("1", &w1);
    TWord w2("b");
    t.InsRecord("11", &w2);    PTWord res = (PTWord)t.FindRecord("2");
    ASSERT_EQ(nullptr, res);
}

TEST(TListHash, can_delete_records2) {
    TListHash t;
    TWord w1("a");
    t.InsRecord("1", &w1);
    TWord w2("b");
    t.InsRecord("2", &w2);
    TWord w3("c");
    t.InsRecord("3", &w3);
    t.DelRecord("1");
    t.DelRecord("2");
    t.DelRecord("3");    PTWord res = (PTWord)t.FindRecord("1");
    ASSERT_EQ(nullptr, res);
}

TEST(TListHash, can_handle_deletion_of_absent_key) {
    TListHash t;
    TWord w1("a");
    t.InsRecord("1", &w1);
    TWord w2("b");
    t.InsRecord("2", &w2);
    TWord w3("c");
    t.InsRecord("3", &w3);
    t.DelRecord("1");
    int dc = t.GetDataCount();
    t.DelRecord("4");
    ASSERT_EQ(t.GetDataCount(), dc);
}

TEST(TListHash, can_insert_50_times) {
    TListHash t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TListHash, can_insert_50_times_reversed) {
    TListHash t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    for (int i = number_of_words - 1; i >= 0; --i) {
        t.InsRecord(std::to_string(i), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TListHash, can_insert_50_times_shuffled) {
    TListHash t;
    const int number_of_words = 50;
    PTWord words[number_of_words];
    std::vector <int> order;
    for (int i = 0; i < number_of_words; ++i)
        order.push_back(i);
    std::mt19937 g(10231235);
    std::shuffle(order.begin(), order.end(), g);
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(order[i]), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TListHash, can_insert_500_times_shuffled) {
    TListHash t;
    const int number_of_words = 500;
    PTWord words[number_of_words];
    std::vector <int> order;
    for (int i = 0; i < number_of_words; ++i)
        order.push_back(i);
    std::mt19937 g(10231236);
    std::shuffle(order.begin(), order.end(), g);
    for (int i = 0; i < number_of_words; ++i) {
        t.InsRecord(std::to_string(order[i]), words[i] = new TWord("word_" + std::to_string(i)));
    }
    for (int i = 0; i < number_of_words; ++i) {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }
    ASSERT_EQ(0, t.GetDataCount());
}
