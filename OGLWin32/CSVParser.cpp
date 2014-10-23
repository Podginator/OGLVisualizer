#include "CSVParser.h"

CSVParser::CSVParser()
{
}

std::vector<std::vector<Proxy>> CSVParser::Parse(std::tr2::sys::wpath opened)
{
	std::cout << "Parsing..." << "\n";
	std::vector<std::vector<Proxy>> res;
	std::ifstream stream(opened);
	std::string line;
	//std::istringstream stream();
	while (std::getline(stream, line))
	{
		res.push_back(NewLine(line));
	}

	std::cout << "Done" << "\n";
	return res;
}

std::vector<Proxy> CSVParser::NewLine(const std::string& newline)
{
	std::vector<Proxy> res; 

	std::string line;
	std::getline(std::istringstream(newline), line);

	std::stringstream stream(line);
	std::string val;

	//Convert Objects to Proxy values and push to the back.
	while (std::getline(stream, val, ';'))
	{
		res.push_back(Proxy(val));
	}


	return res;
}
