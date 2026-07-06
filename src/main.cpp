#include <iostream>
#include <string>

#include "Database.h"

int main()
{
    Database db;

    std::cout << "=================================\n";
    std::cout << "      Mini Database Engine\n";
    std::cout << "=================================\n";

    while (true)
    {
        std::string command;

        std::cout << "MiniDB> ";

        std::getline(std::cin, command);

        if(command=="exit")
            break;

        db.execute(command);
    }

    std::cout << "Database Closed.\n";

    return 0;
}