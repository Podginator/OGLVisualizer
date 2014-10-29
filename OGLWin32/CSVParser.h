#pragma once 
#include "Proxy.h"
#include "CSVColumn.h"
#include <vector>
#include <iostream>
#include <filesystem>
#include <sstream>


class CSVParser
{
public:
	CSVParser();
	static std::vector<std::vector<std::string>> Parse(std::tr2::sys::wpath opened);
private:

	static std::vector<CSVColBase*> GetCols(std::ifstream& stream, size_t size);
	static std::vector<std::string> SplitLine(const std::string& opened);

	static void AddToCols(const std::string& opened, std::vector<CSVColBase*> cols);
};