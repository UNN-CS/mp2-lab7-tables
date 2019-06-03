#include <iostream>

#include <gtest.h>

#include "tabletestkit.hpp"

void TableTestKit::StartKit(int argc, char **argv)
{
    int action = 0;

    while(action != 101)
    {
        mainUI.PrintMainInterface();

        std::cin >> action;

        switch (action)
        {
        case 1:
            EfficiencyTests();
            break;

        case 2:
            GoogleTests(argc, argv);
            break;

        case 3:
            action = 101;
            break;

        default:
            action = 0;
            break;
        }
    }
}

void TableTestKit::EfficiencyTests()
{
    int action = 0;
    int subjCount;
    const int groupCount = 2;

    while(action != 101)
    {
        mainUI.PrintEffTestsInterface();

        std::cin >> action;

        switch (action)
        {
        case 1:
            system("cls");
            std::cout << "\tEfficiency tests" << std::endl << std::endl;

            for (int i = 0; i < groupCount; i++)
            {
                std::string fileName = "group" + std::to_string(i + 1) + ".txt";
                std::string surname, name, temp;
                std::vector<TTabRecord> marksArr;

                TScanTable scanTable;
                TSortTable sortTable;
                TTreeTable treeTable;
                TBalanceTree balancedTreeTable;
                TArrayHash arrHashTable;
                TListHash listHashTable;

                in.open(fileName.c_str(), std::ifstream::out);

                if (!in.is_open())
                {
                    std::cout << "fopen error";
                    std::cin.get();
            
                    break;
                }

                in >> subjCount;
                for (int i = 0; i < subjCount + 1; i++)
                    in >> temp;

                std::cout << "\tGroup " << i + 1 << std::endl << std::endl;

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
                    arrHashTable.InsRecord(surname + " " + name, &marksArr.back());
                    listHashTable.InsRecord(surname + " " + name, &marksArr.back());

                    std::cout << surname << " " << name << " " << marksArr.back().GetKey() << std::endl;
                }
                std::cout << std::endl;
                in.close();

                std::cout << "\tInsert efficiency:" << std::endl;
                std::cout << "scanTable: " << scanTable.GetEfficiency() << std::endl;
                std::cout << "sortTable: " << sortTable.GetEfficiency() << std::endl;
                std::cout << "treeTable: " << treeTable.GetEfficiency() << std::endl;
                std::cout << "balancedTreeTable: " << balancedTreeTable.GetEfficiency() << std::endl;
                std::cout << "arrHashTable: " << arrHashTable.GetEfficiency() << std::endl;
                std::cout << "listHashTable: " << listHashTable.GetEfficiency() << std::endl
                          << std::endl;

                scanTable.ResetEfficiency();
                sortTable.ResetEfficiency();
                treeTable.ResetEfficiency();
                balancedTreeTable.ResetEfficiency();
                arrHashTable.ResetEfficiency();
                listHashTable.ResetEfficiency();

                in.open(fileName, std::fstream::out);

                for (int i = 0; i < subjCount + 2; i++)
                    in >> temp;

                while (!in.eof())
                {
                    in >> surname >> name;
                    std::string marks;

                    for (int i = 0; i < subjCount; ++i)
                    {
                        std::string x;

                        in >> x;
                    }

                    scanTable.FindRecord(surname + " " + name);
                    sortTable.FindRecord(surname + " " + name);
                    treeTable.FindRecord(surname + " " + name);
                    balancedTreeTable.FindRecord(surname + " " + name);
                    arrHashTable.FindRecord(surname + " " + name);
                    listHashTable.FindRecord(surname + " " + name);
                }
                in.close();

                std::cout << "\tFind efficiency:" << std::endl;
                std::cout << "scanTable: " << scanTable.GetEfficiency() << std::endl;
                std::cout << "sortTable: " << sortTable.GetEfficiency() << std::endl;
                std::cout << "treeTable: " << treeTable.GetEfficiency() << std::endl;
                std::cout << "balancedTreeTable: " << balancedTreeTable.GetEfficiency() << std::endl;
                std::cout << "arrHashTable: " << arrHashTable.GetEfficiency() << std::endl;
                std::cout << "listHashTable: " << listHashTable.GetEfficiency() << std::endl
                          << std::endl;

        
                scanTable.ResetEfficiency();
                sortTable.ResetEfficiency();
                treeTable.ResetEfficiency();
                balancedTreeTable.ResetEfficiency();
                arrHashTable.ResetEfficiency();
                listHashTable.ResetEfficiency();

                in.open(fileName, std::fstream::out);

                for (int i = 0; i < subjCount + 2; i++)
                    in >> temp;

                while (!in.eof())
                {
                    in >> surname >> name;
                    std::string marks;

                    for (int i = 0; i < subjCount; ++i)
                    {
                        std::string x;

                        in >> x;
                    }

                    scanTable.DelRecord(surname + " " + name);
                    sortTable.DelRecord(surname + " " + name);
                    treeTable.DelRecord(surname + " " + name);
                    balancedTreeTable.DelRecord(surname + " " + name);
                    arrHashTable.DelRecord(surname + " " + name);
                    listHashTable.DelRecord(surname + " " + name);
                }
                in.close();

                std::cout << "\tDelete efficiency:" << std::endl;
                std::cout << "scanTable: " << scanTable.GetEfficiency() << std::endl;
                std::cout << "sortTable: " << sortTable.GetEfficiency() << std::endl;
                std::cout << "treeTable: " << treeTable.GetEfficiency() << std::endl;
                std::cout << "balancedTreeTable: " << balancedTreeTable.GetEfficiency() << std::endl;
                std::cout << "arrHashTable: " << arrHashTable.GetEfficiency() << std::endl;
                std::cout << "listHashTable: " << listHashTable.GetEfficiency() << std::endl
                          << std::endl;

                scanTable.ResetEfficiency();
                sortTable.ResetEfficiency();
                treeTable.ResetEfficiency();
                balancedTreeTable.ResetEfficiency();
                arrHashTable.ResetEfficiency();
                listHashTable.ResetEfficiency();
            }

            system("pause");
            break;
        
        case 2:
            action = 101;
            break;

        default:
            action = 0;
            break;
        }
    }
}

void TableTestKit::GoogleTests(int argc, char **argv)
{
    int action = 0;

    while (action != 101)
    {
        mainUI.PrintGoogleTestsInterface();

        std::cin >> action;

        switch (action)
        {
        case 1:
            ::testing::InitGoogleTest(&argc, argv);
            RUN_ALL_TESTS();

            system("pause");
            break;
        
        case 2:
            action = 101;
            break;

        default:
            action = 0;
            break;
        }
    }
}
