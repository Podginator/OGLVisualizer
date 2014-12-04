#pragma once
#include <string>
#include <vector>
#include <array>
#include <map>
#include "DataCell.h"
class DataColumn
{
public:
    enum Storage{
        Numerical,Categorical
    };
    size_t size;
    std::string Name() const;
    void Name(std::string name);
    Storage Stores() const { return type; }
    void Stores(Storage _type){ type = _type; }
    void Add(std::string cell);
    int Max;
    int Min;
    void ChangeValues(DataCell* cell, size_t _size);
    std::map<DataCell*, size_t> GetDistribution();

    std::vector<DataCell> rawData;
    DataColumn(){};
    DataColumn(size_t size);
    DataColumn(size_t size, Storage type);
    ~DataColumn(){};
protected:
    void GetStats();
    Storage type;
    std::string header;
    std::size_t index;
};
