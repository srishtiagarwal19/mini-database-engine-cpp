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
bool Storage::selectColumns(
    const std::string& tableName,
    const std::vector<std::string>& columns)
{
    std::string filename = "data/" + tableName + ".tbl";

    if (!std::filesystem::exists(filename))
    {
        return false;
    }

    // Read metadata to get all column names
    std::ifstream meta("data/metadata.txt");

    if (!meta)
    {
        return false;
    }

    std::string line;
    bool foundTable = false;
    std::vector<std::string> allColumns;

    while (std::getline(meta, line))
    {
        if (line == tableName)
        {
            foundTable = true;
            break;
        }
    }

    if (foundTable)
    {
        while (std::getline(meta, line))
        {
            if (line.empty())
                break;

            allColumns.push_back(line);
        }
    }

    meta.close();

    // Find the index of each requested column
    std::vector<int> columnIndexes;

    for (const auto& requestedColumn : columns)
    {
        int index = -1;

        for (size_t i = 0; i < allColumns.size(); i++)
        {
            if (allColumns[i] == requestedColumn)
            {
                index = static_cast<int>(i);
                break;
            }
        }

        if (index == -1)
        {
            std::cout << "Error: Column '" << requestedColumn
                      << "' does not exist.\n";

            return false;
        }

        columnIndexes.push_back(index);
    }

    // Print selected column names
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

    // Open table
    std::ifstream file(filename);

    if (!file)
    {
        return false;
    }

    // Read each record
    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::vector<std::string> values;
        std::string value;

        while (std::getline(ss, value, ','))
        {
            values.push_back(value);
        }

        // Print only requested columns
        for (size_t i = 0; i < columnIndexes.size(); i++)
        {
            int index = columnIndexes[i];

            if (index < static_cast<int>(values.size()))
            {
                std::cout << values[index];
            }

            if (i != columnIndexes.size() - 1)
                std::cout << " | ";
        }

        std::cout << "\n";
    }

    file.close();

    return true;
}
bool Storage::selectWhere(
    const std::string& tableName,
    const std::vector<std::string>& columns,
    bool selectAll,
    const std::string& whereColumn,
    const std::string& whereValue)
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
    std::vector<std::string> allColumns;

    // Find table
    while (std::getline(meta, line))
    {
        if (line == tableName)
        {
            foundTable = true;
            break;
        }
    }

    if (foundTable)
    {
        while (std::getline(meta, line))
        {
            if (line.empty())
                break;

            allColumns.push_back(line);
        }
    }

    meta.close();

    // Find WHERE column index
    int whereIndex = -1;

    for (size_t i = 0; i < allColumns.size(); i++)
    {
        if (allColumns[i] == whereColumn)
        {
            whereIndex = static_cast<int>(i);
            break;
        }
    }

    if (whereIndex == -1)
    {
        std::cout << "Error: Column '" << whereColumn
                  << "' does not exist.\n";

        return false;
    }

    // Determine which columns to print
    std::vector<int> selectedIndexes;

    if (selectAll)
    {
        for (size_t i = 0; i < allColumns.size(); i++)
        {
            selectedIndexes.push_back(static_cast<int>(i));
        }
    }
    else
    {
        for (const auto& column : columns)
        {
            int index = -1;

            for (size_t i = 0; i < allColumns.size(); i++)
            {
                if (allColumns[i] == column)
                {
                    index = static_cast<int>(i);
                    break;
                }
            }

            if (index == -1)
            {
                std::cout << "Error: Column '" << column
                          << "' does not exist.\n";

                return false;
            }

            selectedIndexes.push_back(index);
        }
    }

    // Print headers
    for (size_t i = 0; i < selectedIndexes.size(); i++)
    {
        std::cout << allColumns[selectedIndexes[i]];

        if (i != selectedIndexes.size() - 1)
            std::cout << " | ";
    }

    std::cout << "\n";

    // Separator
    for (size_t i = 0; i < selectedIndexes.size(); i++)
    {
        std::cout << "--------";

        if (i != selectedIndexes.size() - 1)
            std::cout << "-+-";
    }

    std::cout << "\n";

    // Read records
    std::ifstream file(filename);

    if (!file)
    {
        return false;
    }

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::vector<std::string> values;
        std::string value;

        while (std::getline(ss, value, ','))
        {
            values.push_back(value);
        }

        // Check WHERE condition
        if (whereIndex >= static_cast<int>(values.size()))
        {
            continue;
        }

        if (values[whereIndex] != whereValue)
        {
            continue;
        }

        // Print matching record
        for (size_t i = 0; i < selectedIndexes.size(); i++)
        {
            int index = selectedIndexes[i];

            if (index < static_cast<int>(values.size()))
            {
                std::cout << values[index];
            }

            if (i != selectedIndexes.size() - 1)
                std::cout << " | ";
        }

        std::cout << "\n";
    }

    file.close();

    return true;
}
bool Storage::updateRecord(
    const std::string& tableName,
    const std::string& updateColumn,
    const std::string& updateValue,
    const std::string& whereColumn,
    const std::string& whereValue)
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
    std::vector<std::string> columns;

    // Find table
    while (std::getline(meta, line))
    {
        if (line == tableName)
        {
            foundTable = true;
            break;
        }
    }

    // Read column names
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

    // Find UPDATE column
    int updateIndex = -1;

    for (size_t i = 0; i < columns.size(); i++)
    {
        if (columns[i] == updateColumn)
        {
            updateIndex = static_cast<int>(i);
            break;
        }
    }

    if (updateIndex == -1)
    {
        std::cout << "Error: Column '" << updateColumn
                  << "' does not exist.\n";

        return false;
    }

    // Find WHERE column
    int whereIndex = -1;

    for (size_t i = 0; i < columns.size(); i++)
    {
        if (columns[i] == whereColumn)
        {
            whereIndex = static_cast<int>(i);
            break;
        }
    }

    if (whereIndex == -1)
    {
        std::cout << "Error: Column '" << whereColumn
                  << "' does not exist.\n";

        return false;
    }

    // Read all records
    std::ifstream file(filename);

    if (!file)
    {
        return false;
    }

    std::vector<std::vector<std::string>> records;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::vector<std::string> values;
        std::string value;

        while (std::getline(ss, value, ','))
        {
            values.push_back(value);
        }

        records.push_back(values);
    }

    file.close();

    // Update matching records
    bool updated = false;

    for (auto& record : records)
    {
        if (whereIndex < static_cast<int>(record.size()) &&
            record[whereIndex] == whereValue)
        {
            if (updateIndex < static_cast<int>(record.size()))
            {
                record[updateIndex] = updateValue;
                updated = true;
            }
        }
    }

    // Rewrite the file
    std::ofstream output(filename);

    if (!output)
    {
        return false;
    }

    for (const auto& record : records)
    {
        for (size_t i = 0; i < record.size(); i++)
        {
            output << record[i];

            if (i != record.size() - 1)
                output << ",";
        }

        output << "\n";
    }

    output.close();

    return updated;
}