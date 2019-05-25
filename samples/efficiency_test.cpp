#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <set>
#include <fstream>
#include <random>
#include <stdexcept>
#include <functional>
#include <thread>
#include <cstdlib>
#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"
#include "TTreeTable.h"
using namespace std;

int table_test_insert(TTable& tb, vector<string>& keys, int n)
{
    for (int i = 0; i < n; ++i)
        tb.InsRecord(keys[i], nullptr);
    if (tb.GetDataCount() < n)
        throw runtime_error("insert error");
    int ret = tb.GetEfficiency();
    tb.ResetEfficiency();
    return ret;
}

int table_test_insert_random(TTable& tb, vector<string>& keys, int n)
{
    mt19937 mt(time(0) + n + 123);
    uniform_int_distribution<int> dist(0, INT_MAX);
    set<string> s;
    for (int i = 0; i < n; ++i)
        s.insert(keys[i]);
    for (int i = 0; i < n; ++i)
    {
        auto it = s.begin();
        int pos = dist(mt) % s.size();
        for(int j = 0; j < pos; ++j, ++it);
        tb.InsRecord(*it, nullptr);
        s.erase(it);
    }
    if (tb.GetDataCount() < n)
        throw runtime_error("insert random error");
    int ret = tb.GetEfficiency();
    tb.ResetEfficiency();
    return ret;
}

int table_test_find(TTable& tb, vector<string>& keys, int n)
{
    for (int i = 0; i < n; ++i)
        if (tb.FindRecord(keys[i]) == nullptr)
            throw runtime_error("find error");
    int ret = tb.GetEfficiency();
    tb.ResetEfficiency();
    return ret;
}

int table_test_find_random(TTable& tb, vector<string>& keys, int n)
{
    mt19937 mt(time(0) + n + 43211);
    uniform_int_distribution<int> dist(0, INT_MAX);
    set<string> s;
    for (int i = 0; i < n; ++i)
        s.insert(keys[i]);
    for (int i = 0; i < n; ++i)
    {
        auto it = s.begin();
        int pos = dist(mt) % s.size();
        for(int j = 0; j < pos; ++j, ++it);
        if (tb.FindRecord(*it) == nullptr)
            throw runtime_error("find random error");
        s.erase(it);
    }
    int ret = tb.GetEfficiency();
    tb.ResetEfficiency();
    return ret;
}

int table_test_delete(TTable& tb, vector<string>& keys, int n)
{
    for (int i = 0; i < n; ++i)
        tb.DelRecord(keys[i]);
    if (tb.GetDataCount() > 0)
        throw runtime_error("delete error");
    int ret = tb.GetEfficiency();
    tb.ResetEfficiency();
    return ret;
}

int table_test_delete_random(TTable& tb, vector<string>& keys, int n)
{
    mt19937 mt(time(0) + n + 638);
    uniform_int_distribution<int> dist(0, INT_MAX);
    set<string> s;
    for (int i = 0; i < n; ++i)
        s.insert(keys[i]);
    for (int i = 0; i < n; ++i)
    {
        auto it = s.begin();
        int pos = dist(mt) % s.size();
        for(int j = 0; j < pos; ++j, ++it);
        tb.DelRecord(*it);
        s.erase(it);
    }
    if (tb.GetDataCount() > 0)
        throw runtime_error("delete random error");
    int ret = tb.GetEfficiency();
    tb.ResetEfficiency();
    return ret;
}

