#pragma once 

#include <Windows.h>
#include "shobjidl.h"
#include <filesystem>
#include <string>
#include <fstream>
#include <map>

class FileOpen
{
public:
	FileOpen(std::map<LPWSTR,LPWSTR> filters);
	FileOpen(char* Dir, std::map<LPWSTR, LPWSTR> filters);
	FileOpen();

	~FileOpen();
	std::map<char*, char*> FileFilter;
	char* InitialDir;
	COMDLG_FILTERSPEC* Filefilters;

	bool ShowDialog();
	std::tr2::sys::wpath getFile();

private:
	std::tr2::sys::wpath openedFile;
	size_t filterSize;
	//std::string ConvertToString(FILE* file);
};