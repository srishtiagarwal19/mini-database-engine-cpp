#include "Parser.h"
#include <algorithm>
#include <cctype>
#include <sstream>

Command Parser::parse(const std::string& command)
{
    Command cmd;
    cmd.type = CommandType::UNKNOWN;

    // Make a copy of the input
    std::string input = command;

    // Remove leading spaces
    while (!input.empty() && std::isspace((unsigned char)input.front()))
        input.erase(input.begin());

    // Remove trailing spaces
    while (!input.empty() && std::isspace((unsigned char)input.back()))
        input.pop_back();

    // Lowercase copy for keyword matching
    std::string lowerCommand = input;

    std::transform(lowerCommand.begin(),
                   lowerCommand.end(),
                   lowerCommand.begin(),
                   [](unsigned char c)
                   {
                       return std::tolower(c);
                   });

    // ---------------- CREATE TABLE ----------------
    if (lowerCommand.rfind("create table", 0) == 0)
    {
        cmd.type = CommandType::CREATE;

        size_t tablePos = lowerCommand.find("table");
        size_t bracketPos = input.find("(");

        if (tablePos == std::string::npos || bracketPos == std::string::npos)
            return cmd;

        cmd.tableName = input.substr(tablePos + 5,
                                     bracketPos - (tablePos + 5));

        // Trim table name
        while (!cmd.tableName.empty() &&
               std::isspace((unsigned char)cmd.tableName.front()))
            cmd.tableName.erase(cmd.tableName.begin());

        while (!cmd.tableName.empty() &&
               std::isspace((unsigned char)cmd.tableName.back()))
            cmd.tableName.pop_back();

        size_t closePos = input.find(")");

        if (closePos == std::string::npos)
            return cmd;

        std::string cols =
            input.substr(bracketPos + 1,
                         closePos - bracketPos - 1);

        std::stringstream ss(cols);

        std::string col;

        while (getline(ss, col, ','))
        {
            while (!col.empty() &&
                   std::isspace((unsigned char)col.front()))
                col.erase(col.begin());

            while (!col.empty() &&
                   std::isspace((unsigned char)col.back()))
                col.pop_back();

            cmd.columns.push_back(col);
        }

        return cmd;
    }

    // ---------------- INSERT ----------------
    if (lowerCommand.rfind("insert into", 0) == 0)
    {
        cmd.type = CommandType::INSERT;
        return cmd;
    }

    // ---------------- SELECT ----------------
    if (lowerCommand.rfind("select", 0) == 0)
    {
        cmd.type = CommandType::SELECT;
        return cmd;
    }

    // ---------------- UPDATE ----------------
    if (lowerCommand.rfind("update", 0) == 0)
    {
        cmd.type = CommandType::UPDATE;
        return cmd;
    }

    // ---------------- DELETE ----------------
    if (lowerCommand.rfind("delete", 0) == 0)
    {
        cmd.type = CommandType::DELETE_CMD;
        return cmd;
    }

    return cmd;
}