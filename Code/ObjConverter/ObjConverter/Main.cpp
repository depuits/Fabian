#include <string>
#include <iostream>
#include <vector>

#include "Converter.h"

using namespace std;

int main(int argc, char* argv[])
{
	//Get the command line input
	vector<string> files;
	for (int i = 1; i < argc; ++i)
	{
		files.push_back(argv[i]);
	}

	if (files.size() > 0)
	{
		//Show files dropped onto the exe
		cout << "Files: \n";
		for (unsigned int i = 0; i < files.size(); ++i)
		{
			cout << " - " << files[i] << "\n";
		}
		Converter conv;
		conv.Convert(files);
		#ifdef WIN32
            cin.get();
		#endif
	} else {
		//Error: no files were dropped onto the exe
		cout << "You have to drop 1 or more obj or a3d files onto this exe.\n";
		#ifdef WIN32
            cin.get();
		#endif
	}

	return 0;
}
