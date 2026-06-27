#pragma once

#include <string>

enum class CommandType
{
    CREATE,
    INSERT,
    SELECT,
    UPDATE,
    DELETE_CMD,
    UNKNOWN
};

class Parser
{
public:
    CommandType parse(const std::string& command);
};