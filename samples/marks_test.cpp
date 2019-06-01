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

class marks: public TDatValue
{
    private:
    vector<double> mark;
    public:
    marks(const vector<double>& arr): TDatValue(), mark(arr)
    {

    }

    double& operator[](size_t i)
    {
        return mark[i];
    }

    const double& operator[](size_t i) const
    {
        return mark[i];
    }

    PTDatValue GetCopy()
    {
        return new marks(mark);
    }

    size_t size() const
    {
        return mark.size();
    }

};

double get_mark(TTable* tb, int subject, const string& student)
{
    PTTabRecord p = (PTTabRecord)tb->FindRecord(student);
    if (p == nullptr)
        return -1;
    return (*(marks*)p->GetValuePTR())[subject];
}

double get_average_mark(TTable* tb, const string& student)
{
    PTTabRecord p = (PTTabRecord)tb->FindRecord(student);
    if (p == nullptr)
        return -1;
    double d = 0.0;
    marks& m = *((marks*)p->GetValuePTR());
    for (int i = 0; i < m.size(); ++i)
        d += m[i];
    return d / m.size();
}

double get_average_mark(TTable* tb, int subject)
{
    double d = 0.0;
    if (tb->GetDataCount() == 0)
        return 0.0;
    for (tb->Reset(); !tb->IsTabEnded(); tb->GoNext())
        d += (*(marks*)tb->GetValuePTR())[subject];
    return d / tb->GetDataCount();
}

double get_average_mark(TTable* tb)
{
    double d = 0.0;
    size_t s = 0;
    for (tb->Reset(); !tb->IsTabEnded(); tb->GoNext())
    {
        marks& m = (*(marks*)tb->GetValuePTR());
        for (int i = 0; i < m.size(); ++i)
            d += m[i];
        s += m.size();
    }
    if (s == 0)
        return 0.0;
    return d / s;
}

int get_5_students_count(TTable* tb, int subject)
{
    int n = 0;
    for (tb->Reset(); !tb->IsTabEnded(); tb->GoNext())
        if ((*(marks*)tb->GetValuePTR())[subject] >= 5.0)
            ++n;
    return n;
}

int get_5_students_count(TTable* tb)
{
    int n = 0;
    for (tb->Reset(); !tb->IsTabEnded(); tb->GoNext())
    {
        marks& m = (*(marks*)tb->GetValuePTR());
        bool fl = true;
        for (int i = 0; i < m.size(); ++i)
            if (m[i] < 5.0)
                fl = false;
        if (fl)
            ++n;
    }
    return n;
}

double get_average_mark(TTable** tb, int size, int subject)
{
    double d = 0.0;
    int c = 0;
    for (int i = 0; i < size; ++i)
        if (tb[i]->GetDataCount() > 0)
        {
            ++c;
            d += get_average_mark(tb[i], subject);
        }
    return d / c;
}

double get_average_mark(TTable** tb, int size)
{
    double d = 0.0;
    int c = 0;
    for (int i = 0; i < size; ++i)
        if (tb[i]->GetDataCount() > 0)
        {
            ++c;
            d += get_average_mark(tb[i]);
        }
    return d / c;
}

int get_best_group(TTable** tb, int size, int subject)
{
    double d = 0.0;
    int c = 0;
    for (int i = 0; i < size; ++i)
        if (tb[i]->GetDataCount() > 0)
        {
            double b = get_average_mark(tb[i], subject);
            if (b > d)
            {
                d = b;
                c = i;
            }
        }
    return c;
}

int get_best_group(TTable** tb, int size)
{
    double d = 0.0;
    int c = 0;
    for (int i = 0; i < size; ++i)
        if (tb[i]->GetDataCount() > 0)
        {
            double b = get_average_mark(tb[i]);
            if (b > d)
            {
                d = b;
                c = i;
            }
        }
    return c;
}

int get_5_students_count(TTable** tb, int size, int subject)
{
    int c = 0;
    for (int i = 0; i < size; ++i)
        c += get_5_students_count(tb[i], subject);
    return c;
}

int get_5_students_count(TTable** tb, int size)
{
    int c = 0;
    for (int i = 0; i < size; ++i)
        c += get_5_students_count(tb[i]);
    return c;
}

int main(int argc, char** argv)
{
    int n;
    int m = 30;
    string input_file = "marks.txt";
    if (argc > 1)
    {
        input_file = argv[1];
        if (argc > 2)
            m = atoi(argv[2]);
    }
    vector<string> disciplines;
    vector<marks*> v;

    array<TTable*, 6> tab;
    tab[0] = new TScanTable(m);
    tab[1] = new TSortTable(m);
    tab[2] = new TTreeTable();
    tab[3] = new TBalanceTree();
    tab[4] = new TArrayHash(m, 1);
    tab[5] = new TListHash(m);

    ifstream in(input_file);
    in >> n;
    disciplines.resize(n);
    for (int i = 0; i < n; ++i)
    {
        string s;
        in >> s;
        disciplines[i] = s;
    }

    for (int i = 0; i < tab.size(); ++i)
    {
        int g;
        in >> g;
        for (int j = 0; j < g; ++j)
        {
            string s, c;
            vector<double> a(n);
            in >> s >> c;
            for (int k = 0; k < n; ++k)
                in >> a[k];
            v.push_back(new marks(a));
            tab[i]->InsRecord(s + ' ' + c, v.back());
        }
    }
    in.close();

    ofstream out("marks_result.txt");
    out << "average marks\n";
    for (int i = 0; i < tab.size(); ++i)
    {
        for (tab[i]->Reset(); !tab[i]->IsTabEnded(); tab[i]->GoNext())
        {
            double ww = get_average_mark(tab[i], tab[i]->GetKey());
            out << tab[i]->GetKey() << ": " << ww << '\n';
        }
    }

    for (int i = 0; i < disciplines.size(); ++i)
    {
        out << disciplines[i] << '\n';
        for (int j = 0; j < tab.size(); ++j)
        {
            double ww = get_average_mark(tab[j], i);
            out << "group " << j + 1 << ": " << ww << '\n';
        }
        out << "all: " << get_average_mark(tab.data(), tab.size(), i) << '\n';
    }
    out << "\nall subjects average: " << get_average_mark(tab.data(), tab.size()) << '\n';

    out << "\nbest groups\n";
    for (int i = 0; i < disciplines.size(); ++i)
        out << disciplines[i] << ": " << get_best_group(tab.data(), tab.size(), i) + 1 << '\n';
    out << "all: " << get_best_group(tab.data(), tab.size()) + 1 << '\n';

    out << "\ncount of students with 5 marks only\n";
    for (int i = 0; i < tab.size(); ++i)
    {
        out << "group " << i + 1 << '\n';
        for (int j = 0; j < disciplines.size(); ++j)
            out << disciplines[j] << ": " << get_5_students_count(tab[i], j) << '\n';
        out << "all: " << get_5_students_count(tab[i]) << '\n';
    }
    out << "\ncount of students with 5 marks only in all groups\n";
    for (int i = 0; i < disciplines.size(); ++i)
        out << disciplines[i] << ": " << get_5_students_count(tab.data(), tab.size(), i) << '\n';
    out << "all: " << get_5_students_count(tab.data(), tab.size()) << '\n';
    out.close();

    for (marks* i: v)
        delete i;
}
