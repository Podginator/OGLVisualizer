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

template<class Type> 
void DataColumn::AddElement(DataCell& cell)
{
    std::map<DataCell*, size_t>::iterator mapIt = dataDist.begin();

    while (mapIt != dataDist.end())
    {
        if (mapIt->first->equals<Type>(cell))
        {
            mapIt->second++;
            return;
        }
        mapIt++;
    }

    dataDist[new DataCell(cell)] = 1; 
}


void DataColumn::Add(std::string cell)
{
    char * line;
    float convL = std::strtof(cell.c_str(), &line);

    if (*line)
    {
        data[index++] = DataCell(cell);
        AddElement<std::string>(DataCell(cell));

    }
    else
    {
        if (float(int(convL)) == convL)
        {
            data[index++] = DataCell((int(convL)));
            AddElement<int>(DataCell((int(convL))));

        }
        else
        {
            data[index++] = DataCell((float(convL)));
            AddElement<float>(DataCell((float(convL))));
        }
    }
}

std::map<std::string, float> DataColumn::GetDistribution()
{
    std::map<std::string, float> res;
    std::string identifier;
    for (size_t i = 0; i < size; i++)
    {
        if (data[i].isNull()){ break; }

        if ((data[i].isA<std::string>()))
        {
            identifier = data[i].asA<std::string>();
        }
        else if (data[i].isA<float>())
        {
            identifier = std::to_string(data[i].asA<float>());
        }
        else{
            identifier = std::to_string(data[i].asA<int>());
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

