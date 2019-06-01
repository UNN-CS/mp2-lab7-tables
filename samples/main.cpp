#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "tsorttable.hpp"
#include "tbalancetree.hpp"
#include "tarrayhash.hpp"
#include "tlisthash.hpp"
#include "ttabrecord.hpp"

int main(int argc, char **argv)
{
    const int subjCount = 5;
    const int groupCount = 1;
    std::ifstream in;

    for (int i = 0; i < groupCount; i++)
    {
        std::string fileName = "group" + std::to_string(i + 1) + ".txt";
        in.open(fileName.c_str(), std::ifstream::out);

        if (!in.is_open())
        {
            std::cout << "fopen error";
            return 1;
        }

        std::string surname, name;
        std::vector<TTabRecord> marksArr;

        TScanTable scanTable;
        TSortTable sortTable;
        TTreeTable treeTable;
        TBalanceTree balancedTreeTable;
        TArrayHash arrHashTale;
        TListHash listHashTable;

        while (!in.eof())
        {
            in >> name >> surname;
            std::string marks;

            for (int i = 0; i < subjCount; ++i)
            {
                std::string x;

                in >> x;
                marks += x;

                if (i + 1 != subjCount)
                    marks.push_back(' ');
            }

            marksArr.push_back(TTabRecord(marks));
            scanTable.InsRecord(surname + " " + name, &marksArr.back());
            sortTable.InsRecord(surname + " " + name, &marksArr.back());
            treeTable.InsRecord(surname + " " + name, &marksArr.back());
            balancedTreeTable.InsRecord(surname + " " + name, &marksArr.back());
            arrHashTale.InsRecord(surname + " " + name, &marksArr.back());
            listHashTable.InsRecord(surname + " " + name, &marksArr.back());

            std::cout << surname << " " << name << " " << marksArr.back().GetKey() << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Insert:" << std::endl;
        std::cout << "scanTable: " << scanTable.GetEfficiency() << std::endl;
        std::cout << "sortTable: " << sortTable.GetEfficiency() << std::endl;
        std::cout << "treeTable: " << treeTable.GetEfficiency() << std::endl;
        std::cout << "balancedTreeTable: " << balancedTreeTable.GetEfficiency() << std::endl;
        std::cout << "arrHashTale: " << arrHashTale.GetEfficiency() << std::endl;
        std::cout << "listHashTable: " << listHashTable.GetEfficiency() << std::endl
                  << std::endl;
        in.close();

        scanTable.ResetEfficiency();
        sortTable.ResetEfficiency();
        treeTable.ResetEfficiency();
        balancedTreeTable.ResetEfficiency();
        arrHashTale.ResetEfficiency();
        listHashTable.ResetEfficiency();

        in.open(fileName, std::fstream::out);

        while (!in.eof())
        {
            in >> surname >> name;
            std::string marks;

            for (int i = 0; i < subjCount; ++i)
            {
                std::string x;

                in >> x;
                marks += x;

                if (i + 1 != subjCount)
                    marks.push_back(' ');
            }

            marksArr.push_back(TTabRecord(marks));
            scanTable.FindRecord(surname + " " + name);
            sortTable.FindRecord(surname + " " + name);
            treeTable.FindRecord(surname + " " + name);
            balancedTreeTable.FindRecord(surname + " " + name);
            arrHashTale.FindRecord(surname + " " + name);
            listHashTable.FindRecord(surname + " " + name);
        }

        std::cout << "Find:" << std::endl;
        std::cout << "scanTable: " << scanTable.GetEfficiency() << std::endl;
        std::cout << "sortTable: " << sortTable.GetEfficiency() << std::endl;
        std::cout << "treeTable: " << treeTable.GetEfficiency() << std::endl;
        std::cout << "balancedTreeTable: " << balancedTreeTable.GetEfficiency() << std::endl;
        std::cout << "arrHashTale: " << arrHashTale.GetEfficiency() << std::endl;
        std::cout << "listHashTable: " << listHashTable.GetEfficiency() << std::endl
                  << std::endl;

        in.close();
        scanTable.ResetEfficiency();
        sortTable.ResetEfficiency();
        treeTable.ResetEfficiency();
        balancedTreeTable.ResetEfficiency();
        arrHashTale.ResetEfficiency();
        listHashTable.ResetEfficiency();

        in.open(fileName, std::fstream::out);

        while (!in.eof())
        {
            in >> surname >> name;
            std::string marks;

            for (int i = 0; i < subjCount; ++i)
            {
                std::string x;

                in >> x;
                marks += x;

                if (i + 1 != subjCount)
                    marks.push_back(' ');
            }

            marksArr.push_back(TTabRecord(marks));
            scanTable.DelRecord(surname + " " + name);
            sortTable.DelRecord(surname + " " + name);
            treeTable.DelRecord(surname + " " + name);
            balancedTreeTable.DelRecord(surname + " " + name);
            arrHashTale.DelRecord(surname + " " + name);
            listHashTable.DelRecord(surname + " " + name);
        }

        std::cout << "Del:" << std::endl;
        std::cout << "scanTable: " << scanTable.GetEfficiency() << std::endl;
        std::cout << "sortTable: " << sortTable.GetEfficiency() << std::endl;
        std::cout << "treeTable: " << treeTable.GetEfficiency() << std::endl;
        std::cout << "balancedTreeTable: " << balancedTreeTable.GetEfficiency() << std::endl;
        std::cout << "arrHashTale: " << arrHashTale.GetEfficiency() << std::endl;
        std::cout << "listHashTable: " << listHashTable.GetEfficiency() << std::endl
                  << std::endl;

        in.close();
    }

    std::cin.get();

    return 0;
}