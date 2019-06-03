#include <gtest.h>
#include <random>
#include <algorithm>

#include "tscantable.hpp"
#include "ttabrecord.hpp"

TEST(TScanTable, can_insert_record)
{
    TScanTable t;
    TTabRecord w("b");

    t.InsRecord("a", &w);

    TTabRecord res = *((PTTabRecord)t.FindRecord("a"));
    TTabRecord expected = TTabRecord("b");

    ASSERT_EQ(expected, res);
}

TEST(TScanTable, can_delete_record)
{
    TScanTable t;
    TTabRecord w("b");

    t.InsRecord("a", &w);
    t.DelRecord("a");

    PTTabRecord res = (PTTabRecord)t.FindRecord("a");

    ASSERT_EQ(nullptr, res);
}

TEST(TScanTable, can_handle_deletion_of_absent_key)
{
    TScanTable t;
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

TEST(TScanTable, can_insert_50_times)
{
    TScanTable t;
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

TEST(TScanTable, can_insert_50_times_reversed)
{
    TScanTable t;
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

TEST(TScanTable, can_insert_50_times_shuffled)
{
    TScanTable t;
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

TEST(TScanTable, can_insert_500_times_shuffled)
{
    TScanTable t;
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

TEST(TScanTable, cant_insert_501st_element)
{
    TScanTable t;
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