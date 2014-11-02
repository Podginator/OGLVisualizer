#pragma once
#include "DataColumn.h"

class DataTable
{
public:
    DataTable(size_t _size);
    ~DataTable();

    void Add(DataColumn* col);
    std::size_t size;
    DataColumn* operator[](size_t index);
    DataColumn* operator[](size_t index) const;
protected:
    std::vector<DataColumn*> cols;
};