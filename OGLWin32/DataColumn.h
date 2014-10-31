#pragma once
#include <string>
#include <vector>
#include <array>

class DataColumn
{
public:
    std::string Name() const{ return header; } 
    void Name(std::string name){ header = name;}
    virtual void Add(std::string cell) = 0;

    DataColumn(size_t size) :size(size), index(0){}
    size_t size;

    ~DataColumn()
    {
    }

protected:
    std::string header;
    std::size_t index;
    
};


class DataColumnString : public DataColumn
{
public:
    DataColumnString(size_t _size) :DataColumn(_size)
    {
        data = std::vector<std::string>(_size);
    }

    void Add(std::string cell)
    {
        data[index++] = cell;
    }

private:
    std::vector<std::string> data;
};

class DataColumnFloat : public DataColumn
{
public:
    DataColumnFloat(size_t _size) :DataColumn(_size)
    {
        data = std::vector<float>(_size);
    }

    void Add(std::string cell)
    {
        data[index++] = std::stof(cell);
    }

private:
    std::vector<float> data;
};

class DataColumnInt : public DataColumn
{
public:
    DataColumnInt(size_t _size) :DataColumn(_size)
    {
        data = std::vector<int>(_size);
    }

    void Add(std::string cell)
    {
        data[index++] = std::stoi(cell);
    }

private:
    std::vector<int> data;
};