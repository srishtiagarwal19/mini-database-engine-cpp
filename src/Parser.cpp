#include "Parser.h"

#include <algorithm>
#include <cctype>
#include <sstream>

Command Parser::parse(const std::string& command)
{
    Command cmd;
    cmd.type = CommandType::UNKNOWN;

    // Copy input
    std::string input = command;

    // Remove leading spaces
    while (!input.empty() &&
           std::isspace(static_cast<unsigned char>(input.front())))
    {
        input.erase(input.begin());
    }

    // Remove trailing spaces
    while (!input.empty() &&
           std::isspace(static_cast<unsigned char>(input.back())))
    {
        input.pop_back();
    }

    // Lowercase copy for keyword matching
    std::string lowerCommand = input;

    std::transform(lowerCommand.begin(),
                   lowerCommand.end(),
                   lowerCommand.begin(),
                   [](unsigned char c)
                   {
                       return std::tolower(c);
                   });

    // ================= CREATE TABLE =================

    if (lowerCommand.rfind("create table", 0) == 0)
    {
        cmd.type = CommandType::CREATE;

        size_t tablePos = lowerCommand.find("table");
        size_t bracketPos = input.find("(");

        if (tablePos == std::string::npos ||
            bracketPos == std::string::npos)
        {
            return cmd;
        }

        cmd.tableName =
            input.substr(tablePos + 5,
                         bracketPos - (tablePos + 5));

        // Trim table name
        while (!cmd.tableName.empty() &&
               std::isspace(static_cast<unsigned char>(cmd.tableName.front())))
        {
            cmd.tableName.erase(cmd.tableName.begin());
        }

        while (!cmd.tableName.empty() &&
               std::isspace(static_cast<unsigned char>(cmd.tableName.back())))
        {
            cmd.tableName.pop_back();
        }

        size_t closePos = input.find(")");

        if (closePos == std::string::npos)
        {
            return cmd;
        }

        std::string cols =
            input.substr(bracketPos + 1,
                         closePos - bracketPos - 1);

        std::stringstream ss(cols);

        std::string col;

        while (getline(ss, col, ','))
        {
            while (!col.empty() &&
                   std::isspace(static_cast<unsigned char>(col.front())))
            {
                col.erase(col.begin());
            }

            while (!col.empty() &&
                   std::isspace(static_cast<unsigned char>(col.back())))
            {
                col.pop_back();
            }

            cmd.columns.push_back(col);
        }

        return cmd;
    }

    // ================= INSERT INTO =================

    if (lowerCommand.rfind("insert into", 0) == 0)
    {
        cmd.type = CommandType::INSERT;

        size_t intoPos = lowerCommand.find("into");
        size_t valuesPos = lowerCommand.find("values");

        if (intoPos == std::string::npos ||
            valuesPos == std::string::npos)
        {
            return cmd;
        }

        cmd.tableName =
            input.substr(intoPos + 4,
                         valuesPos - (intoPos + 4));

        while (!cmd.tableName.empty() &&
               std::isspace(static_cast<unsigned char>(cmd.tableName.front())))
        {
            cmd.tableName.erase(cmd.tableName.begin());
        }

        while (!cmd.tableName.empty() &&
               std::isspace(static_cast<unsigned char>(cmd.tableName.back())))
        {
            cmd.tableName.pop_back();
        }

        size_t open = input.find("(", valuesPos);
        size_t close = input.find(")", open);

        if (open == std::string::npos ||
            close == std::string::npos)
        {
            return cmd;
        }

        std::string values =
            input.substr(open + 1,
                         close - open - 1);

        std::stringstream ss(values);

        std::string value;

        while (getline(ss, value, ','))
        {
            while (!value.empty() &&
                   std::isspace(static_cast<unsigned char>(value.front())))
            {
                value.erase(value.begin());
            }

            while (!value.empty() &&
                   std::isspace(static_cast<unsigned char>(value.back())))
            {
                value.pop_back();
            }

            cmd.values.push_back(value);
        }

        return cmd;
    }

// ================= SELECT =================

if (lowerCommand.rfind("select", 0) == 0)
{
    cmd.type = CommandType::SELECT;

    size_t fromPos = lowerCommand.find("from");

    if (fromPos == std::string::npos)
    {
        return cmd;
    }

    // Get SELECT part
    std::string selectPart =
        input.substr(6, fromPos - 6);

    // Trim spaces
    while (!selectPart.empty() &&
           std::isspace(static_cast<unsigned char>(selectPart.front())))
    {
        selectPart.erase(selectPart.begin());
    }

    while (!selectPart.empty() &&
           std::isspace(static_cast<unsigned char>(selectPart.back())))
    {
        selectPart.pop_back();
    }

    // SELECT *
    if (selectPart == "*")
    {
        cmd.selectAll = true;
    }
    else
    {
        // SELECT name,age
        std::stringstream ss(selectPart);

        std::string column;

        while (std::getline(ss, column, ','))
        {
            while (!column.empty() &&
                   std::isspace(static_cast<unsigned char>(column.front())))
            {
                column.erase(column.begin());
            }

            while (!column.empty() &&
                   std::isspace(static_cast<unsigned char>(column.back())))
            {
                column.pop_back();
            }

            cmd.columns.push_back(column);
        }
    }

    // Get everything after FROM
    std::string fromPart = input.substr(fromPos + 4);

    // Find WHERE
    std::string lowerFromPart = fromPart;

    std::transform(
        lowerFromPart.begin(),
        lowerFromPart.end(),
        lowerFromPart.begin(),
        [](unsigned char c)
        {
            return std::tolower(c);
        });

    size_t wherePos = lowerFromPart.find("where");

    if (wherePos == std::string::npos)
    {
        // No WHERE condition
        cmd.tableName = fromPart;

        while (!cmd.tableName.empty() &&
               std::isspace(static_cast<unsigned char>(cmd.tableName.front())))
        {
            cmd.tableName.erase(cmd.tableName.begin());
        }

        while (!cmd.tableName.empty() &&
               std::isspace(static_cast<unsigned char>(cmd.tableName.back())))
        {
            cmd.tableName.pop_back();
        }

        return cmd;
    }

    // Table name is before WHERE
    cmd.tableName = fromPart.substr(0, wherePos);

    while (!cmd.tableName.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.tableName.front())))
    {
        cmd.tableName.erase(cmd.tableName.begin());
    }

    while (!cmd.tableName.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.tableName.back())))
    {
        cmd.tableName.pop_back();
    }

    // Get condition after WHERE
    std::string condition =
        fromPart.substr(wherePos + 5);

    while (!condition.empty() &&
           std::isspace(static_cast<unsigned char>(condition.front())))
    {
        condition.erase(condition.begin());
    }

    while (!condition.empty() &&
           std::isspace(static_cast<unsigned char>(condition.back())))
    {
        condition.pop_back();
    }

    // Find =
    size_t equalPos = condition.find("=");

    if (equalPos == std::string::npos)
    {
        return cmd;
    }

    cmd.whereColumn = condition.substr(0, equalPos);
    cmd.whereValue = condition.substr(equalPos + 1);

    // Trim where column
    while (!cmd.whereColumn.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.whereColumn.front())))
    {
        cmd.whereColumn.erase(cmd.whereColumn.begin());
    }

    while (!cmd.whereColumn.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.whereColumn.back())))
    {
        cmd.whereColumn.pop_back();
    }

    // Trim where value
    while (!cmd.whereValue.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.whereValue.front())))
    {
        cmd.whereValue.erase(cmd.whereValue.begin());
    }

    while (!cmd.whereValue.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.whereValue.back())))
    {
        cmd.whereValue.pop_back();
    }

    cmd.hasWhere = true;

    return cmd;
}
    // ================= UPDATE =================

