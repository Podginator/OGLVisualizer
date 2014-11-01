#pragma once
#include <string>
#include <vector>
#include <array>
#include <map>
class DataColumn
{
public:
    size_t size;
    std::string Name() const;
    void Name(std::string name);
    virtual void Add(std::string cell) = 0;
    virtual std::map<std::string, float> GetDistribution() = 0;

    DataColumn(size_t size) :size(size), index(0){}
    ~DataColumn(){};
protected:
    std::string header;
    std::size_t index;
};

class DataColumnString : public DataColumn
{
public:
    DataColumnString(size_t _size);
    std::map<std::string, float> GetDistribution();
    void Add(std::string cell);
private:
    std::vector<std::string> data;
};

class DataColumnFloat : public DataColumn
{
public:
    DataColumnFloat(size_t _size);
    void Add(std::string cell);
    std::map<std::string, float> GetDistribution();
private:
    std::vector<float> data;
};

class DataColumnInt : public DataColumn
{
public:
    DataColumnInt(size_t _size);
    void Add(std::string cell);
    std::map<std::string, float> GetDistribution();
private:
    std::vector<int> data;
};