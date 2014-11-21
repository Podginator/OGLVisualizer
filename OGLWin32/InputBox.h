#pragma once

#include <Windows.h>
#include "resource.h"
#include "DataCell.h"
#include "DataColumn.h"

class InputBox
{
public:
    InputBox(DataCell* cell, DataColumn* col)
    {
        _cell = cell;
        _col = col;

        ShowDialog();
    }

    InputBox();

    void ShowDialog()
    {
        HWND g_hToolbar = NULL;

        g_hToolbar = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1),
            NULL, (DLGPROC)DiaProc);
        if (g_hToolbar != NULL)
        {
            ShowWindow(g_hToolbar, SW_SHOW);
        }

        MSG n_msg;
        while (GetMessage(&n_msg, g_hToolbar, 0, 0) > 0)
        {
            //printf("Yessssssss\n");

            if (!IsDialogMessage(g_hToolbar, &n_msg))    // This is important!
            {
                TranslateMessage(&n_msg);
                DispatchMessage(&n_msg);
                printf("%d\n", n_msg.message);

            }
        }
    }

    static LRESULT CALLBACK DiaProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        switch (msg) {
        case WM_COMMAND:
            switch (wparam)
            {
            case IDOK:
                EndDialog(hwnd, 1);
                BOOL flag;
                _col->ChangeValues(_cell, GetDlgItemInt(hwnd, IDC_EDIT1, &flag, FALSE));
                DestroyWindow(hwnd);
                return 1;
            case IDCANCEL:
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

private:
    static DataCell* _cell;
    static DataColumn* _col;

};