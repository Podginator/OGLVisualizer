#pragma once 

#include <Windows.h>
#include "shobjidl.h"
#include <filesystem>
#include <string>
#include <fstream>

class FileOpen
{
public:
	FileOpen(char* type);
	FileOpen(char* Dir, char* type);
	FileOpen();

	char* FileFilter;
	char* InitialDir;

	bool ShowDialog();
	std::tr2::sys::wpath getFile();

private:
	std::tr2::sys::wpath openedFile;
	//std::string ConvertToString(FILE* file);
};