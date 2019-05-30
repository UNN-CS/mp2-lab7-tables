#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include "sorttable.h"
#include "balancetree.h"
#include "arrayhash.h"
#include "listhash.h"
#include "word.h"

int main() {
    setlocale(0, "");
    const int number_of_subjects = 5;
    const int number_of_groups = 1;
    std::ifstream in;
    for (int i = 0; i < number_of_groups; ++i) {
        in.open("group" + std::to_string(i + 1) + ".txt");
        if (!in.is_open())
            return 1;
        std::string surname, name;
        std::vector <TWord> marks_array;
        TScanTable scan_table;
        TSortTable sort_table;
        TTreeTable tree_table;
        TBalanceTree btree_table;
        TArrayHash ahash_table;
        TListHash lhash_table;
        while (!in.eof()) {
            in >> surname >> name;
            std::string marks;
            for (int i = 0; i < number_of_subjects; ++i) {
                std::string x;
                in >> x;
                marks += x;
                if (i + 1 != number_of_subjects)
                    marks.push_back(' ');
            }
            marks_array.push_back(TWord(marks));
            scan_table.InsRecord(surname + " " + name, &marks_array.back());
            sort_table.InsRecord(surname + " " + name, &marks_array.back());
            tree_table.InsRecord(surname + " " + name, &marks_array.back());
            btree_table.InsRecord(surname + " " + name, &marks_array.back());
            ahash_table.InsRecord(surname + " " + name, &marks_array.back());
            lhash_table.InsRecord(surname + " " + name, &marks_array.back());
        }
        std::cout << "Insert:" << std::endl;
        std::cout << "scan_table: " << scan_table.GetEfficiency() << std::endl;
        std::cout << "sort_table: " << sort_table.GetEfficiency() << std::endl;
        std::cout << "tree_table: " << tree_table.GetEfficiency() << std::endl;
        std::cout << "btree_table: " << btree_table.GetEfficiency() << std::endl;
        std::cout << "ahash_table: " << ahash_table.GetEfficiency() << std::endl;
        std::cout << "lhash_table: " << lhash_table.GetEfficiency() << std::endl;
        in.close();
        scan_table.ResetEfficiency();
        sort_table.ResetEfficiency();
        tree_table.ResetEfficiency();
        btree_table.ResetEfficiency();
        ahash_table.ResetEfficiency();
        lhash_table.ResetEfficiency();
        in.open("group" + std::to_string(i + 1) + ".txt");
        while (!in.eof()) {
            in >> surname >> name;
            std::string marks;
            for (int i = 0; i < number_of_subjects; ++i) {
                std::string x;
                in >> x;
                marks += x;
                if (i + 1 != number_of_subjects)
                    marks.push_back(' ');
            }
            marks_array.push_back(TWord(marks));
            scan_table.FindRecord(surname + " " + name);
            sort_table.FindRecord(surname + " " + name);
            tree_table.FindRecord(surname + " " + name);
            btree_table.FindRecord(surname + " " + name);
            ahash_table.FindRecord(surname + " " + name);
            lhash_table.FindRecord(surname + " " + name);
        }
        std::cout << "Find:" << std::endl;
        std::cout << "scan_table: " << scan_table.GetEfficiency() << std::endl;
        std::cout << "sort_table: " << sort_table.GetEfficiency() << std::endl;
        std::cout << "tree_table: " << tree_table.GetEfficiency() << std::endl;
        std::cout << "btree_table: " << btree_table.GetEfficiency() << std::endl;
        std::cout << "ahash_table: " << ahash_table.GetEfficiency() << std::endl;
        std::cout << "lhash_table: " << lhash_table.GetEfficiency() << std::endl;
        in.close();
        scan_table.ResetEfficiency();
        sort_table.ResetEfficiency();
        tree_table.ResetEfficiency();
        btree_table.ResetEfficiency();
        ahash_table.ResetEfficiency();
        lhash_table.ResetEfficiency();
        in.open("group" + std::to_string(i + 1) + ".txt");
        while (!in.eof()) {
            in >> surname >> name;
            std::string marks;
            for (int i = 0; i < number_of_subjects; ++i) {
                std::string x;
                in >> x;
                marks += x;
                if (i + 1 != number_of_subjects)
                    marks.push_back(' ');
            }
            marks_array.push_back(TWord(marks));
            scan_table.DelRecord(surname + " " + name);
            sort_table.DelRecord(surname + " " + name);
            tree_table.DelRecord(surname + " " + name);
//            btree_table.DelRecord(surname + " " + name);
            ahash_table.DelRecord(surname + " " + name);
            lhash_table.DelRecord(surname + " " + name);
        }
        std::cout << "Del:" << std::endl;
        std::cout << "scan_table: " << scan_table.GetEfficiency() << std::endl;
        std::cout << "sort_table: " << sort_table.GetEfficiency() << std::endl;
        std::cout << "tree_table: " << tree_table.GetEfficiency() << std::endl;
//        std::cout << "btree_table: " << btree_table.GetEfficiency() << std::endl;
        std::cout << "ahash_table: " << ahash_table.GetEfficiency() << std::endl;
        std::cout << "lhash_table: " << lhash_table.GetEfficiency() << std::endl;
        in.close();
    }
    return 0;
}
