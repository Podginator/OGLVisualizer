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
    rawData = std::vector<DataCell>(_size);
}

DataColumn::DataColumn(size_t _size, Storage store) : size(_size), index(0), type(store)
{
    rawData = std::vector<DataCell>(_size);
}

void DataColumn::ChangeValues(DataCell* cell, size_t _size)
{
    size_t prevSize = dataDist[cell];
    if (_size == 0)
    {
        std::map<DataCell*, size_t>::iterator it = dataDist.find(cell);
        dataDist.erase(it);
        //delete cell;
        size -= prevSize;
        return;
    }

    dataDist[cell] = _size;
    size += _size > prevSize ? -(prevSize - _size) : (_size - prevSize);

    GetStats();

    printf("%d\n", size);
}


void DataColumn::GetStats()
{
    Min = Max = MaxDist = 0;
    

    std::map<DataCell*, size_t>::iterator mapIt = dataDist.begin();
    while (mapIt != dataDist.end())
    {
        if (Min == 0)
        {
            Min = mapIt->second;
        }
        if (mapIt->second > Max)
        {
            MaxDist = mapIt->second;
        }
        if (mapIt->second < Min)
        {
            Min = mapIt->second;
        }

        mapIt++;
    }
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
        rawData[index++] = DataCell(cell);
        AddElement<std::string>(DataCell(cell));

    }
    else
    {
        if (float(int(convL)) == convL)
        {
            rawData[index++] = DataCell((int(convL)));
            AddElement<int>(DataCell((int(convL))));

        }
        else
        {
            rawData[index++] = DataCell((float(convL)));
            AddElement<float>(DataCell((float(convL))));
        }
    }

    GetStats();
}
