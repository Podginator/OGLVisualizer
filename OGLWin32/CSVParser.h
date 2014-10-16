#pragma once 
#include "Proxy.h"
#include <vector>
#include <iostream>
#include <sstream>


class CSVParser
{
public:
	CSVParser();
	static std::vector<std::vector<Proxy>> Parse(FILE* opened);
private:
	static std::vector<Proxy> NewLine(const std::string& opened);
	static std::string ConvertToString(FILE* file);
};