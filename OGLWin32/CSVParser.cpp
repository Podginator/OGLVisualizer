#include "CSVParser.h"

void CSVParser::ResetStream(std::ifstream& stream)
{
    stream.clear();
    stream.seekg(0, std::ios::beg);
}

DataTable CSVParser::GetCols(std::ifstream& stream)
{
    size_t size = std::count(
        std::istreambuf_iterator<char>(stream),
        std::istreambuf_iterator<char>{},
        '\n');
    ResetStream(stream);

    std::string first, second;
    std::getline(stream, first);
    std::getline(stream, second);

    std::vector<std::string> header, def;
    header = SplitLine(first);
    def = SplitLine(second);

    bool hasHeader = false;

    DataTable cols(header.size());

    //Here we loop through and determine the types we'll use AND if there's a header.
    size = hasHeader ? size - 1 : size;

    for (size_t i = 0; i < header.size(); i++)
    {
        char * h;
        char * line;

        float convH = std::strtof(header[i].c_str(), &h);
        float convL = std::strtof(def[i].c_str(), &line);

        if (*h || *line)
        {
            hasHeader = true;
        }
        
        cols.Add(DataColumn(size));
    }

    for (size_t i = 0; i < header.size(); i++)
    {
        //Then loop again adding names to the columns
        cols[i].Name(hasHeader ? header[i] : "Value" + std::to_string(i));
    }

    //Reset the strream
    ResetStream(stream);
    //And move the pointer to the second line if there's a header.
    if (hasHeader)
    {
        std::getline(stream, first);
    }

    return cols;
}

DataTable CSVParser::Parse(std::tr2::sys::wpath opened)
{
    std::cout << "Parsing..." << std::endl;
    std::ifstream stream(opened);
        
    
    DataTable cols = GetCols(stream);
    
    std::string line;
    
    for (std::size_t i = 0; std::getline(stream, line); ++i)
    {
        AddToCols(line, cols);
    }
    std::cout << "Done" << "\n"; 
    return cols;
}

std::vector<std::string> CSVParser::SplitLine(const std::string& newline)
{
    //Preallocate size.
    std::size_t const Size = std::count(newline.begin(), newline.end(), ',');

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

void CSVParser::AddToCols(const std::string& newline, DataTable& cols)
{
    std::string line;
    std::getline(std::istringstream(newline), line);

    std::stringstream stream(line);
    std::string val;

    for (std::size_t i = 0; std::getline(stream, val, ','); ++i)
    {
        cols[i].Add(val);
    }
}
