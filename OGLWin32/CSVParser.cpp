#include "CSVParser.h"

std::vector<CSVColBase*> CSVParser::GetCols(std::ifstream& stream, size_t size)
{
	std::string first, second;
	std::getline(stream, first);
	std::getline(stream, second);

	std::vector<std::string> header, def;
	header = SplitLine(first);
	def = SplitLine(second);

	bool hasHeader = false;

	std::vector<CSVColBase*> columns;

	for (size_t i = 0; i < header.size(); i++)
	{
		char * h;
		char * line;

		float convH = std::strtof(header[i].c_str(), &h);
		float convL = std::strtof(def[i].c_str(), &line);

		if (*h && *line)
		{
			columns.push_back(new CSVColumn<std::string>(size));
		}
		else if (*h || *line)
		{
			hasHeader = true;
			
			if ((float)std::stoi(def[i]) == std::stof(def[i]))
			{
				columns.push_back(new CSVColumn<int>(size));
			}
			else
			{
				columns.push_back(new CSVColumn<float>(size));
			}
		}
		else
		{
			if ((float)std::stoi(def[i]) == std::stof(def[i]))
			{
				columns.push_back(new CSVColumn<int>(size));
			}
			else
			{
				columns.push_back(new CSVColumn<float>(size));
			}
		}
	}

	for (size_t i = 0; i < header.size(); i++)
	{
		if (hasHeader)
		{
			columns[i]->Name(header[i]);
		}
		else
		{
			columns[i]->Name("Value#" + std::to_string(i));
		}
	}

	return columns;
}

std::vector<std::vector<std::string>> CSVParser::Parse(std::tr2::sys::wpath opened)
{
	std::cout << "Parsing..." << std::endl;
	std::ifstream stream(opened);
	int size = std::count(
		std::istreambuf_iterator<char>(stream),
		std::istreambuf_iterator<char>{},
		'\n') + 1;
	stream.clear();
	stream.seekg(0, std::ios::beg);

	std::vector<CSVColBase*> cols = GetCols(stream, size);

	stream.clear();
	stream.seekg(0, std::ios::beg);


	std::vector<std::vector<std::string>> res(size);

	std::string line;
	
	for (std::size_t i = 0; std::getline(stream, line); ++i)
	{
		res[i] = SplitLine(line);
		AddToCols(line, cols);
	}
	std::cout << "Done" << "\n";
	return res;
}

std::vector<std::string> CSVParser::SplitLine(const std::string& newline)
{
	//Preallocate size.
	static std::size_t const Size = std::count(newline.begin(), newline.end(), ',');

	std::vector<std::string> res(Size+1); 

	std::string line;
	std::getline(std::istringstream(newline), line);

	std::stringstream stream(line);
	std::string val;

	for (std::size_t i = 0; std::getline(stream, val, ','); ++i)
	{
		res[i] = val;
	}

	return res;
}


void CSVParser::AddToCols(const std::string& newline, std::vector<CSVColBase*> cols)
{
	//Preallocate size.
	static std::size_t const Size = std::count(newline.begin(), newline.end(), ',');

	std::vector<std::string> res(Size + 1);

	std::string line;
	std::getline(std::istringstream(newline), line);

	std::stringstream stream(line);
	std::string val;

	for (std::size_t i = 0; std::getline(stream, val, ','); ++i)
	{
		cols[i]->Add(val);
	}

}
