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

    if (cmd.hasWhere)
    {
        storage.selectWhere(
            cmd.tableName,
            cmd.columns,
            cmd.selectAll,
            cmd.whereColumn,
            cmd.whereValue);
    }
    else if (cmd.selectAll)
    {
        if (!storage.selectAll(cmd.tableName))
        {
            std::cout << "Error: Table '" << cmd.tableName
                      << "' does not exist.\n";
        }
    }
    else if (!cmd.columns.empty())
    {
        storage.selectColumns(
            cmd.tableName,
            cmd.columns);
    }
    else
    {
        std::cout << "Error: Invalid SELECT query.\n";
    }

    break;

       case CommandType::UPDATE:

    if (!cmd.hasWhere)
    {
        std::cout << "Error: UPDATE requires a WHERE condition.\n";
        break;
    }

    if (storage.updateRecord(
            cmd.tableName,
            cmd.updateColumn,
            cmd.updateValue,
            cmd.whereColumn,
            cmd.whereValue))
    {
        std::cout << "Record(s) updated successfully.\n";
    }
    else
    {
        std::cout << "No matching records found or update failed.\n";
    }

    break;
        case CommandType::DELETE_CMD:

    if (!cmd.hasWhere)
    {
        std::cout << "Error: DELETE requires a WHERE condition.\n";
        break;
    }

    if (storage.deleteRecords(
            cmd.tableName,
            cmd.whereColumn,
            cmd.whereValue))
    {
        std::cout << "Record(s) deleted successfully.\n";
    }
    else
    {
        std::cout << "No matching records found or delete failed.\n";
    }

    break;
        default:

            std::cout << "Unknown command.\n";
    }
}