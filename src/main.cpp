#include <iostream>
#include <string>
#include "Parser.h"

int main()
{
    std::cout << "=================================\n";
    std::cout << "      Mini Database Engine\n";
    std::cout << "=================================\n";

    Parser parser;

    while (true)
    {
        std::string command;

        std::cout << "MiniDB> ";
        std::getline(std::cin, command);

        if (command == "exit")
            break;

        CommandType type = parser.parse(command);

        switch (type)
        {
            case CommandType::CREATE:
                std::cout << "CREATE command detected\n";
                break;

            case CommandType::INSERT:
                std::cout << "INSERT command detected\n";
                break;

            case CommandType::SELECT:
                std::cout << "SELECT command detected\n";
                break;

            case CommandType::UPDATE:
                std::cout << "UPDATE command detected\n";
                break;

            case CommandType::DELETE_CMD:
                std::cout << "DELETE command detected\n";
                break;

            default:
                std::cout << "Unknown command\n";
        }
    }

    std::cout << "Database Closed.\n";

    return 0;
}