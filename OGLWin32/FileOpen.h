#pragma once 

#include <Windows.h>
#include <string>
#include <fstream>

class FileOpen
{
public:
	FileOpen(LPWSTR type);
	FileOpen(LPCTSTR Dir, LPWSTR type);
	FileOpen();

	LPWSTR FileFilter;
	LPCTSTR InitialDir;

	bool ShowDialog();
	std::FILE* getFile();

private:
	std::FILE* openedFile;
	//std::string ConvertToString(FILE* file);
};