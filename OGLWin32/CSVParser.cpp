#include "CSVParser.h"

CSVParser::CSVParser()
{
}

std::vector<std::vector<Proxy>> CSVParser::Parse(FILE* opened)
{
	std::cout << "Start" << "\n";
	std::vector<std::vector<Proxy>> res;

	std::string line;
	std::istringstream stream(ConvertToString(opened));
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

std::string CSVParser::ConvertToString(FILE* file)
{
	std::string contents;
	std::fseek(file, 0, SEEK_END);
	contents.resize(std::ftell(file));
	std::rewind(file);
	std::fread(&contents[0], 1, contents.size(), file);
	std::fclose(file);
	return(contents);
}