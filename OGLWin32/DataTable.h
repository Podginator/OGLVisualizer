#pragma once
#include "DataColumn.h"

class DataTable
{
public:
    DataTable(size_t _size){ cols = std::vector<DataColumn*>(_size); size = 0; }
    void Add(DataColumn* column)
    {
        cols[size++] = column;
    }

    ~DataTable()
    {
        for (size_t i = 0; i < size; i++)
        {
            //delete cols[i];
        }
    }

    DataColumn* operator[](size_t index){ return cols[index]; }
    //Const set.
    DataColumn* operator[](size_t index) const{ return cols[index]; }

    std::size_t size;

private:
    std::vector<DataColumn*> cols;

};