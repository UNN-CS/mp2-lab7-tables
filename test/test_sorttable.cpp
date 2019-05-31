#include <gtest.h>
#include <random>
#include <algorithm>

#include "tsorttable.hpp"

TEST(TSortTable, can_insert_record)
{
    TSortTable t;
    TTabRecord w("b");

    t.InsRecord("a", &w);

    TTabRecord res = *((PTTabRecord)t.FindRecord("a"));
    TTabRecord expected = TTabRecord("b");

    ASSERT_EQ(expected, res);
}

TEST(TSortTable, can_delete_record)
{
    TSortTable t;
    TTabRecord w("b");

    t.InsRecord("a", &w);
    t.DelRecord("a");

    PTTabRecord res = (PTTabRecord)t.FindRecord("a");

    ASSERT_EQ(nullptr, res);
}

TEST(TSortTable, can_create_from_ScanTable_using_insert_sort)
{
    TScanTable t;
    TTabRecord w5("word5");
    t.InsRecord("e", &w5);

    TTabRecord w4("word4");
    t.InsRecord("d", &w4);

    TTabRecord w3("word3");
    t.InsRecord("c", &w3);

    TTabRecord w1("word1");
    t.InsRecord("a", &w1);

    TTabRecord w2("word2");
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

TEST(TSortTable, can_create_from_ScanTable_using_quick_sort)
{
    TScanTable t;
    TTabRecord w5("word5");
    t.InsRecord("e", &w5);

    TTabRecord w4("word4");
    t.InsRecord("d", &w4);

    TTabRecord w3("word3");
    t.InsRecord("c", &w3);

    TTabRecord w1("word1");
    t.InsRecord("a", &w1);

    TTabRecord w2("word2");
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

TEST(TSortTable, can_create_from_ScanTable_using_merge_sort)
{
    TScanTable t;
    TTabRecord w5("word5");
    t.InsRecord("e", &w5);

    TTabRecord w4("word4");
    t.InsRecord("d", &w4);

    TTabRecord w3("word3");
    t.InsRecord("c", &w3);

    TTabRecord w1("word1");
    t.InsRecord("a", &w1);

    TTabRecord w2("word2");
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

TEST(TSortTable, can_insert_records)
{
    TSortTable t;
    TTabRecord w5("word5");
    t.InsRecord("e", &w5);

    TTabRecord w4("word4");
    t.InsRecord("d", &w4);

    TTabRecord w3("word3");
    t.InsRecord("c", &w3);

    TTabRecord w1("word1");
    t.InsRecord("a", &w1);

    TTabRecord w2("word2");
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

TEST(TSortTable, can_delete_records)
{
    TScanTable t1;
    TSortTable t(t1);
    TTabRecord w5("word5");
    t.InsRecord("e", &w5);

    TTabRecord w4("word4");
    t.InsRecord("d", &w4);

    TTabRecord w3("word3");
    t.InsRecord("c", &w3);

    TTabRecord w1("word1");
    t.InsRecord("a", &w1);

    TTabRecord w2("word2");
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

TEST(TSortTable, can_handle_deletion_of_absent_key)
{
    TSortTable t;
    TTabRecord w1("a");
    t.InsRecord("1", &w1);

    TTabRecord w2("b");
    t.InsRecord("2", &w2);

    TTabRecord w3("c");
    t.InsRecord("3", &w3);

    t.DelRecord("1");
    int dc = t.GetDataCount();
    t.DelRecord("4");

    ASSERT_EQ(t.GetDataCount(), dc);
}

TEST(TSortTable, can_insert_50_times)
{
    TSortTable t;
    const int number_of_words = 50;
    PTTabRecord words[number_of_words];

    for (int i = 0; i < number_of_words; ++i)
    {
        t.InsRecord(std::to_string(i), words[i] = new TTabRecord("word_" + std::to_string(i)));
    }

    for (int i = 0; i < number_of_words; ++i)
    {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }

    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TSortTable, can_insert_50_times_reversed)
{
    TSortTable t;
    const int number_of_words = 50;
    PTTabRecord words[number_of_words];

    for (int i = number_of_words - 1; i >= 0; --i)
    {
        t.InsRecord(std::to_string(i), words[i] = new TTabRecord("word_" + std::to_string(i)));
    }

    for (int i = 0; i < number_of_words; ++i)
    {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }

    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TSortTable, can_insert_50_times_shuffled)
{
    TSortTable t;
    const int number_of_words = 50;
    PTTabRecord words[number_of_words];
    std::vector<int> order;

    for (int i = 0; i < number_of_words; ++i)
        order.push_back(i);
    std::mt19937 g(10231235);
    std::shuffle(order.begin(), order.end(), g);

    for (int i = 0; i < number_of_words; ++i)
    {
        t.InsRecord(std::to_string(order[i]), words[i] = new TTabRecord("word_" + std::to_string(i)));
    }

    for (int i = 0; i < number_of_words; ++i)
    {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }

    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TSortTable, can_insert_500_times_shuffled)
{
    TSortTable t;
    const int number_of_words = 500;
    PTTabRecord words[number_of_words];
    std::vector<int> order;

    for (int i = 0; i < number_of_words; ++i)
        order.push_back(i);
    std::mt19937 g(10231236);
    std::shuffle(order.begin(), order.end(), g);

    for (int i = 0; i < number_of_words; ++i)
    {
        t.InsRecord(std::to_string(order[i]), words[i] = new TTabRecord("word_" + std::to_string(i)));
    }

    for (int i = 0; i < number_of_words; ++i)
    {
        t.DelRecord(std::to_string(i));
        delete words[i];
    }

    ASSERT_EQ(0, t.GetDataCount());
}

TEST(TSortTable, cannot_insert_501st_element)
{
    TSortTable t;
    const int number_of_words = 500;
    PTTabRecord words[number_of_words + 1];

    for (int i = 0; i < number_of_words; ++i)
    {
        t.InsRecord(std::to_string(i), words[i] = new TTabRecord("word_" + std::to_string(i)));
    }

    ASSERT_ANY_THROW(t.InsRecord(std::to_string(500), words[500] = new TTabRecord("word_" + std::to_string(500))));

    for (int i = 0; i < number_of_words + 1; ++i)
    {
        delete words[i];
    }
}