int main(int argc, char** argv)
{
    int n = 2000, m = 10;
    if (argc > 1)
    {
        n = atoi(argv[1]);
        if (argc > 2)
            m = atoi(argv[2]);
    }
    ifstream input("name_table.txt");
    vector<string> data;
    vector<array<int, 6>> results[8];
    for (int i = 0; i < n; ++i)
    {
        string s;
        getline(input, s, '\n');
        data.push_back(s);
    }
    input.close();

    // TScanTable
    function<void(int, int, vector<array<int, 6>>&)> fu1 = [&data](int n, int m, vector<array<int, 6>>& res)
    {
        for (int i = m; i <= n; i += m)
        {
            array<int, 6> arr;
            arr[0] = i;
            TScanTable tab(i);
            arr[1] = table_test_insert(tab, data, i);
            arr[2] = table_test_find(tab, data, i);
            arr[3] = table_test_find_random(tab, data, i);
            arr[4] = table_test_delete(tab, data, i);
            table_test_insert(tab, data, i);
            arr[5] = table_test_delete_random(tab, data, i);
            res.push_back(arr);
        }
        cout << "Scan Table ended\n";
        cout.flush();
    };
    thread thr1(fu1, n, m, ref(results[0]));
    // TSortTable
    function<void(int, int, vector<array<int, 6>>&)> fu2 = [&data](int n, int m, vector<array<int, 6>>& res)
    {
        for (int i = m; i <= n; i += m)
        {
            array<int, 6> arr;
            arr[0] = i;
            TSortTable tab(i);
            arr[1] = table_test_insert(tab, data, i);
            arr[2] = table_test_find(tab, data, i);
            arr[3] = table_test_find_random(tab, data, i);
            arr[4] = table_test_delete(tab, data, i);
            table_test_insert(tab, data, i);
            arr[5] = table_test_delete_random(tab, data, i);
            res.push_back(arr);
        }
        cout << "Sort Table ended\n";
        cout.flush();
    };
    thread thr2(fu2, n, m, ref(results[1]));
    // TTreeTable
    function<void(int, int, vector<array<int, 6>>&)> fu3 = [&data](int n, int m, vector<array<int, 6>>& res)
    {
        for (int i = m; i <= n; i += m)
        {
            array<int, 6> arr;
            arr[0] = i;
            TTreeTable tab;
            arr[1] = table_test_insert(tab, data, i);
            arr[2] = table_test_find(tab, data, i);
            arr[3] = table_test_find_random(tab, data, i);
            arr[4] = table_test_delete(tab, data, i);
            table_test_insert(tab, data, i);
            arr[5] = table_test_delete_random(tab, data, i);
            res.push_back(arr);
        }
        cout << "Tree Table ended\n";
        cout.flush();
    };
    thread thr3(fu3, n, m, ref(results[2]));
    // TBalanceTree
    function<void(int, int, vector<array<int, 6>>&)> fu4 = [&data](int n, int m, vector<array<int, 6>>& res)
    {
        for (int i = m; i <= n; i += m)
        {
            array<int, 6> arr;
            arr[0] = i;
            TBalanceTree tab;
            arr[1] = table_test_insert(tab, data, i);
            arr[2] = table_test_find(tab, data, i);
            arr[3] = table_test_find_random(tab, data, i);
            arr[4] = table_test_delete(tab, data, i);
            table_test_insert(tab, data, i);
            arr[5] = table_test_delete_random(tab, data, i);
            res.push_back(arr);
        }
        cout << "Balance Tree ended\n";
        cout.flush();
    };
    thread thr4(fu4, n, m, ref(results[3]));
    // TArrayHash
    function<void(int, int, vector<array<int, 6>>&)> fu5 = [&data](int n, int m, vector<array<int, 6>>& res)
    {
        for (int i = m; i <= n; i += m)
        {
            array<int, 6> arr;
            arr[0] = i;
            TArrayHash tab(i, 1);
            arr[1] = table_test_insert(tab, data, i);
            arr[2] = table_test_find(tab, data, i);
            arr[3] = table_test_find_random(tab, data, i);
            arr[4] = table_test_delete(tab, data, i);
            table_test_insert(tab, data, i);
            arr[5] = table_test_delete_random(tab, data, i);
            res.push_back(arr);
        }
        cout << "Array Hash ended\n";
        cout.flush();
    };
    thread thr5(fu5, n, m, ref(results[4]));
    // TArrayHash with big size
    function<void(int, int, vector<array<int, 6>>&)> fu6 = [&data](int n, int m, vector<array<int, 6>>& res)
    {
        for (int i = m; i <= n; i += m)
        {
            array<int, 6> arr;
            arr[0] = i;
            TArrayHash tab(i * 2, 1);
            arr[1] = table_test_insert(tab, data, i);
            arr[2] = table_test_find(tab, data, i);
            arr[3] = table_test_find_random(tab, data, i);
            arr[4] = table_test_delete(tab, data, i);
            table_test_insert(tab, data, i);
            arr[5] = table_test_delete_random(tab, data, i);
            res.push_back(arr);
        }
        cout << "big Array Hash ended\n";
        cout.flush();
    };
    thread thr6(fu6, n, m, ref(results[5]));
    // TListHash
    function<void(int, int, vector<array<int, 6>>&)> fu7 = [&data](int n, int m, vector<array<int, 6>>& res)
    {
        for (int i = m; i <= n; i += m)
        {
            array<int, 6> arr;
            arr[0] = i;
            TListHash tab(i);
            arr[1] = table_test_insert(tab, data, i);
            arr[2] = table_test_find(tab, data, i);
            arr[3] = table_test_find_random(tab, data, i);
            arr[4] = table_test_delete(tab, data, i);
            table_test_insert(tab, data, i);
            arr[5] = table_test_delete_random(tab, data, i);
            res.push_back(arr);
        }
        cout << "List Hash ended\n";
        cout.flush();
    };
    thread thr7(fu7, n, m, ref(results[6]));
    // TListHash with small size
    function<void(int, int, vector<array<int, 6>>&)> fu8 = [&data](int n, int m, vector<array<int, 6>>& res)
    {
        for (int i = m; i <= n; i += m)
        {
            array<int, 6> arr;
            arr[0] = i;
            TListHash tab((i / 2 > 0)?(i / 2): 1);
            arr[1] = table_test_insert(tab, data, i);
            arr[2] = table_test_find(tab, data, i);
            arr[3] = table_test_find_random(tab, data, i);
            arr[4] = table_test_delete(tab, data, i);
            table_test_insert(tab, data, i);
            arr[5] = table_test_delete_random(tab, data, i);
            res.push_back(arr);
        }
        cout << "small List Hash ended\n";
        cout.flush();
    };
    thread thr8(fu8, n, m, ref(results[7]));

    thr1.join();
    thr2.join();
    thr3.join();
    thr4.join();
    thr5.join();
    thr6.join();
    thr7.join();
    thr8.join();

    ofstream output("results.txt");
    output << "n ";
    vector<string> info = {"TScanTable ", "TSortTable ", "TTreeTable ", "TBalanceTree ", "TArrayHash ", "TArrayHash_b ", "TListHash ", "TListHash_s "};
    for (string s: info)
        for (int i = 0; i < 5; ++i)
            output << s;
    output << '\n';
    for (int i = 0; i < results[0].size(); ++i)
    {
        output << left << setw(5) << results[0][i][0] << ' ';
        for (int j = 0; j < 8; ++j)
            for (int k = 1; k < 6; ++k)
                output << setw(9) << results[j][i][k] << ' ';
        output << '\n';
    }
    output.close();
}
