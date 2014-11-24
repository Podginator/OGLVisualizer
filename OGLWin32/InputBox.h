#pragma once

#include <Windows.h>
#include "resource.h"
#include "DataCell.h"
#include "DataColumn.h"

class InputBox
{
public:
    InputBox(DataCell* cell, DataColumn* col);
    InputBox();
    void ShowDialog();
private:
    static LRESULT CALLBACK DiaProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
    static DataCell* _cell;
    static DataColumn* _col;

};