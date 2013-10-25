#include <Windows.h>
#include <string>
#include <tchar.h>
#include <iostream>
#include <vector>

#include "Converter.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//Get the command line input
	vector<wstring> files;
	for (int i = 1; i < argc; ++i)
	{
		files.push_back(argv[i]);
	}

	if (files.size() > 0)
	{
		//Show files dropped onto the exe
		wcout << _T("Files: \n");
		for (unsigned int i = 0; i < files.size(); ++i)
		{
			wcout << _T(" - ") << files[i] << _T("\n");
		}
		Converter conv;
		conv.Convert(files);
		system("pause");
	} else {
		//Error: no files were dropped onto the exe
		wcout << _T("You have to drop 1 or more obj or a3d files onto this exe.\n");
		system("pause");
	}

	return 0;
}