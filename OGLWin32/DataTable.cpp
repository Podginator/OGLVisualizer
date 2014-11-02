#pragma once
#include "DataTable.h"

DataTable::DataTable(size_t _size)
{ 
    cols = std::vector<DataColumn*>(_size);
    size = 0; 
}

void DataTable::Add(DataColumn* col)
{
    cols[size++] = col;
}

DataTable::~DataTable(){}

DataColumn* DataTable::operator[](size_t index){ return cols[index]; }
DataColumn* DataTable::operator[](size_t index) const{ return cols[index]; }