#pragma once 
#include "Proxy.h"
#include <vector>
#include <iostream>
#include <filesystem>
#include <sstream>


class CSVParser
{
public:
	CSVParser();
	static std::vector<std::vector<Proxy>> Parse(std::tr2::sys::wpath opened);
private:
	static std::vector<Proxy> NewLine(const std::string& opened);
};