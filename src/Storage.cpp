#include "Storage.h"

#include <fstream>
#include <filesystem>

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