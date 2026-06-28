#include "Parser.h"

#include <sstream>

Command Parser::parse(const std::string& command)
{
    Command cmd;
    cmd.type = CommandType::UNKNOWN;

    if(command.find("CREATE TABLE") == 0)
    {
        cmd.type = CommandType::CREATE;

        size_t start = command.find("TABLE") + 6;

        size_t bracket = command.find("(");

        cmd.tableName = command.substr(start, bracket-start);

        size_t close = command.find(")");

        std::string cols = command.substr(bracket+1,
                                          close-bracket-1);

        std::stringstream ss(cols);

        std::string col;

        while(getline(ss,col,','))
        {
            cmd.columns.push_back(col);
        }
    }

    return cmd;
}