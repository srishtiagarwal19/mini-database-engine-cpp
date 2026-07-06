#include "Storage.h"
#include <filesystem>
#include <fstream>

bool Storage::createTable(
        const std::string& tableName,
        const std::vector<std::string>& columns)
{
    std::string filename = "data/" + tableName + ".tbl";
  if(std::filesystem::exists(filename))
    {
        return false;
    }
    std::ofstream table(filename);

    if(!table)
        return false;

    table.close();

    std::ofstream meta("data/metadata.txt", std::ios::app);

    meta << tableName << "\n";

    for(auto &c : columns)
        meta << c << "\n";

    meta << "\n";

    meta.close();

    return true;
}