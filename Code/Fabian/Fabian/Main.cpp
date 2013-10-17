#include <SDL.h>
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

#include "CApplication.h"

int main(int argc, char *argv[])
{
	CApplication *pApp = new CApplication();
	int rv = pApp->Run(argc, argv);
	delete pApp;

	return rv;
}
