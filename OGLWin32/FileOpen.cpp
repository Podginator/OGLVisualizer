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

bool FileOpen::ShowDialog()
{
	OPENFILENAMEA filename;
	char szName[MAX_PATH] = "";

	ZeroMemory(&filename, sizeof(filename));

	filename.lStructSize = sizeof(filename);
	filename.hwndOwner = 0;
	filename.lpstrFile = szName;
	filename.lpstrFile[0] = '\0';
	filename.lpstrFilter = "../";
	filename.nMaxFile = MAX_PATH;
	filename.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	filename.lpstrInitialDir = InitialDir;
	filename.lpstrDefExt = "txt";

	if (GetOpenFileNameA(&filename))
	{
		openedFile = std::tr2::sys::path(std::string(filename.lpstrFile));
		return true;
	}

	return false;
}

std::tr2::sys::path FileOpen::getFile()
{
	return openedFile;
}