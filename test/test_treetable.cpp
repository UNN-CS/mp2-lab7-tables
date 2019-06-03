#include <gtest.h>
#include <random>
#include <algorithm>

#include "ttreetable.hpp"
#include "ttabrecord.hpp"

TEST(TTreeTable, can_insert_records)
{
    TTreeTable t;
    TTabRecord w("lulu");

    t.InsRecord("lu", &w);

    TTabRecord res = *((PTTabRecord)t.FindRecord("lu"));
    TTabRecord expected = TTabRecord("lulu");

    ASSERT_EQ(expected, res);
}

TEST(TTreeTable, can_delete_records)
{
    TTreeTable t;
    TTabRecord w("lulu");

    t.Print();
    t.InsRecord("lu", &w);
    t.Print();
    t.DelRecord("lu");
    t.Print();

    PTTabRecord res = (PTTabRecord)t.FindRecord("lu");

    ASSERT_EQ(nullptr, res);
}

TEST(TTreeTable, can_insert_records2)
{
    TTreeTable t;
    TTabRecord w1("a");
    t.InsRecord("1", &w1);

    TTabRecord w2("b");
    t.InsRecord("2", &w2);

    TTabRecord w3("c");
    t.InsRecord("3", &w3);

    TTabRecord res = *((PTTabRecord)t.FindRecord("2"));
    TTabRecord expected = TTabRecord("b");

    ASSERT_EQ(expected, res);
}

TEST(TTreeTable, can_delete_records2)
{
    TTreeTable t;
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

TEST(TTreeTable, can_handle_deletion_of_absent_key)
{
    TTreeTable t;
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

TEST(TTreeTable, can_insert_50_times)
{
    TTreeTable t;
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

TEST(TTreeTable, can_insert_50_times_reversed)
{
    TTreeTable t;
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

TEST(TTreeTable, can_insert_50_times_shuffled)
{
    TTreeTable t;
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

TEST(TTreeTable, can_insert_500_times_shuffled)
{
    TTreeTable t;
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