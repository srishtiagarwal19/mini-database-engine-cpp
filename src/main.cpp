#include <iostream>
#include <string>
#include "Parser.h"

int main()
{
    std::cout << "=================================\n";
    std::cout << "      Mini Database Engine\n";
    std::cout << "=================================\n";

    Parser parser;

    while (true)
    {
        std::string command;

        std::cout << "MiniDB> ";
        std::getline(std::cin, command);

        if (command == "exit")
            break;

        Command cmd = parser.parse(command);

switch(cmd.type)
{
    case CommandType::CREATE:

        std::cout<<"Command : CREATE\n";

        std::cout<<"Table : "<<cmd.tableName<<"\n";

        std::cout<<"Columns\n";

        for(auto &c : cmd.columns)
            std::cout<<c<<std::endl;

        break;

    default:

        std::cout<<"Unknown command\n";
}
    }

    std::cout << "Database Closed.\n";

    return 0;
}