#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "TSortTable.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"
#include "TTabRecord.h"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "Russian");
    const int marksCount = 5;
    const int keyCount = 2;
    std::ifstream file;

    for (int i = 0; i < keyCount; i++)
    {
        std::string fileName = "key"+std::to_string(i+1)+".txt";
        file.open(fileName);

        if (file.is_open()) 
            cout << "Все ОК! Файл " + std::to_string(i+1) + " открыт!\n\n" << endl;
        else
        {
            cout << "Файл не открыт!\n\n" << endl;
            return -1;
        }

        std::string surname, name;
        std::vector<TTabRecord> marksArr;

        TScanTable scanTable;
        TSortTable sortTable;
        TTreeTable treeTable;
        TBalanceTree balancedTreeTable;
        TArrayHash arrHashTale;
        TListHash listHashTable;

        while (!file.eof())
        {
            file >> name >> surname;
            std::string marks;

            for (int i = 0; i < marksCount; ++i)
            {
                std::string x;

                file >> x;
                marks += x;

                if (i + 1 != marksCount)
                    marks.push_back(' ');
            }

            marksArr.push_back(TTabRecord(marks));
            scanTable.InsRecord(surname + " " + name, &marksArr.back());
            sortTable.InsRecord(surname + " " + name, &marksArr.back());
            treeTable.InsRecord(surname + " " + name, &marksArr.back());
            balancedTreeTable.InsRecord(surname + " " + name, &marksArr.back());
            arrHashTale.InsRecord(surname + " " + name, &marksArr.back());
            listHashTable.InsRecord(surname + " " + name, &marksArr.back());

            std::cout << name << " " << surname << " " << marksArr.back().GetKey() << std::endl;
        }
        std::cout << "---------------------------------------"<<std::endl;

        std::cout << "Вставка:" << std::endl;
        std::cout << "scanTable: " << scanTable.GetEfficiency() << std::endl;
        std::cout << "sortTable: " << sortTable.GetEfficiency() << std::endl;
        std::cout << "treeTable: " << treeTable.GetEfficiency() << std::endl;
        std::cout << "balancedTreeTable: " << balancedTreeTable.GetEfficiency() << std::endl;
        std::cout << "arrHashTale: " << arrHashTale.GetEfficiency() << std::endl;
        std::cout << "listHashTable: " << listHashTable.GetEfficiency() << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        file.close();

        scanTable.ResetEfficiency();
        sortTable.ResetEfficiency();
        treeTable.ResetEfficiency();
        balancedTreeTable.ResetEfficiency();
        arrHashTale.ResetEfficiency();
        listHashTable.ResetEfficiency();

        file.open(fileName);

        while (!file.eof())
        {
            file >> surname >> name;
            std::string marks;

            for (int i = 0; i < marksCount; ++i)
            {
                std::string x;

                file >> x;
                marks += x;

                if (i + 1 != marksCount)
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

        std::cout << "Поиск:" << std::endl;
        std::cout << "scanTable: " << scanTable.GetEfficiency() << std::endl;
        std::cout << "sortTable: " << sortTable.GetEfficiency() << std::endl;
        std::cout << "treeTable: " << treeTable.GetEfficiency() << std::endl;
        std::cout << "balancedTreeTable: " << balancedTreeTable.GetEfficiency() << std::endl;
        std::cout << "arrHashTale: " << arrHashTale.GetEfficiency() << std::endl;
        std::cout << "listHashTable: " << listHashTable.GetEfficiency() << std::endl;
        std::cout << "---------------------------------------" << std::endl;

        file.close();
        scanTable.ResetEfficiency();
        sortTable.ResetEfficiency();
        treeTable.ResetEfficiency();
        balancedTreeTable.ResetEfficiency();
        arrHashTale.ResetEfficiency();
        listHashTable.ResetEfficiency();

        file.open(fileName);

        while (!file.eof())
        {
            file >> surname >> name;
            std::string marks;

            for (int i = 0; i < marksCount; ++i)
            {
                std::string x;

                file >> x;
                marks += x;

                if (i + 1 != marksCount)
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

        std::cout << "Удаление:" << std::endl;
        std::cout << "scanTable: " << scanTable.GetEfficiency() << std::endl;
        std::cout << "sortTable: " << sortTable.GetEfficiency() << std::endl;
        std::cout << "treeTable: " << treeTable.GetEfficiency() << std::endl;
        std::cout << "balancedTreeTable: " << balancedTreeTable.GetEfficiency() << std::endl;
        std::cout << "arrHashTale: " << arrHashTale.GetEfficiency() << std::endl;
        std::cout << "listHashTable: " << listHashTable.GetEfficiency() << std::endl;
        std::cout << "---------------------------------------" << std::endl;

        file.close();
    }

    std::cin.get();

    return 0;
}