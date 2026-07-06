#pragma once

#include <string>
#include <vector>

class Storage
{
public:
    bool createTable(
        const std::string& tableName,
        const std::vector<std::string>& columns);
};