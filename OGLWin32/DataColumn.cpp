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

DataColumn::DataColumn(size_t _size) :size(_size), index(0)
{
    data = std::vector<DataCell>(_size);
}

void DataColumn::Add(std::string cell)
{
    char * line;
    float convL = std::strtof(cell.c_str(), &line);

    if (*line)
    {
        data[index++] = DataCell(cell);
    }
    else
    {
        if (float(int(convL)) == convL)
        {
            data[index++] = DataCell((int(convL)));
        }
        else
        {
            data[index++] = DataCell((float(convL)));
        }
    }
}

std::map<std::string, float> DataColumn::GetDistribution()
{
    std::map<std::string, float> res;
    std::string identifier;
    for (size_t i = 0; i < size; i++)
    {
        if (data[i].null()){ break; }

        if ((data[i].is<std::string>()))
        {
            identifier = data[i].as<std::string>();
        }
        else if (data[i].is<float>())
        {
            identifier = std::to_string(data[i].as<float>());
        }
        else{
            identifier = std::to_string(data[i].as<int>());
        }
        if (res.count(identifier) == 1)
        {
            res[identifier]++;
        }
        else
        {
            res[identifier] = 1;
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

