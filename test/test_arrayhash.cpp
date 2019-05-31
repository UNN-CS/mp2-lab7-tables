#include <gtest.h>
#include <random>
#include <algorithm>

#include "tarrayhash.hpp"
#include "ttabrecord.hpp"

TEST(TArrayHash, can_insert_records)
{
    TArrayHash t;
    TTabRecord w1("a");
    t.InsRecord("1", &w1);

    TTabRecord w2("b");
    t.InsRecord("11", &w2);

    TTabRecord res = *((PTTabRecord)t.FindRecord("11"));
    TTabRecord expected = TTabRecord("b");

    ASSERT_EQ(expected, res);
}

TEST(TArrayHash, can_handle_find_of_absent_key)
{
    TArrayHash t;
    TTabRecord w1("a");
    t.InsRecord("1", &w1);

    TTabRecord w2("b");
    t.InsRecord("11", &w2);

    PTTabRecord res = (PTTabRecord)t.FindRecord("2");

    ASSERT_EQ(nullptr, res);
}

TEST(TArrayHash, can_delete_records2)
{
    TArrayHash t;
    TTabRecord w1("a");
    t.InsRecord("1", &w1);

    TTabRecord w2("b");
    t.InsRecord("2", &w2);

    TTabRecord w3("c");
    t.InsRecord("3", &w3);

    t.DelRecord("1");
    t.DelRecord("2");
    t.DelRecord("3");

    PTTabRecord res = (PTTabRecord)t.FindRecord("1");

    ASSERT_EQ(nullptr, res);
}

TEST(TArrayHash, can_handle_deletion_of_absent_key)
{
    TArrayHash t;
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

TEST(TArrayHash, can_insert_50_times)
{
    TArrayHash t;
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

TEST(TArrayHash, can_insert_50_times_reversed)
{
    TArrayHash t;
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

TEST(TArrayHash, can_insert_50_times_shuffled)
{
    TArrayHash t;
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

TEST(TArrayHash, can_insert_500_times_shuffled)
{
    TArrayHash t;
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

TEST(TArrayHash, cannot_insert_501st_element)
{
    TArrayHash t;
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