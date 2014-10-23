#include "CSVParser.h"

CSVParser::CSVParser()
{
}

std::vector<std::vector<Proxy>> CSVParser::Parse(std::tr2::sys::wpath opened)
{
	std::cout << "Parsing..." << std::endl;
	std::ifstream stream(opened);

	//Iterate through the stream, counting each occurance of a newline.
	//Seems expensive, but if you think about what vector.pushback is doing 
	//Then it's not so much.
	std::vector<std::vector<Proxy>> res(
		std::count(
			std::istreambuf_iterator<char>(stream),
			std::istreambuf_iterator<char>{},
			'\n')+1
		);

	stream.clear();
	stream.seekg(0, std::ios::beg);
	
	std::string line;
	
	for (std::size_t i = 0; std::getline(stream, line); ++i)
	{
		res[i] = NewLine(line);
	}
	std::cout << "Done" << "\n";
	return res;
}

std::vector<Proxy> CSVParser::NewLine(const std::string& newline)
{
	//Preallocate size.
	static std::size_t const Size = std::count(newline.begin(), newline.end(), ',');
	
	std::cout << Size << std::endl;
	std::vector<Proxy> res(Size+1); 

	std::string line;
	std::getline(std::istringstream(newline), line);

	std::stringstream stream(line);
	std::string val;

	int i = 0;
	for (std::size_t i = 0; std::getline(stream, val, ','); ++i)
	{
		res[i] = Proxy(val);
	}


	return res;
}
