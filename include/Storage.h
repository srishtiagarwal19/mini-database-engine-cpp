#pragma once

#include <string>
#include <vector>

class Storage
{
public:

    bool createTable(
        const std::string& tableName,
        const std::vector<std::string>& columns);

    bool insertRecord(
        const std::string& tableName,
        const std::vector<std::string>& values);

    bool selectAll(
        const std::string& tableName);

    bool selectColumns(
        const std::string& tableName,
        const std::vector<std::string>& columns);

    bool selectWhere(
        const std::string& tableName,
        const std::vector<std::string>& columns,
        bool selectAll,
        const std::string& whereColumn,
        const std::string& whereValue);

    bool updateRecord(
        const std::string& tableName,
        const std::string& updateColumn,
        const std::string& updateValue,
        const std::string& whereColumn,
        const std::string& whereValue);
        bool deleteRecords(
    const std::string& tableName,
    const std::string& whereColumn,
    const std::string& whereValue);
};