if (lowerCommand.rfind("update", 0) == 0)
{
    cmd.type = CommandType::UPDATE;

    // Find SET
    size_t setPos = lowerCommand.find("set");

    // Find WHERE
    size_t wherePos = lowerCommand.find("where");

    if (setPos == std::string::npos ||
        wherePos == std::string::npos)
    {
        return cmd;
    }

    // Get table name between UPDATE and SET
    cmd.tableName =
        input.substr(6, setPos - 6);

    // Trim table name
    while (!cmd.tableName.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.tableName.front())))
    {
        cmd.tableName.erase(cmd.tableName.begin());
    }

    while (!cmd.tableName.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.tableName.back())))
    {
        cmd.tableName.pop_back();
    }

    // Get SET condition
    std::string setPart =
        input.substr(setPos + 3,
                     wherePos - (setPos + 3));

    // Find =
    size_t equalPos = setPart.find("=");

    if (equalPos == std::string::npos)
    {
        return cmd;
    }

    cmd.updateColumn = setPart.substr(0, equalPos);
    cmd.updateValue = setPart.substr(equalPos + 1);

    // Trim update column
    while (!cmd.updateColumn.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.updateColumn.front())))
    {
        cmd.updateColumn.erase(cmd.updateColumn.begin());
    }

    while (!cmd.updateColumn.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.updateColumn.back())))
    {
        cmd.updateColumn.pop_back();
    }

    // Trim update value
    while (!cmd.updateValue.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.updateValue.front())))
    {
        cmd.updateValue.erase(cmd.updateValue.begin());
    }

    while (!cmd.updateValue.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.updateValue.back())))
    {
        cmd.updateValue.pop_back();
    }

    // Get WHERE condition
    std::string wherePart =
        input.substr(wherePos + 5);

    equalPos = wherePart.find("=");

    if (equalPos == std::string::npos)
    {
        return cmd;
    }

    cmd.whereColumn = wherePart.substr(0, equalPos);
    cmd.whereValue = wherePart.substr(equalPos + 1);

    // Trim WHERE column
    while (!cmd.whereColumn.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.whereColumn.front())))
    {
        cmd.whereColumn.erase(cmd.whereColumn.begin());
    }

    while (!cmd.whereColumn.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.whereColumn.back())))
    {
        cmd.whereColumn.pop_back();
    }

    // Trim WHERE value
    while (!cmd.whereValue.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.whereValue.front())))
    {
        cmd.whereValue.erase(cmd.whereValue.begin());
    }

    while (!cmd.whereValue.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.whereValue.back())))
    {
        cmd.whereValue.pop_back();
    }

    cmd.hasWhere = true;

    return cmd;
}

    // ================= DELETE =================

