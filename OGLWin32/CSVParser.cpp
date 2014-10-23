#include "CSVParser.h"

CSVParser::CSVParser()
{
}

std::vector<std::vector<Proxy>> CSVParser::Parse(std::tr2::sys::wpath opened)
{
	std::cout << "Parsing..." << "\n";
	std::ifstream stream(opened);

	//Iterate through the stream, counting each occurance of a newline.
	//Seems expensive, but if you think about what PushBack is doing 
	//Then it's not so much.
	std::vector<std::vector<Proxy>> res(
		std::count(std::istreambuf_iterator<char>(stream),
		std::istreambuf_iterator<char>{},
		'\n')
		);
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
	//Preallocate size.
	static std::size_t const Size = std::count(newline.begin(), newline.end(), ',');
	std::vector<Proxy> res(Size); 

	std::string line;
	std::getline(std::istringstream(newline), line);

	std::stringstream stream(line);
	std::string val;

	//Convert Objects to Proxy values and push to the back.
	while (std::getline(stream, val, ','))
	{
		res.push_back(Proxy(val));
	}


	return res;
}
