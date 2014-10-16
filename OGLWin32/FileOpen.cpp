#include "FileOpen.h"

FileOpen::FileOpen()
{
	FileFilter = L"All Files (*.*)\0*.*\0";
	InitialDir = L"../";
}

FileOpen::FileOpen(LPWSTR filter)
{
	FileFilter = filter;
	InitialDir = L"../";

}

FileOpen::FileOpen(LPCTSTR dir, LPWSTR filter)
{
	FileFilter = filter; 
	InitialDir = dir;
}

bool FileOpen::ShowDialog()
{
	OPENFILENAME filename;
	char szName[MAX_PATH] = "";

	ZeroMemory(&filename, sizeof(filename));

	filename.lStructSize = sizeof(filename);
	filename.hwndOwner = 0;
	filename.lpstrFile = (LPWSTR)szName;
	filename.lpstrFile[0] = '\0';
	filename.lpstrFilter = FileFilter;
	filename.nMaxFile = MAX_PATH;
	filename.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	filename.lpstrInitialDir = InitialDir;
	filename.lpstrDefExt = L"txt";

	if (GetOpenFileName(&filename))
	{
		openedFile = _wfopen(filename.lpstrFile, L"r");
		return true;
	}

	return false;
}



std::FILE* FileOpen::getFile()
{
	return openedFile;
}