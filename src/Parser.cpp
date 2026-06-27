#include "Parser.h"

CommandType Parser::parse(const std::string& command)
{
    if(command.find("CREATE TABLE") == 0)
        return CommandType::CREATE;

    if(command.find("INSERT INTO") == 0)
        return CommandType::INSERT;

    if(command.find("SELECT") == 0)
        return CommandType::SELECT;

    if(command.find("UPDATE") == 0)
        return CommandType::UPDATE;

    if(command.find("DELETE") == 0)
        return CommandType::DELETE_CMD;

    return CommandType::UNKNOWN;
}