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


void DataColumn::GetStats()
{
    Min = Max = 0;

    std::map<DataCell*, size_t>::iterator mapIt = dataDist.begin();

    while (mapIt != dataDist.end())
    {
        if (Min == 0)
        {
            Min = mapIt->second;
        }
        if (mapIt->second > Max)
        {
            Max = mapIt->second;
        }
        if (mapIt->second < Min)
        {
            Min = mapIt->second;
        }

        mapIt++;
    }
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

    GetStats();
}
