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


std::map<DataCell*, size_t> DataColumn::GetDistribution()
{
    std::map<DataCell*, size_t> res;

    for (int i = 0; i < rawData.size(); i++)
    {
        DataCell cell = rawData[i];
        bool added = false;
        std::map<DataCell*, size_t>::iterator mapIt = res.begin();
        while (mapIt != res.end())
        {
            
            if (mapIt->first->equals<float>(cell))
            {
                mapIt->second++;
                added = true;
            }
            else if (mapIt->first->equals<int>(cell))
            {
                mapIt->second++;
                added = true;
            }
            if (mapIt->first->equals<std::string>(cell))
            {
                mapIt->second++;
                added = true;
            }
            mapIt++;
        }

        if (!added)
        {
            res[new DataCell(cell)] = 1;
        }
        
    }

    printf("%d", res.size());
    return res;
}

DataColumn::DataColumn(size_t _size) :size(_size), index(0)
{
    rawData = std::vector<DataCell>(_size);
}

DataColumn::DataColumn(size_t _size, Storage store) : size(_size), index(0), type(store)
{
    rawData = std::vector<DataCell>(_size);
}


void DataColumn::GetStats()
{
    Min = Max = 0;

    if (type == Numerical)
    {
        for (int i = 0; i < rawData.size(); i++)
        {
            if (rawData[i].isA<float>())
            {
                Max = rawData[i].asA<float>() > Max ? rawData[i].asA<float>() : Max;
            }
            else if (rawData[i].isA<int>())
            {
                Max = rawData[i].asA<int>() > Max ? rawData[i].asA<int>() : Max;
            }
        }
    }
    
}


void DataColumn::Add(std::string cell)
{
    char * line;
    float convL = std::strtof(cell.c_str(), &line);

     if (*line)
    {
        rawData[index++] = DataCell(cell);
    }
    else
    {
        if (float(int(convL)) == convL)
        {
            rawData[index++] = DataCell((int(convL)));
        }
        else
        {
            rawData[index++] = DataCell((float(convL)));
        }
    }

    GetStats();
}
