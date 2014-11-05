#pragma once
#include <string>
#include <vector>
#include <array>
#include <map>
#include "DataCell.h"
class DataColumn
{
public:
    size_t size;
    std::string Name() const;
    void Name(std::string name);
    virtual void Add(std::string cell);
    virtual std::map<std::string, float> GetDistribution();
    DataColumn(){};
    DataColumn(size_t size);
    ~DataColumn(){};
protected:
    std::string header;
    std::size_t index;
    std::vector<DataCell> data;
};
