#include "FileOpen.h"

FileOpen::FileOpen()
{
	FileFilter = "All Files (*.*)\0*.*\0";
	InitialDir = "../";
}

FileOpen::FileOpen(char* filter)
{
	FileFilter = filter;
	InitialDir = "../";

}

FileOpen::FileOpen(char* dir, char* filter)
{
	FileFilter = filter; 
	InitialDir = dir;
}

bool FileOpen::ShowDialog() {
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	IFileOpenDialog* FileOpen;
	CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&FileOpen));

	COMDLG_FILTERSPEC rgSpec[] = {
		{ L"Comma separated values", L"*.csv" },
		// Add more here as they become available/necessary
	};

	FileOpen->SetFileTypes(ARRAYSIZE(rgSpec), rgSpec);
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