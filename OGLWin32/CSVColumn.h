#pragma once
#include <string>
#include <vector>
#include <array>

class CSVColumn
{
public:
    enum Type{
        Numerical,
        String,
        Date
    };
    std::string Name() const{ return header; } 
    void Name(std::string name){ header = name;}
    void Add(std::string cell)
    {
        data[size++] = cell;
    }

    std::string& operator[](int rhs){ return data[rhs]; }
    std::string operator[](int rhs) const { return data[rhs]; }

    Type GetType() const{ return type; }
    CSVColumn(size_t _size, Type _type){ data = std::vector<std::string>(_size); size = 0; type = _type; }
    size_t size;

    CSVColumn(){};
private:
    std::string header;
    Type type;
    std::vector<std::string> data;
};
