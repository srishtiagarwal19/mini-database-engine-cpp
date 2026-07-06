#pragma once

#include <string>
#include "Parser.h"
#include "Storage.h"

class Database
{
private:
    Parser parser;
    Storage storage;

public:
    void execute(const std::string& command);
};