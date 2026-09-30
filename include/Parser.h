#pragma once

#include <string>
#include <vector>

enum class CommandType
{
    CREATE,
    INSERT,
    SELECT,
    UPDATE,
    DELETE_CMD,
    UNKNOWN
};

struct Command
{
    CommandType type;

    std::string tableName;

    std::vector<std::string> columns;

    std::vector<std::string> values;

    bool selectAll = false;

    std::string whereColumn;

    std::string whereValue;

    bool hasWhere = false;

    std::string updateColumn;

    std::string updateValue;
};

class Parser
{
public:
    Command parse(const std::string& command);
};