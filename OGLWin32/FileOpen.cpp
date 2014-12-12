#include "FileOpen.h"

FileOpen::FileOpen()
{

    Filefilters = new COMDLG_FILTERSPEC[1]{
        { L"All Files", L"*.*" }
    };
    filterSize = 1;
    InitialDir = "../";
}


FileOpen::FileOpen(std::map<LPWSTR,LPWSTR> filters)
{
    Filefilters = new COMDLG_FILTERSPEC[filters.size()+1];
    size_t i = 0;
    for (std::map<LPWSTR, LPWSTR>::iterator iterator = filters.begin(); iterator != filters.end(); iterator++)
    {
        Filefilters[i] = { LPWSTR(iterator->first), LPWSTR(iterator->second) };
        i++;
    }
    filterSize = i;
    InitialDir = "../";

}

FileOpen::FileOpen(char* dir, std::map<LPWSTR, LPWSTR> filters)
{
    Filefilters = new COMDLG_FILTERSPEC[filters.size() + 1];
    size_t i = 0;
    for (std::map<LPWSTR, LPWSTR>::iterator iterator = filters.begin(); iterator != filters.end(); iterator++)
    {
        Filefilters[i] = { LPWSTR(iterator->first), LPWSTR(iterator->second) };
        i++;
    }
    filterSize = i;

    InitialDir = dir;
}

FileOpen::~FileOpen()
{
    delete[] Filefilters;
}

bool FileOpen::ShowDialog() {
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    IFileOpenDialog* FileOpen;
    CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&FileOpen));

    FileOpen->SetFileTypes(filterSize, Filefilters);
    switch (FileOpen->Show(NULL)) {
    case S_OK: {
        IShellItem* Item{};
        FileOpen->GetResult(&Item);
        PWSTR FileCString;
        Item->GetDisplayName(SIGDN_FILESYSPATH, &FileCString);
        std::wstring FileWString{ FileCString };
        openedFile = { FileWString.begin(), FileWString.end() };

        return true;
    }
    case (ERROR_CANCELLED & 0x0000FFFF) | (FACILITY_WIN32 << 16) | 0x80000000:
        return false;
    }

    throw;

}


std::tr2::sys::wpath FileOpen::getFile()
{
    return openedFile;
}