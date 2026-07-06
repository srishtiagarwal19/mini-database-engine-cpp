#include "Database.h"

#include <iostream>

void Database::execute(const std::string& command)
{
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

            if (storage.insertRecord(cmd.tableName, cmd.values))
            {
                std::cout << "Record inserted successfully.\n";
            }
            else
            {
                std::cout << "Error: Table '" << cmd.tableName
                          << "' does not exist.\n";
            }

            break;

        case CommandType::SELECT:

            std::cout << "SELECT will be implemented in Milestone 6.\n";

            break;

        case CommandType::UPDATE:

            std::cout << "UPDATE will be implemented in a future milestone.\n";

            break;

        case CommandType::DELETE_CMD:

            std::cout << "DELETE will be implemented in a future milestone.\n";

            break;

        default:

            std::cout << "Unknown command.\n";
    }
}