if (lowerCommand.rfind("delete", 0) == 0)
{
    cmd.type = CommandType::DELETE_CMD;

    // Find FROM
    size_t fromPos = lowerCommand.find("from");

    // Find WHERE
    size_t wherePos = lowerCommand.find("where");

    if (fromPos == std::string::npos ||
        wherePos == std::string::npos)
    {
        return cmd;
    }

    // Get table name between FROM and WHERE
    cmd.tableName =
        input.substr(fromPos + 4,
                     wherePos - (fromPos + 4));

    // Trim table name
    while (!cmd.tableName.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.tableName.front())))
    {
        cmd.tableName.erase(cmd.tableName.begin());
    }

    while (!cmd.tableName.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.tableName.back())))
    {
        cmd.tableName.pop_back();
    }

    // Get WHERE condition
    std::string wherePart =
        input.substr(wherePos + 5);

    size_t equalPos = wherePart.find("=");

    if (equalPos == std::string::npos)
    {
        return cmd;
    }

    cmd.whereColumn =
        wherePart.substr(0, equalPos);

    cmd.whereValue =
        wherePart.substr(equalPos + 1);

    // Trim WHERE column
    while (!cmd.whereColumn.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.whereColumn.front())))
    {
        cmd.whereColumn.erase(cmd.whereColumn.begin());
    }

    while (!cmd.whereColumn.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.whereColumn.back())))
    {
        cmd.whereColumn.pop_back();
    }

    // Trim WHERE value
    while (!cmd.whereValue.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.whereValue.front())))
    {
        cmd.whereValue.erase(cmd.whereValue.begin());
    }

    while (!cmd.whereValue.empty() &&
           std::isspace(static_cast<unsigned char>(cmd.whereValue.back())))
    {
        cmd.whereValue.pop_back();
    }

    cmd.hasWhere = true;

    return cmd;
}
    return cmd;
}