#include <SDL.h>
#include "CApplication.h"

int main(int argc, char *argv[])
{
	CApplication *pApp = new CApplication();
	int rv = pApp->Run(argc, argv);
	delete pApp;

	return rv;
}
