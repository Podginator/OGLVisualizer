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
    void Add(std::string cell);
    template<class Type> void AddElement(DataCell& cell);
    std::map<std::string, float> GetDistribution();
    std::map<DataCell*, size_t> dataDist;
    size_t operator[](DataCell* rhs){ return dataDist[rhs]; }
    DataColumn(){};
    DataColumn(size_t size);
    ~DataColumn(){};
protected:
    std::string header;
    std::size_t index;
    std::vector<DataCell> data;
    
};