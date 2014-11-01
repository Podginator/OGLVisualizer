#pragma once
#include "DataColumn.h"

std::string DataColumn::Name() const
{
    return header;
}

void DataColumn::Name(std::string name)
{
    header = name;
}

DataColumnString::DataColumnString(size_t _size) :DataColumn(_size)
{
    data = std::vector<std::string>(_size);
}

std::map<std::string, float> DataColumnString::GetDistribution()
{
    std::map<std::string, float> res;

    for (size_t i = 0; i < size; i++)
    {
        if (res.count(data[i]) == 1)
        {
            res[data[i]]++;
        }
        else
        {
            res[data[i]] = 1;
        }
    }

    std::map<std::string, float>::iterator mapIt = res.begin();
    while (mapIt != res.end())
    {
        mapIt->second /= size;
        mapIt++;
    }

    return res;
}

void DataColumnString::Add(std::string cell)
{
    data[index++] = cell;
}


DataColumnFloat::DataColumnFloat(size_t _size) :DataColumn(_size)
{
    data = std::vector<float>(_size);
}

void DataColumnFloat::Add(std::string cell)
{
    data[index++] = std::stof(cell);
}

std::map<std::string, float> DataColumnFloat::GetDistribution()
{
    std::map<std::string, float> res;

    for (size_t i = 0; i < size; i++)
    {
        if (res.count(std::to_string(data[i])) == 1)
        {
            res[std::to_string(data[i])]++;
        }
        else
        {
            res[std::to_string(data[i])] = 1;
        }
    }

    std::map<std::string, float>::iterator mapIt = res.begin();
    while (mapIt != res.end())
    {
        mapIt->second /= size;

        mapIt++;
    }

    return res;
}

DataColumnInt::DataColumnInt(size_t _size) :DataColumn(_size)
{
    data = std::vector<int>(_size);
}

void DataColumnInt::Add(std::string cell)
{
    data[index++] = std::stoi(cell);
}

std::map<std::string, float> DataColumnInt::GetDistribution()
{
    std::map<std::string, float> res;

    for (size_t i = 0; i < size; i++)
    {
        if (res.count(std::to_string(data[i])) == 1)
        {
            res[std::to_string(data[i])]++;
        }
        else
        {
            res[std::to_string(data[i])] = 1;
        }
    }

    std::map<std::string, float>::iterator mapIt = res.begin();
    while (mapIt != res.end())
    {
        mapIt->second /= size;
        mapIt++;
    }

    return res;

}