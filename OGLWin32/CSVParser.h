#pragma once 
#include "Proxy.h"
#include "DataTable.h"
#include <vector>
#include <iostream>
#include <filesystem>
#include <sstream>


class CSVParser
{
public:
    CSVParser();
    static DataTable Parse(std::tr2::sys::wpath opened);
private:

    static void AddToCols(const std::string& newline, DataTable& cols);
    static void ResetStream(std::ifstream& stream);
    static DataTable GetCols(std::ifstream& stream);
    static std::vector<std::string> SplitLine(const std::string& opened);
};