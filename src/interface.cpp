#include <iostream>

#include "interface.hpp"

void Interface::PrintMainInterface()
{
    system("cls");
    std::cout << "\tTables testing kit" << std::endl << std::endl;

    std::cout << "1. Efficeincy tests" << std::endl << std::endl;
    std::cout << "2. Google tests" << std::endl << std::endl;
    std::cout << "3. Exit" << std::endl << std::endl;
}

void Interface::PrintEffTestsInterface()
{
    system("cls");
    std::cout << "\tEfficiency tests" << std::endl << std::endl;

    std::cout << "1. Start" << std::endl << std::endl;
    std::cout << "2. Back" << std::endl << std::endl;
}

void Interface::PrintGoogleTestsInterface()
{
    system("cls");
    std::cout << "\tGoogle tests" << std::endl << std::endl;

    std::cout << "1. Start" << std::endl << std::endl;
    std::cout << "2. Back" << std::endl << std::endl;
}
