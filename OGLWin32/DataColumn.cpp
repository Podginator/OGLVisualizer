#pragma once
#include "DataColumn.h"

std::string DataColumn::Name() const
{
    return header;
}

void DataColumn::Name(std::string name)
{
    std::string cat = type == Numerical ? name + " (Numerical)" : name + " (Categorical)";
    header = cat;
}


std::map<DataCell*, size_t> DataColumn::GetDistribution()
{
    std::map<DataCell*, size_t> res;

    for (int i = 0; i < data.size(); i++)
    {
        DataCell cell = data[i];
        bool added = false;
        std::map<DataCell*, size_t>::iterator mapIt = res.begin();
        if (!(data[i].isNull()))
        {
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
    }

    printf("%d", res.size());
    return res;
}

DataColumn::DataColumn(size_t _size) :size(_size), index(0)
{
    data = std::vector<DataCell>(_size);
}

DataColumn::DataColumn(size_t _size, Storage store) : size(_size), index(0), type(store)
{
    data = std::vector<DataCell>(_size);
}


void DataColumn::GetStats()
{
    Min = Max = 0;

    if (type == Numerical)
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i].isA<float>())
            {
                if (Min == 0){ Min = data[i].asA<float>(); }
                Max = data[i].asA<float>() > Max ? data[i].asA<float>() : Max;
                Min = data[i].asA<float>() < Min ? data[i].asA<float>() : Min;
            }
            else if (data[i].isA<int>())
            {
                if (Min == 0){ Min = data[i].asA<int>(); }
                Max = data[i].asA<int>() > Max ? data[i].asA<int>() : Max;
                Min = data[i].asA<int>() < Min ? data[i].asA<int>() : Min;
            }
        }
    }
}


void DataColumn::Add(std::string cell)
{
    char * line;
    float convL = std::strtof(cell.c_str(), &line);
    DataCell _cell;

    if (*line)
    {
        _cell = DataCell(cell);
    }
    else
    {
        if (float(int(convL)) == convL)
        {
            _cell = DataCell((int(convL)));
        }
        else
        {
            _cell = DataCell((float(convL)));
        }
    }

    if (!(_cell.isNull()))
    {
        data[index++] = _cell;
    }
    
}
