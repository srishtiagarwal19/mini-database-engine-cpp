#include <iostream>
#include <string>

#include "Parser.h"
#include "Storage.h"

int main()
{
    std::cout << "=================================\n";
    std::cout << "      Mini Database Engine\n";
    std::cout << "=================================\n";

    Parser parser;
    Storage storage;

    while (true)
    {
        std::string command;

        std::cout << "MiniDB> ";
        std::getline(std::cin, command);

        if (command == "exit")
            break;

        Command cmd = parser.parse(command);

        switch (cmd.type)
        {
            case CommandType::CREATE:

                if (storage.createTable(cmd.tableName, cmd.columns))
                {
                    std::cout << "Table created successfully.\n";
                }
                else
                {
                    std::cout << "Error: Table '" << cmd.tableName
          << "' already exists.\n";
                }

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