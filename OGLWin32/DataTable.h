#pragma once
#include "DataColumn.h"

class DataTable
{
public:
    DataTable(size_t _size);
    ~DataTable();
    DataTable() :size(0){}
    void Add(const DataColumn& col);
    void Destroy();
    std::size_t size;
    DataColumn& operator[](size_t index);
    DataColumn operator[](size_t index) const;
protected:
    std::vector<DataColumn> cols;
};