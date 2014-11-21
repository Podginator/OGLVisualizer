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
    int Max;
    int Min;
    void ChangeValues(DataCell* cell, size_t _size)
    {
        size_t prevSize = dataDist[cell];
        if (_size == 0)
        {
            std::map<DataCell*, size_t>::iterator it = dataDist.find(cell);
            dataDist.erase(it);
            delete cell;
            size -= prevSize;
            return;
        }

        dataDist[cell] = _size;
        size += _size > prevSize ? -(prevSize-_size) : (_size-prevSize);

        GetStats();

        printf("%d\n", size);
    }

    template<class Type> void AddElement(DataCell& cell);
    std::map<std::string, float> GetDistribution();
    std::map<DataCell*, size_t> dataDist;
    size_t operator[](DataCell* rhs){ return dataDist[rhs]; }
    DataColumn(){};
    DataColumn(size_t size);
    ~DataColumn(){};
protected:
    void GetStats();
    std::string header;
    std::size_t index;
    std::vector<DataCell> data;
    
};
