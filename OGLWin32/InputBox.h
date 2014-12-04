#pragma once

#include <Windows.h>
#include "resource.h"
#include "DataCell.h"
#include "DataColumn.h"

class InputBox
{
public:
    InputBox(DataCell* cell, std::map<DataCell*, size_t>* col);
    InputBox();
    void ShowDialog();
private:
    static LRESULT CALLBACK DiaProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
    static DataCell* _cell;
    static std::map<DataCell*, size_t>* _col;

};