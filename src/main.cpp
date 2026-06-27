#include <iostream>

int main()
{
    std::cout << "=================================\n";
    std::cout << "      Mini Database Engine\n";
    std::cout << "=================================\n";

    while (true)
    {
        std::string command;

        std::cout << "MiniDB> ";

        getline(std::cin, command);

        if (command == "exit")
            break;

        std::cout << "You entered: " << command << std::endl;
    }

    std::cout << "Database Closed.\n";

    return 0;
}