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
	static std::vector<CSVColumn> Parse(std::tr2::sys::wpath opened);
private:

	static void AddToCols(const std::string& newline, std::vector<CSVColumn>& cols);
	static void ResetStream(std::ifstream& stream);
	static std::vector<CSVColumn> GetCols(std::ifstream& stream);
	static std::vector<std::string> SplitLine(const std::string& opened);
};