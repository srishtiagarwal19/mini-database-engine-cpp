#include "Storage.h"

#include <fstream>
#include <filesystem>
#include <iostream>
bool Storage::createTable(
    const std::string& tableName,
    const std::vector<std::string>& columns)
{
    std::string filename = "data/" + tableName + ".tbl";

    // Check if table already exists
    if (std::filesystem::exists(filename))
    {
        return false;
    }

    // Create table file
    std::ofstream table(filename);

    if (!table)
        return false;

    table.close();

    // Store metadata
    std::ofstream meta("data/metadata.txt", std::ios::app);

    if (!meta)
        return false;

    meta << tableName << "\n";

    for (const auto& column : columns)
    {
        meta << column << "\n";
    }

    meta << "\n";

    meta.close();

    return true;
}

bool Storage::insertRecord(
    const std::string& tableName,
    const std::vector<std::string>& values)
{
    std::string filename = "data/" + tableName + ".tbl";

    // Check if table exists
    if (!std::filesystem::exists(filename))
    {
        return false;
    }

    // Open table file in append mode
    std::ofstream file(filename, std::ios::app);

    if (!file)
        return false;

    // Write comma-separated values
    for (size_t i = 0; i < values.size(); i++)
    {
        file << values[i];

        if (i != values.size() - 1)
            file << ",";
    }

    file << "\n";

    file.close();

    return true;
}
bool Storage::selectAll(const std::string& tableName)
{
    std::string filename = "data/" + tableName + ".tbl";

    if (!std::filesystem::exists(filename))
    {
        return false;
    }

    // Read metadata
    std::ifstream meta("data/metadata.txt");

    if (!meta)
    {
        return false;
    }

    std::string line;
    bool foundTable = false;

    // Find the table in metadata
    while (std::getline(meta, line))
    {
        if (line == tableName)
        {
            foundTable = true;
            break;
        }
    }

    // Read column names
    std::vector<std::string> columns;

    if (foundTable)
    {
        while (std::getline(meta, line))
        {
            if (line.empty())
                break;

            columns.push_back(line);
        }
    }

    meta.close();

    // Print column names
    for (size_t i = 0; i < columns.size(); i++)
    {
        std::cout << columns[i];

        if (i != columns.size() - 1)
            std::cout << " | ";
    }

    std::cout << "\n";

    // Separator
    for (size_t i = 0; i < columns.size(); i++)
    {
        std::cout << "--------";

        if (i != columns.size() - 1)
            std::cout << "-+-";
    }

    std::cout << "\n";

    // Read table records
    std::ifstream file(filename);

    if (!file)
    {
        return false;
    }

    while (std::getline(file, line))
    {
        std::cout << line << "\n";
    }

    file.close();

    return true;
}