#pragma once
#include "DataColumn.h"

class DataTable
{
public:
    DataTable(size_t _size);
    ~DataTable();
    std::size_t size;
    DataColumn* operator[](size_t index){ return cols[index]; }
    DataColumn* operator[](size_t index) const{ return cols[index]; }
private:
    std::vector<DataColumn*> cols;

};