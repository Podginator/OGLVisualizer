#pragma once

#include "InputBox.h"

DataCell* InputBox::_cell;
std::map<DataCell*, size_t>* InputBox::_col;

InputBox::InputBox(DataCell* cell, std::map<DataCell*, size_t>* col)
{
    _cell = cell;
    _col = col;

    ShowDialog();
}

void InputBox::ShowDialog()
{
    HWND iwhnd = NULL;

    iwhnd = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1),
        NULL, (DLGPROC)DiaProc);
    if (iwhnd != NULL)
    {
        ShowWindow(iwhnd, SW_SHOW);
    }

    MSG n_msg;
    while (GetMessage(&n_msg, iwhnd, 0, 0) > 0)
    {
        //printf("Yessssssss\n");

        if (!IsDialogMessage(iwhnd, &n_msg))    // This is important!
        {
            TranslateMessage(&n_msg);
            DispatchMessage(&n_msg);
        }
    }
}

LRESULT CALLBACK InputBox::DiaProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg) {
    case WM_COMMAND:
        switch (wparam)
        {
        case IDOK:
            EndDialog(hwnd, 1);
            BOOL flag;
            _col->operator[](_cell) = size_t(GetDlgItemInt(hwnd, IDC_EDIT1, &flag, FALSE));
            DestroyWindow(hwnd);
            return 1;
        case IDCLOSE:
            EndDialog(hwnd, 1);
            DestroyWindow(hwnd);
        default:
            break;
        }
        //printf('\n%d', lparam == IDOK);
        break;
    default:
        break;
    }
    return 0;
}